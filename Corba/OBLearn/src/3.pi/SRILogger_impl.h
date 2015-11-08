// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _SRILogger_impl_h_
#define _SRILogger_impl_h_

//
// Server Request Interceptor logger -- logs server activity
//

class SRILogger_impl :
    public PortableInterceptor::ServerRequestInterceptor,
    public RILogger
{
    //
    // Get the logging level
    //
    CORBA::Short
    level(PortableInterceptor::ServerRequestInfo_ptr);

    //
    // Display PortableInterceptor::ServerRequestInfo
    //
    void displayServerRequestInfo(PortableInterceptor::ServerRequestInfo_ptr,
				  CORBA::Short);

public:

    SRILogger_impl(PortableInterceptor::ORBInitInfo_ptr,
		   PortableInterceptor::SlotId);
    ~SRILogger_impl();

    //
    // IDL to C++ Mapping
    //

    //
    // The name of the interceptor.
    //
    virtual char*
    name();

    virtual void
    destroy();

    //
    // At this interception point, Interceptors must get their service
    // context information from the incoming request and transfer it
    // to a slot of PortableInterceptor::Current.
    //
    virtual void
    receive_request_service_contexts(
    	PortableInterceptor::ServerRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query request
    // information after all the information, including operation
    // parameters, are available.
    //
    virtual void
    receive_request(PortableInterceptor::ServerRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);
    
    //
    // This interception point allows an Interceptor to query reply
    // information and modify the reply service context after the
    // target operation has been invoked and before the reply is
    // returned to the client.
    //
    virtual void
    send_reply(PortableInterceptor::ServerRequestInfo_ptr)
	throw(CORBA::SystemException);
    
    //
    // This interception point allows an Interceptor to query the
    // exception information and modify the reply service context
    // before the exception is raised to the client.
    //
    virtual void
    send_exception(PortableInterceptor::ServerRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query
    // the information available when a request results in
    // something other thatn a normal reply or an exception.
    //
    virtual void
    send_other(PortableInterceptor::ServerRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);
};

#endif
