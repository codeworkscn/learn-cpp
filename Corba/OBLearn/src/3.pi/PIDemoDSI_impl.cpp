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

#include <PIDemoDSI_impl.h>

// ----------------------------------------------------------------------
// PIDemoDSI_impl constructor and destructor
// ----------------------------------------------------------------------

PIDemoDSI_impl::PIDemoDSI_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : orb_(CORBA::ORB::_duplicate(orb)),
      poa_(PortableServer::POA::_duplicate(poa))
{
}

// ----------------------------------------------------------------------
// PIDemoDSI_impl public member implementation
// ----------------------------------------------------------------------

void
PIDemoDSI_impl::setOtherObj(PIDemo_ptr obj)
{
    otherObj_ = PIDemo::_duplicate(obj);
}

CORBA::RepositoryId
PIDemoDSI_impl::_primary_interface(const PortableServer::ObjectId& /* oid */,
				   PortableServer::POA_ptr /* poa */)
{
    return CORBA::string_dup("IDL:PIDemo:1.0");
}

CORBA::Boolean
PIDemoDSI_impl::_is_a(const char* name)
    throw(CORBA::SystemException)
{
    if(strcmp(name, "IDL:PIDemo:1.0") == 0)
	return true;

#ifdef HAVE_VCPLUSPLUS_BUGS
    return ServantBase::_is_a(name);
#else
    return ::PortableServer::ServantBase::_is_a(name);
#endif
}

void
PIDemoDSI_impl::invoke(CORBA::ServerRequest_ptr request)
    throw()
{
    CORBA::String_var name = request -> operation();

    if(strcmp(name, "noargs") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

	return;
    }

    if(strcmp(name, "noargs_oneway") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

	return;
    }

    if(strcmp(name, "noargs_return") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

        CORBA::Any result;
        result <<= "PIDemoDSI";
        request -> set_result(result);

	return;
    }

    if(strcmp(name, "withargs") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
        list -> add(CORBA::ARG_IN) -> value() ->
	    replace(CORBA::_tc_string, 0);
        list -> add(CORBA::ARG_INOUT) -> value() ->
	    replace(CORBA::_tc_string, 0);
        list -> add(CORBA::ARG_OUT) -> value() ->
	    replace(CORBA::_tc_string, 0);
	request -> arguments(list);

        CORBA::Any* any;

        any = list -> item(1) -> value();
        *any <<= "PIDemoDSI";

        any = list -> item(2) -> value();
        *any <<= "PIDemoDSI";

	return;
    }

    if(strcmp(name, "systemexception") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

        CORBA::Any result;
        result <<= CORBA::NO_IMPLEMENT();
        request -> set_exception(result);

        return;
    }


    if(strcmp(name, "userexception") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

        CORBA::Any result;
        result <<= PIDemo::User();
        request -> set_exception(result);

        return;
    }

    if(strcmp(name, "switch_to_static_impl") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

        return;
    }

    if(strcmp(name, "switch_to_dynamic_impl") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
	request -> arguments(list);

        return;
    }

    if(strcmp(name, "call_other_impl") == 0)
    {
	CORBA::NVList_ptr list;
	orb_ -> create_list(0, list);
        list -> add(CORBA::ARG_IN) -> value() ->
	    replace(CORBA::_tc_short, 0);
	request -> arguments(list);

        CORBA::Any* any;
        any = list -> item(0) -> value();
	CORBA::Short level;
        if(!(*any >>= level))
	{
	    CORBA::Any result;
	    result <<= CORBA::BAD_PARAM();
	    request -> set_exception(result);

	    return;
	}
	    
	if(!CORBA::is_nil(otherObj_) && level > 0)
	    otherObj_ -> call_other_impl(--level);

        return;
    }

    if(strcmp(name, "deactivate") == 0)
    {
	CORBA::NVList_ptr list;

	orb_ -> create_list(0, list);
	request -> arguments(list);

        orb_ -> shutdown(false);

	return;
    }

    CORBA::NVList_ptr list;
    orb_ -> create_list(0, list);
    request -> arguments(list);
    
    CORBA::Any exAny;
    exAny <<= new CORBA::BAD_OPERATION();
    request -> set_exception(exAny);
}

