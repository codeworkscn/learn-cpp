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
#include <CorbaOut.h>
#include <RILogger.h>
#include <CRILogger_impl.h>
#include <SRILogger_impl.h>

#include <stdio.h> // For sprintf()

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

//
// ORB Initializer for the server and client request interceptors
//
class RIORBInitializer_impl : 
    public PortableInterceptor::ORBInitializer,
    public OBCORBA::RefCountLocalObject
{
public:

    //
    // IDL to C++ Mapping
    //
    virtual void
    pre_init(PortableInterceptor::ORBInitInfo_ptr)
    {
    }

    //
    // Note: the interceptors are registered in post_init()
    //       because the CRILogger_impl and SRILogger_impl
    //       constructors require
    //       ORBInitInfo::resolve_initial_reference(), which
    //       cannot be called in pre_init().
    //
    virtual void
    post_init(PortableInterceptor::ORBInitInfo_ptr info)
    {
	//
	// Register the policy factory
	//
	PortableInterceptor::PolicyFactory_var pf =
	    new LoggerPolicyFactory_impl;
	info -> register_policy_factory(LOGGER_POLICY_ID, pf);

	//
	// Allocate state slot for call stack tracing
	//
	PortableInterceptor::SlotId slotId = info -> allocate_slot_id();

	//
	// Create the interceptors
	//
	PortableInterceptor::ClientRequestInterceptor_var
	    clientInterceptor = new CRILogger_impl(info, slotId);
	PortableInterceptor::ServerRequestInterceptor_var
	    serverInterceptor = new SRILogger_impl(info, slotId);

	//
	// Register the interceptors
	//
	try
	{
	    info -> add_client_request_interceptor(clientInterceptor);
	    info -> add_server_request_interceptor(serverInterceptor);
	}
	catch(const PortableInterceptor::ORBInitInfo::DuplicateName&)
	{
	    assert(false);
	}
    }
};

// ---------------------------------------------------------------------
// RILogger private member implementation
// ---------------------------------------------------------------------

char*
RILogger::getOctet(CORBA::Octet oct)
{
    char str[5];
    sprintf(str, "<%02X>", oct);

    return CORBA::string_dup(str);
}

void
RILogger::displayRequestInfo(
    PortableInterceptor::RequestInfo_ptr info,
    CORBA::Short logLevel)
{
    CORBA::ULong i;

    //
    // Display request id
    //
    CORBA::ULong request_id = info -> request_id();
    out_ -> skip();
    cout << "request id = " << request_id << endl;

    //
    // Display operation
    //
    CORBA::String_var operation = info -> operation();
    out_ -> skip();
    cout << "operation = " <<  operation << endl;

    //
    // Display arguments
    //
    try
    {
	Dynamic::ParameterList_var args = info -> arguments();

	out_ -> skip();
	cout << "arguments = ";
	if (args -> length() == 0)
	{
	    cout << "(no arguments)";
	}
	else
	{
	    out_ -> down();
	    for (i = 0 ; i < args -> length() ; i++)
	    {
		cout << endl;
		switch(args[i].mode)
		{
		case CORBA::PARAM_IN:
		    out_ -> skip();
		    cout <<  "in ";
		    break;
		case CORBA::PARAM_OUT:
		    out_ -> skip();
		    cout <<  "out ";
		    break;
		default: // case PARAM_INOUT:
		    out_ -> skip();
		    cout <<  "inout ";
		    break;
		}
		out_ -> show_Any(args[i].argument);
	    }
	    out_ -> up();
	}
	cout << endl;
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }
    catch(const CORBA::NO_RESOURCES&)
    {
	// Operation not supported in this environment
    }

    //
    // Display exceptions
    //
    try
    {
	Dynamic::ExceptionList_var exceptions = info -> exceptions();

	out_ -> skip();
	cout << "exceptions = ";
	if (exceptions -> length() == 0)
	{
	    cout << "(no exceptions)" << endl;
	}
	else
	{
	    cout << endl;
	    out_ -> down();
	    for (i = 0 ; i < exceptions -> length() ; i++)
		out_ -> display_IDL_TypeCode(exceptions[i]);
	    out_ -> up();
	}
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }
    catch(const CORBA::NO_RESOURCES&)
    {
	// Operation not supported in this environment
    }
    
    //
    // Display result
    //
    try
    {
	CORBA::Any_var result = info -> result();

	out_ -> skip();
	cout << "result = ";
	out_ -> show_Any(result);
	cout << endl;
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }
    catch(const CORBA::NO_RESOURCES&)
    {
	// Operation not supported in this environment
    }

    //
    // Display response expected
    //
    bool response_expected = info -> response_expected();

    out_ -> skip();
    cout << "response expected = ";
    if (response_expected)
	cout << "true";
    else
	cout << "false";
    cout << endl;

    //
    // Display reply status
    //
    try
    {
	PortableInterceptor::ReplyStatus status = info -> reply_status();

	out_ -> skip();
	cout << "reply status = ";
	if (status == PortableInterceptor::SUCCESSFUL)
	    cout << "SUCCESSFUL";
	else if (status == PortableInterceptor::SYSTEM_EXCEPTION)
	    cout << "SYSTEM_EXCEPTION";
	else if (status == PortableInterceptor::USER_EXCEPTION)
	    cout << "USER_EXCEPTION";
	else if (status == PortableInterceptor::LOCATION_FORWARD)
	    cout << "LOCATION_FORWARD";
	else if (status == PortableInterceptor::TRANSPORT_RETRY)
	    cout << "TRANSPORT_RETRY";
	else
	    cout << "UNKNOWN_REPLY_STATUS";
	cout << endl;
    }
    catch(const CORBA::BAD_INV_ORDER&)
    {
	// Operation not supported in this context
    }

    if(logLevel > 1)
    {
	//
	// Display slot data
	//
	try
	{
	    CORBA::Any_var slotData = info -> get_slot(mySlotId_);

	    out_ -> skip();
	    cout << "slot data " << mySlotId_ << " = " << endl;
	    out_ -> down();
	    out_ -> display_Any(slotData);
	    out_ -> up();
	}
	catch(const PortableInterceptor::InvalidSlot&)
	{
	}

	//
	// Display request service context
	//
	try
	{
	    IOP::ServiceContext_var context =
		info -> get_request_service_context(REQUEST_CONTEXT_ID);

	    out_ -> skip();
	    cout << "request service context " << REQUEST_CONTEXT_ID << " = ";

	    for (i = 0 ; i < context -> context_data.length() ; i++)
		cout << CORBA::String_var(getOctet(context -> context_data[i]));
	    cout << endl;
	}
	catch(const CORBA::BAD_INV_ORDER&)
	{
	    // Operation not supported in this context
	}
	catch(const CORBA::BAD_PARAM&)
	{
	    // No entry found
	}

	//
	// Display reply service context
	//
	try
	{
	    IOP::ServiceContext_var context =
		info -> get_reply_service_context(REPLY_CONTEXT_ID);

	    out_ -> skip();
	    cout << "reply service context " << REPLY_CONTEXT_ID << " = ";

	    for (i = 0 ; i < context -> context_data.length() ; i++)
		cout << CORBA::String_var(getOctet(context -> context_data[i]));
	    cout << endl;
	}
	catch(const CORBA::BAD_INV_ORDER&)
	{
	    // Operation not supported in this context
	}
	catch(const CORBA::BAD_PARAM&)
	{
	    // No entry found
	}
    }
}

// ---------------------------------------------------------------------
// RILogger constructor/destructor
// ---------------------------------------------------------------------

RILogger::RILogger(PortableInterceptor::ORBInitInfo_ptr info,
		   PortableInterceptor::SlotId slotId)
    : REQUEST_CONTEXT_ID(100),
      REPLY_CONTEXT_ID(101),
      mySlotId_(slotId)
{
    //
    // Get the codec factory
    //
    IOP::CodecFactory_var factory = info -> codec_factory();
    assert(!CORBA::is_nil(factory));

    //
    // Create codec
    //
    IOP::Encoding how;
    how.major_version = 1;
    how.minor_version = 0;
    how.format = IOP::ENCODING_CDR_ENCAPS;

    try
    {
	cdrCodec_ = factory -> create_codec(how);
    }
    catch(const IOP::CodecFactory::UnknownEncoding&)
    {
	assert(false);
    }
    assert(!CORBA::is_nil(cdrCodec_));

    //
    // Get the dynamic any factory
    //
    DynamicAny::DynAnyFactory_var dynAnyFactory;
    try
    {
	CORBA::Object_var obj =
	    info -> resolve_initial_references("DynAnyFactory");
	dynAnyFactory = DynamicAny::DynAnyFactory::_narrow(obj);
    }
    catch(const PortableInterceptor::ORBInitInfo::InvalidName&)
    {
	assert(false);
    }
    assert(!CORBA::is_nil(dynAnyFactory));

    //
    // Create the CorbaOut object for displaying the CORBA::Any
    //
    out_ = new CorbaOut(dynAnyFactory, cout);
    out_ -> down();
}

RILogger::~RILogger()
{
    delete out_;
}

// ---------------------------------------------------------------------
// RILogger public member implementation
// ---------------------------------------------------------------------

void
RILogger::init()
{
    //
    // Register the ORB initializer
    //
    PortableInterceptor::ORBInitializer_var initializer =
	new RIORBInitializer_impl();
    PortableInterceptor::register_orb_initializer(initializer);
}
