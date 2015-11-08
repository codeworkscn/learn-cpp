// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef __corba_out_h__
#define __corba_out_h__

// ---------------------------------------------------------------------
// A class to display various CORBA types
// ---------------------------------------------------------------------

class CorbaOut
{
    DynamicAny::DynAnyFactory_var factory_;
    OB_STD(ostream)& ostr_;
    int level_;

protected:

    char* getOctet(CORBA::Octet oct);

public:

    //
    // Constructor/destructor
    //
    CorbaOut(DynamicAny::DynAnyFactory_ptr, OB_STD(ostream)&);
    ~CorbaOut();
    
    //
    // Manage level
    //
    void down() { level_ ++; };
    void up() { level_ --; };
    OB_STD(ostream)& skip();
    
    
    //
    // Display types
    //
    void display_IDL_TypeCode(CORBA::TypeCode_ptr);
    void show_name_TypeCode(CORBA::TypeCode_ptr);
    
    void display_DynAny(DynamicAny::DynAny_ptr);
    void show_DynAny_without_type(DynamicAny::DynAny_ptr);
    void show_DynAny(DynamicAny::DynAny_ptr);

    void display_Any(const CORBA::Any&);
    void show_Any(const CORBA::Any&);

};

#endif // __corba_out_h__
