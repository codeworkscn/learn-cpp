// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _LoggerPolicy_impl_h_
#define _LoggerPolicy_impl_h_

#include <LoggerPolicy.h>
#include <OB/LocalObject.h>

//
// Request interceptor logger policy
//
class LoggerPolicy_impl : 
    public LoggerPolicy,
    public OBCORBA::RefCountLocalObject
{
    //
    // No copy-constructor or assignment operator
    //
    LoggerPolicy_impl(const LoggerPolicy_impl&);
    void operator=(const LoggerPolicy_impl&);

    //
    // The log level
    //
    CORBA::Short level_;

public:

    LoggerPolicy_impl(CORBA::Short level);
    virtual ~LoggerPolicy_impl();

    //
    // IDL to C++ Mapping
    //

    virtual CORBA::Short level()
        throw(CORBA::SystemException);

    virtual CORBA::PolicyType policy_type()
        throw(CORBA::SystemException);

    virtual CORBA::Policy_ptr copy()
        throw(CORBA::SystemException);

    virtual void destroy()
        throw(CORBA::SystemException);
};

//
// Request interceptor logger policy factory
//
class LoggerPolicyFactory_impl : 
    public PortableInterceptor::PolicyFactory,
    public OBCORBA::RefCountLocalObject
{
public:

    //
    // IDL to C++ Mapping
    //

    virtual CORBA::Policy_ptr create_policy(CORBA::PolicyType type,
                                            const CORBA::Any& any)
	throw(CORBA::PolicyError);
};

#endif
