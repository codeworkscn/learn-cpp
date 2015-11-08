// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _PIDemoDSI_impl_h_
#define _PIDemoDSI_impl_h_

#include <PIDemo.h>

//
// Servant implementing PIDemo using the Dynamic Skeleton
// Interface
//
class PIDemoDSI_impl : public PortableServer::DynamicImplementation,
		       public PortableServer::RefCountServantBase
{
    //
    // No copy constructor/assignment operator
    //
    PIDemoDSI_impl(const PIDemoDSI_impl&);
    void operator=(const PIDemoDSI_impl&);

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

    PIDemoDSI_impl(CORBA::ORB_ptr, PortableServer::POA_ptr);

    //
    // Set the reference to the object corresponding to the
    // static implementation
    //
    void setOtherObj(PIDemo_ptr);

    //
    // Methods for dynamic invocation
    //

    virtual CORBA::RepositoryId
    _primary_interface(const PortableServer::ObjectId&,
		       PortableServer::POA_ptr);

    virtual CORBA::Boolean
    _is_a(const char*)
	throw(CORBA::SystemException);

    virtual void
    invoke(CORBA::ServerRequest_ptr)
	throw();

    virtual PortableServer::POA_ptr
    _default_POA()
    {
        return PortableServer::POA::_duplicate(poa_);
    }
};

#endif
