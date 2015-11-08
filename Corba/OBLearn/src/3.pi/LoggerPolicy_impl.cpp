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
#include <OB/PortableInterceptor.h>

#include <LoggerPolicy_impl.h>

// ----------------------------------------------------------------------
// LoggerPolicy constructor/destructor
// ----------------------------------------------------------------------

LoggerPolicy_impl::LoggerPolicy_impl(CORBA::Short level)
    : level_(level)
{
}

LoggerPolicy_impl::~LoggerPolicy_impl()
{
}

// ----------------------------------------------------------------------
// LoggerPolicy IDL to C++ Mapping
// ----------------------------------------------------------------------

CORBA::Short
LoggerPolicy_impl::level()
    throw(CORBA::SystemException)
{
    return level_;
}

CORBA::PolicyType
LoggerPolicy_impl::policy_type()
    throw(CORBA::SystemException)
{
    return LOGGER_POLICY_ID;
}

CORBA::Policy_ptr
LoggerPolicy_impl::copy()
    throw(CORBA::SystemException)
{
    return CORBA::Policy::_duplicate(this);
}

void
LoggerPolicy_impl::destroy()
    throw(CORBA::SystemException)
{
}

// ----------------------------------------------------------------------
// LoggerPolicyFactory IDL to C++ Mapping
// ----------------------------------------------------------------------

CORBA::Policy_ptr
LoggerPolicyFactory_impl::create_policy(CORBA::PolicyType type,
					const CORBA::Any& any)
    throw(CORBA::PolicyError)
{
    if(type == LOGGER_POLICY_ID)
    {
	CORBA::Short level;
	if(any >>= level)
	    return new LoggerPolicy_impl(level);
	throw CORBA::PolicyError(CORBA::BAD_POLICY_TYPE);
    }
    throw CORBA::PolicyError(CORBA::BAD_POLICY);
    return CORBA::Policy::_nil(); // Some compilers need this
}

