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

#include <CallStack.h>
#include <LoggerPolicy_impl.h>
#include <CorbaOut.h>
#include <RILogger.h>
#include <CRILogger_impl.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

// ---------------------------------------------------------------------
// CRILogger private member implementation
// ---------------------------------------------------------------------

CORBA::Short
CRILogger_impl::level(PortableInterceptor::ClientRequestInfo_ptr ri)
{
    CORBA::Short l = 0;

    try
    {
	//
	// Get the logger policy
	//
	CORBA::Policy_var policy = ri -> get_request_policy(LOGGER_POLICY_ID);
	LoggerPolicy_var loggerPolicy = LoggerPolicy::_narrow(policy);
	if(!CORBA::is_nil(loggerPolicy))
	    l = loggerPolicy -> level();
    }
    catch(const CORBA::INV_POLICY&)
    {
    }

    return l;
}

void
CRILogger_impl::displayClientRequestInfo(
    PortableInterceptor::ClientRequestInfo_ptr info,
    CORBA::Short logLevel)
{
    CORBA::ULong i;

    displayRequestInfo(info, logLevel);

    if(logLevel > 2)
    {
	//
	// Display effective profile
	//
	IOP::TaggedProfile_var profile = info -> effective_profile();

	out_ -> skip();
	cout << "effective profile = ";
	if (profile -> tag == IOP::TAG_INTERNET_IOP)
	    cout << "TAG_INTERNET_IOP";
	else if (profile -> tag == IOP::TAG_MULTIPLE_COMPONENTS)
	    cout << "TAG_MULTIPLE_COMPONENTS";
	else
	    cout << "UNKNOWN_TAG";
	cout << ": ";

	for (i = 0 ; i < profile -> profile_data.length() ; i++)
	    cout << CORBA::String_var(getOctet(profile -> profile_data[i]));
	cout << endl;
    }

    //
    // Display received exception
    //
    try
    {
	CORBA::Any_var exception = info -> received_exception();

	out_ -> skip();
    	cout << "received exception = " << endl;
	out_ -> down();
	out_ -> display_Any(exception);
	out_ -> up();
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }

    //
    // Display received exception id
    //
    try
    {
	CORBA::RepositoryId_var exception_id = info -> received_exception_id();

	out_ -> skip();
    	cout << "received exception id = " << exception_id << endl;
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }
}

// ---------------------------------------------------------------------
// CRILogger constructor/destructor
// ---------------------------------------------------------------------

CRILogger_impl::CRILogger_impl(PortableInterceptor::ORBInitInfo_ptr info,
			       PortableInterceptor::SlotId slotId)
    : RILogger(info, slotId)
{
}

CRILogger_impl::~CRILogger_impl()
{
}

// ----------------------------------------------------------------------
// IDL to C++ Mapping
// ----------------------------------------------------------------------

char*
CRILogger_impl::name()
{
    return CORBA::string_dup("CRILogger");
}

void
CRILogger_impl::destroy()
{
}

void
CRILogger_impl::send_request(PortableInterceptor::ClientRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	//
	// Try to get the CallStack from slot
	//
	try
	{
	    CORBA::Any_var any = ri -> get_slot(mySlotId_);
	    CORBA::TypeCode_var tc = any -> type();
	    if(tc -> kind() != CORBA::tk_null)
	    {
		//
		// Encode CallStack
		//
		CORBA::OctetSeq_var data = cdrCodec_ -> encode_value(any);

		//
		// Add encoded CallStack to service context
		//
		IOP::ServiceContext sc;
		sc.context_id = REQUEST_CONTEXT_ID;
		sc.context_data.length(data -> length());
		memcpy(sc.context_data.get_buffer(), data -> get_buffer(),
		       data -> length());
		ri -> add_request_service_context(sc, false);
	    }
	}
	catch(const PortableInterceptor::InvalidSlot&)
	{
	    // Ignore failure in this demo
	}
	catch(const IOP::Codec::InvalidTypeForEncoding&)
	{
	    // Ignore failure in this demo
	}

	cout << "send request:" << endl;
        displayClientRequestInfo(ri, l);
	cout << endl;
    }
}

void
CRILogger_impl::send_poll(PortableInterceptor::ClientRequestInfo_ptr ri)
    throw(CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "send poll:" << endl;
        displayClientRequestInfo(ri, l);
	cout << endl;
    }
}

void
CRILogger_impl::receive_reply(PortableInterceptor::ClientRequestInfo_ptr ri)
    throw(CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "receive reply:" << endl;
        displayClientRequestInfo(ri, l);
	cout << endl;
    }
}

void
CRILogger_impl::receive_other(PortableInterceptor::ClientRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "receive other:" << endl;
        displayClientRequestInfo(ri, l);
	cout << endl;
    }
}

void
CRILogger_impl::receive_exception(PortableInterceptor::ClientRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "receive exception:" << endl;
        displayClientRequestInfo(ri, l);
	cout << endl;
    }
}

