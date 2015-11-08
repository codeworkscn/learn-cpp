// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _PIDemo_impl_h_
#define _PIDemo_impl_h_

#include <PIDemo_skel.h>

//
// Servant implementing PIDemo using static skeletons
//
class PIDemo_impl : public POA_PIDemo,
		    public PortableServer::RefCountServantBase
{
    //
    // No copy constructor/assignment operator
    //
    PIDemo_impl(const PIDemo_impl&);
    void operator=(const PIDemo_impl&);

    //
    // My ORB
    //
    CORBA::ORB_var orb_;

    //
    // My POA
    //
    PortableServer::POA_var poa_;

    //
    // A reference to the object corresponding to the static
    // implementation (used by call_other_impl())
    //
    PIDemo_var otherObj_;

public:

    PIDemo_impl(CORBA::ORB_ptr, PortableServer::POA_ptr);

    //
    // Set the reference to the object corresponding to the
    // dynamic implementation
    //
    void setOtherObj(PIDemo_ptr);

    //
    // Standard IDL to C++ mapping
    //

    //
    // IDL:PIDemo/noargs:1.0
    //
    virtual void noargs()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/noargs_oneway:1.0
    //
    virtual void noargs_oneway()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/noargs_return:1.0
    //
    virtual char* noargs_return()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/withargs:1.0
    //
    virtual void withargs(const char*, char*&, CORBA::String_out)
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/systemexception:1.0
    //
    virtual void systemexception()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/userexception:1.0
    //
    virtual void userexception()
        throw(PIDemo::User, CORBA::SystemException);

    //
    // IDL:PIDemo/switch_to_static_impl:1.0
    //
    virtual void switch_to_static_impl()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/switch_to_dynamic_impl:1.0
    //
    virtual void switch_to_dynamic_impl()
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/call_other_impl:1.0
    //
    virtual void call_other_impl(CORBA::Short)
        throw(CORBA::SystemException);

    //
    // IDL:PIDemo/deactivate:1.0
    //
    virtual void deactivate()
        throw(CORBA::SystemException);

    virtual PortableServer::POA_ptr
    _default_POA()
    {
        return PortableServer::POA::_duplicate(poa_);
    }
};

#endif
