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
#include <SRILogger_impl.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

// ---------------------------------------------------------------------
// SRILogger private member implementation
// ---------------------------------------------------------------------

CORBA::Short
SRILogger_impl::level(PortableInterceptor::ServerRequestInfo_ptr ri)
{
    CORBA::Short l = 0;

    try
    {
	//
	// Get the logger policy
	//
	CORBA::Policy_var policy = ri -> get_server_policy(LOGGER_POLICY_ID);
	LoggerPolicy_var loggerPolicy = LoggerPolicy::_narrow(policy);
	if(!CORBA::is_nil(loggerPolicy))
	    l = loggerPolicy -> level();
    }
    catch(...)
    {
    }

    return l;
}

void
SRILogger_impl::displayServerRequestInfo(
    PortableInterceptor::ServerRequestInfo_ptr info,
    CORBA::Short logLevel)
{
    CORBA::ULong i;

    displayRequestInfo(info, logLevel);

    //
    // Display sending exception
    //
    try
    {
	CORBA::Any_var exception = info -> sending_exception();

	out_ -> skip();
    	cout << "sending exception = " << endl;
	out_ -> down();
	out_ -> display_Any(exception);
	out_ -> up();
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }

    if(logLevel > 2)
    {
	//
	// Display object id
	//
	try
	{
	    CORBA::OctetSeq_var octets = info -> object_id();

	    out_ -> skip();
	    cout << "object id = ";

	    for (i = 0 ; i < octets -> length() ; i++)
		cout << CORBA::String_var(getOctet(octets[i]));
	    cout << endl;
	}
	catch(const CORBA::BAD_INV_ORDER&)
	{
	    // Operation not supported in this context
	}

	//
	// Display adapter id
	//
	try
	{
	    CORBA::OctetSeq_var octets = info -> adapter_id();

	    out_ -> skip();
	    cout << "adapter id = ";

	    for (i = 0 ; i < octets -> length() ; i++)
		cout << CORBA::String_var(getOctet(octets[i]));
	    cout << endl;
	}
	catch(const CORBA::BAD_INV_ORDER&)
	{
	    // Operation not supported in this context
	}
    }

    //
    // Display target most derived interface
    //
    try
    {
	CORBA::RepositoryId_var tmdi = info -> target_most_derived_interface();

	out_ -> skip();
    	cout << "target most derived interface = " << tmdi << endl;
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }
}

// ---------------------------------------------------------------------
// SRILogger constructor/destructor
// ---------------------------------------------------------------------

SRILogger_impl::SRILogger_impl(PortableInterceptor::ORBInitInfo_ptr info,
			       PortableInterceptor::SlotId slotId)
    : RILogger(info, slotId)
{
}

SRILogger_impl::~SRILogger_impl()
{
}

// ----------------------------------------------------------------------
// IDL to C++ Mapping
// ----------------------------------------------------------------------

char*
SRILogger_impl::name()
{
    return CORBA::string_dup("SRILogger");
}

void
SRILogger_impl::destroy()
{
}

void
SRILogger_impl::receive_request_service_contexts(
    PortableInterceptor::ServerRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "receive request service contexts:" << endl;
        displayServerRequestInfo(ri, l);
	cout << endl;

	//
	// Get CallStack from service context
	//
	CallStack callStack(0);
	try
	{
	    //
	    // Get encoded CallStack from service context
	    //
	    IOP::ServiceContext_var sc =
		ri -> get_request_service_context(REQUEST_CONTEXT_ID);

	    //
	    // Decode CallStack
	    //
	    CORBA::Any_var any;
	    CORBA::OctetSeq data(sc -> context_data.length());
	    data.length(sc -> context_data.length());
	    memcpy(data.get_buffer(), sc -> context_data.get_buffer(),
		   sc -> context_data.length());
	    try
	    {
		any = cdrCodec_ -> decode_value(data, _tc_CallStack);
	    }
	    catch(const IOP::Codec::TypeMismatch&)
	    {
		//
		// Ignore failure in this demo
		//
		return;
	    }
	    catch(const IOP::Codec::FormatMismatch&)
	    {
		//
		// Ignore failure in this demo
		//
		return;
	    }

	    const CallStack* stack = 0;
	    if(!(any >>= stack))
	    {
		//
		// Ignore failure in this demo
		//
		return;
	    }
	    assert(stack);

	    //
	    // Set length of new CallStack to the length of
	    // the old CallStack, plus one for the new call
	    //
	    callStack.length(stack -> length() + 1);

	    //
	    // Copy old CallStack to new CallStack
	    //
	    for(CORBA::ULong i = 0 ; i < stack -> length() ; i++)
		callStack[i] = (*stack)[i];
	}
	catch(const CORBA::BAD_PARAM&)
	{
	    //
	    // Service context was not previously set -- set length
	    // of the new CallStack to one for the new call
	    //
	    callStack.length(1);
	}

	//
	// Add new call to the CallStack
	//
	CORBA::String_var op(ri -> operation());
	callStack[callStack.length() - 1] = op;
	    
	//
	// Save the new CallStack in slot
	//
	CORBA::Any any;
	any <<= callStack;
	try
	{
	    ri -> set_slot(mySlotId_, any);
	}
	catch(const PortableInterceptor::InvalidSlot&)
	{
	    //
	    // Ignore failure in this demo
	    //
	    return;
	}

	//
	// Print the CallStack
	//
	out_ -> skip();
	cout << "stack =" << endl;
	out_ -> down();
	for(CORBA::ULong i = 0 ; i < callStack.length() ; i++)
	{
	    out_ -> skip();
	    cout << (i + 1) << ".\t" << callStack[i] << endl;
	}
	out_ -> up();
	cout << endl;
    }
}

void
SRILogger_impl::receive_request(
    PortableInterceptor::ServerRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "receive request:" << endl;
        displayServerRequestInfo(ri, l);
	cout << endl;
    }
}
    
void
SRILogger_impl::send_reply(
    PortableInterceptor::ServerRequestInfo_ptr ri)
    throw(CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "send reply:" << endl;
        displayServerRequestInfo(ri, l);
	cout << endl;
    }
}
    
void
SRILogger_impl::send_other(
    PortableInterceptor::ServerRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "send other:" << endl;
        displayServerRequestInfo(ri, l);
	cout << endl;
    }
}

void
SRILogger_impl::send_exception(
    PortableInterceptor::ServerRequestInfo_ptr ri)
    throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
    CORBA::Short l = level(ri);
    if(l > 0)
    {
	cout << "send exception:" << endl;
        displayServerRequestInfo(ri, l);
	cout << endl;
    }
}

