// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#include <OB/CORBA.h>
#include <OB/Codec.h>

#include <CorbaOut.h>

#include <stdio.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif
using namespace CORBA;
using namespace DynamicAny;
using namespace IOP;

char*
CorbaOut::getOctet(Octet oct)
{
    char str[5];
    sprintf(str, "<%02X>", oct);

    return string_dup(str);
}

CorbaOut::CorbaOut(DynamicAny::DynAnyFactory_ptr factory, ostream& ostr)
    : factory_(DynamicAny::DynAnyFactory::_duplicate(factory)),
      ostr_(ostr),
      level_(0)
{
}

CorbaOut::~CorbaOut()
{
}
    
ostream&
CorbaOut::skip()
{
    for(int i = 0 ; i < level_; i++)
	ostr_ << "   ";
    return ostr_;
}
    
// ----------------------------------------------------------------------
// Display CORBA::TypeCode
// ----------------------------------------------------------------------

static const char* NameTypeIDL [] =
{
    "null", "void",
    "short", "long",
    "unsigned short", "unsigned long",
    "float", "double",
    "boolean",
    "char",
    "octet",
    "any",
    "TypeCode",
    "Principal",
    "objref",
    "struct", "union",
    "enum",
    "string",
    "sequence", "array",
    "alias",
    "exception",
    "long long", "unsigned long long",
    "long double",
    "wchar", "wstring",
    "fixed",
    "value", "valuebox",
    "native",
    "abstract_interface"
};

void
CorbaOut::display_IDL_TypeCode(TypeCode_ptr tc)
{
    ULong i;
    TCKind kind = tc -> kind();

    switch(kind)
    {
    case tk_objref:
        skip() << "interface " << tc -> name() << ';';
        break;

    case tk_struct:
    case tk_except:
    {
        skip() << NameTypeIDL[kind] << ' ' << tc -> name() << " {"
	       << OB_ENDL;

        down();
        for(i = 0; i < tc -> member_count() ; i++)
	{
            skip();
            TypeCode_var member_type = tc -> member_type(i);
            show_name_TypeCode(member_type);
            ostr_ << ' ' << tc -> member_name(i) << ';' << OB_ENDL;
        }
        up();
        skip() << "};";

	break;
    }
 
    case tk_union:
    {
        skip() << "union " << tc -> name() << " switch(";
        TypeCode_var discriminator_type = tc -> discriminator_type();
        show_name_TypeCode(discriminator_type);
        ostr_ << ") {" << OB_ENDL;

        down();
        for(i = 0 ; i < tc -> member_count() ; i++)
	{
            Any_var any_member_label = tc -> member_label(i);
            TypeCode_var type_label = any_member_label -> type();
            if(type_label -> kind() == tk_octet)
	    {
	        skip() << "default";
            }
	    else
	    {
	        skip() << "case ";
                DynAny_var dyn_any_member_label =
                    factory_ -> create_dyn_any(any_member_label);
                show_DynAny_without_type(dyn_any_member_label);
            }
            ostr_ << ": ";
            TypeCode_var member_type = tc -> member_type(i);
            show_name_TypeCode(member_type);
            ostr_ << ' ' << tc -> member_name(i) << ';' << OB_ENDL;
        }
        up();
        skip() << "};"; 

	break;
    }

    case tk_enum:
    {
        skip()  << "enum " << tc -> name() << " {";
        for(i = 0 ; i < tc -> member_count() ; i++) {
            if(i != 0)
 	       ostr_ << ", ";
            ostr_ << tc -> member_name(i);
        }
        ostr_ << "};";

        break;
    }

    case tk_string:
    {
        skip() << "string";
        ULong length = tc -> length();
        if(length != 0)
	  ostr_ << '<' << length << '>';

	break;
    }

    case tk_sequence:
    {
        skip() << "sequence<";
        TypeCode_var content_type = tc -> content_type();
        show_name_TypeCode(content_type);
        ULong length = tc -> length();
        if(length != 0)
          ostr_ << ", " << length;
        ostr_ << '>';

	break;
    }

    case tk_array:
    {
        skip();
        TypeCode_var content_type = tc -> content_type();
        show_name_TypeCode(content_type);
        ostr_ << '[' << tc -> length() << ']';

	break;
    }

    case tk_alias:
    {
        skip() << "typedef ";
        TypeCode_var content_type = tc -> content_type();
        show_name_TypeCode(content_type);
        ostr_ << ' ' << tc -> name() << ';';

	break;
    }

    default:
        skip() << NameTypeIDL [kind];

	break;
    }

    ostr_ << OB_ENDL;
}

void
CorbaOut::show_name_TypeCode(TypeCode_ptr tc)
{
    TCKind kind = tc -> kind();

    switch(kind)
    {
    case tk_objref:
    case tk_enum:
    case tk_union:
    case tk_struct:
    case tk_except:
    case tk_alias:
    {
        ostr_ << tc -> name();

        break;
    }

    case tk_string:
    {
        ostr_ << "string";
        ULong length = tc -> length();
        if(length != 0)
	  ostr_ << '<' << length << '>';

	break;
    }

    case tk_sequence:
    {
        ostr_ << "sequence<";
        TypeCode_var content_type = tc -> content_type();
        show_name_TypeCode(content_type);
        ULong length = tc -> length();
        if(length != 0)
          ostr_ << ", " << length;
        ostr_ << '>';

	break;
    }

    case tk_array:
    {
        TypeCode_var content_type = tc -> content_type();
        show_name_TypeCode(content_type);
        ostr_ << '[' << tc -> length() << ']';

	break;
    }

    default:
    {
        ostr_ << NameTypeIDL [kind];

        break;
    }
    }
}

// ----------------------------------------------------------------------
// Show CORBA::DynAny
// ----------------------------------------------------------------------

void
CorbaOut::display_DynAny(DynAny_ptr dyn_any)
{
    skip();
    show_DynAny(dyn_any);
    ostr_ << OB_ENDL;
}

void
CorbaOut::show_DynAny(DynAny_ptr dyn_any)
{
    TypeCode_var tc = dyn_any -> type();

    show_name_TypeCode(tc);
    ostr_ << '(';
    show_DynAny_without_type(dyn_any);
    ostr_ << ')';
}

void
CorbaOut::show_DynAny_without_type(DynAny_ptr dyn_any)
{
    ULong i;

    dyn_any -> rewind();

    TypeCode_var tc = dyn_any -> type();
    tc = OB::GetOrigType(tc);

    TCKind kind = tc -> kind();

    switch(kind)
    {
    case tk_null:
    case tk_void:
    {
	break;
    }

    case tk_short:
    {
        Short v_short = dyn_any -> get_short();
        ostr_ << v_short;

	break;
    }

    case tk_long:
    {
        Long v_long = dyn_any -> get_long();
        ostr_ << v_long;

	break;
    }

    case tk_ushort:
    {
        UShort v_ushort = dyn_any -> get_ushort();
        ostr_ << v_ushort;

	break;
    }

    case tk_ulong:
    {
        ULong v_ulong = dyn_any -> get_ulong();
        ostr_ << v_ulong;

	break;
    }

    case tk_float:
    {
        Float v_float = dyn_any -> get_float();
        ostr_ << v_float;

	break;
    }

    case tk_double:
    {
        Double v_double = dyn_any -> get_double();
        ostr_ << v_double;

	break;
    }

    case tk_boolean:
    {
        Boolean v_boolean = dyn_any -> get_boolean();
        if(v_boolean == true)
	    ostr_ << "TRUE";
        else ostr_ << "FALSE";

	break;
    }

    case tk_char:
    {
        Char v_char = dyn_any -> get_char();
        ostr_ << "'" <<(char)v_char << "'";

	break;
    }

    case tk_octet:
    {
        Octet v_octet = dyn_any -> get_octet();
        ostr_ << int(v_octet);

	break;
    }

    case tk_any:
    {
        Any_var v_any = dyn_any -> get_any();
        show_Any(v_any);

	break; 
    }

    case tk_TypeCode: {
        TypeCode_var v_tc = dyn_any -> get_typecode();
        show_name_TypeCode(v_tc);

	break;
    }

    case tk_Principal:
    {
	ostr_ << "<Principal>";

	break;
    }

    case tk_objref:
    {
        ostr_ << tc -> id();
        Object_ptr v_obj = dyn_any -> get_reference();
        if(CORBA::is_nil(v_obj))
            ostr_ << "<NULL>";

	break;
    }
    
    case tk_struct:
    {
        DynStruct_var dyn_struct =
	    DynStruct::_narrow(dyn_any);

        ostr_ << OB_ENDL;
        down();

        ULong member_count = tc -> member_count();
        for(i = 0 ; i < member_count ; i++)
	{
            String_var member_name = dyn_struct -> current_member_name();
            skip() << member_name << " = ";
            DynAny_var component = dyn_struct -> current_component();
            show_DynAny(component);
            ostr_ << OB_ENDL;
            dyn_struct -> next();  
        }

        up();
        skip();

	break;
    }

    case tk_union:
    {
        DynUnion_var dyn_union = DynUnion::_narrow(dyn_any);

        ostr_ << OB_ENDL;
        down();

        DynAny_var component = dyn_union -> current_component();

        skip() << "discriminator = ";
        show_DynAny(component);
        ostr_ << OB_ENDL;

        if(dyn_union -> component_count() == 2)
        {
            dyn_union -> next();

            component = dyn_union -> current_component();

            String_var member_name = dyn_union -> member_name();
            skip() << member_name << " = ";
            show_DynAny(component);

            ostr_ << OB_ENDL;
        }

        up();
        skip();

	break;
    }

    case tk_enum:
    {
         DynEnum_var dyn_enum = DynEnum::_narrow(dyn_any);
         String_var v_string = dyn_enum -> get_as_string();
         ostr_ << v_string;

	 break;   
    }

    case tk_string:
    {
        String_var v_string = dyn_any -> get_string();
        ostr_ << '"' << v_string << '"';

	break;
    }

    case tk_sequence:
    {
        DynSequence_var dyn_sequence = DynSequence::_narrow(dyn_any);
        for(i = 0 ; i < dyn_sequence -> get_length() ; i++)
	{
            if(i != 0) ostr_ << ", ";
            DynAny_var component = dyn_sequence -> current_component();
            show_DynAny(component);
            dyn_sequence -> next();
	}

	break;   
    }

    case tk_array:
    {
        DynArray_var dyn_array = DynArray::_narrow(dyn_any);
        for(i = 0 ; i < tc -> length() ; i++)
	{
            if(i != 0) ostr_ << ", ";
            DynAny_var component = dyn_array -> current_component();
	    show_DynAny(component);
	    dyn_array -> next();
	}

	break;   
    }

    case tk_alias:
    {
	ostr_ << "<alias>";

	break;
    }

    case tk_except:
    {
	ostr_ << "<except>";

	break;
    }

    case tk_longlong:
    {
        LongLong v_longlong = dyn_any -> get_longlong();
        String_var str = OB::LongLongToString(v_longlong);
        ostr_ << str;

	break;
    }

    case tk_ulonglong:
    {
        ULongLong v_ulonglong = dyn_any -> get_ulonglong();
        String_var str = OB::ULongLongToString(v_ulonglong);
        ostr_ << str;

	break;
    }

#if SIZEOF_LONG_DOUBLE >= 12
    case tk_longdouble:
    {
        LongDouble v_longdouble = dyn_any -> get_longdouble();
        //
        // Not all platforms support this
        //
        //ostr_ << v_longdouble;
        char str[25];
        sprintf(str, "%31Lg", v_longdouble);
        ostr_ << str;

	break;
    }
#endif

    case tk_wchar:
    {
        WChar v_wchar = dyn_any -> get_wchar();
	//
	// Output of narrowed wchar to narrow stream
	//
	ostr_ << "'" << (char)v_wchar << "' - narrowed";
	break;
    }

    case tk_wstring:
    {
        WString_var v_wstring = dyn_any -> get_wstring();
	//
	// Output of narrowed wstring to narrow stream
	//
	ostr_ << '"';
	for (CORBA::ULong i=0; i < OB::wcslen(v_wstring); i++)
	{
	    ostr_ << (char)v_wstring[i];
	}
	ostr_ <<  '"' << " - narrowed";

	break;
    }

    case tk_fixed:
    {
	DynFixed_var dyn_fixed = DynFixed::_narrow(dyn_any);

	ostr_ << OB_ENDL;
	down();

        String_var str = dyn_fixed -> get_value();
        skip() << str;

	ostr_ << OB_ENDL;

        up();
        skip();

	break;
    }

    case tk_value:
    {
	ostr_ << "<value>";

	break;
    }

    case tk_value_box:
    {
	ostr_ << "<value_box>";

	break;
    }

    case tk_native:
    {
	ostr_ << "<native>";

	break;
    }

    case tk_abstract_interface:
    {
	ostr_ << "<abstract_interface>";

	break;
    }

    default:
    {
	ostr_ << "Unknown DynAny: " <<  (int) kind;

	break;
    }
    }

    dyn_any -> rewind();
}

// ----------------------------------------------------------------------
// Show CORBA::Any
// ----------------------------------------------------------------------

void
CorbaOut::display_Any(const Any& any)
{
    DynAny_var dyn_any = factory_ -> create_dyn_any(any);
    display_DynAny(dyn_any);
}

void
CorbaOut::show_Any(const Any& any)
{
    DynAny_var dyn_any = factory_ -> create_dyn_any(any);
    show_DynAny(dyn_any);
}

