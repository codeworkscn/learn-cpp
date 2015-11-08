// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef HELLO_IMPL_H
#define HELLO_IMPL_H

#include <Hello_skel.h>

class Hello_impl : public POA_Hello,
		   public PortableServer::RefCountServantBase
{
    CORBA::ORB_var orb_;
    OCI::Current_var current_;

public:

    Hello_impl(CORBA::ORB_ptr, OCI::Current_ptr current);

    virtual void say_hello()
        throw(CORBA::SystemException);

    virtual void shutdown()
        throw(CORBA::SystemException);
};

#endif
