// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _CRILogger_impl_h_
#define _CRILogger_impl_h_

//
// Client Request Interceptor logger -- logs client activity
//
class CRILogger_impl :
    public PortableInterceptor::ClientRequestInterceptor,
    public RILogger
{
    //
    // Get the logging level
    //
    CORBA::Short
    level(PortableInterceptor::ClientRequestInfo_ptr);

    //
    // Display PortableInterceptor::ClientRequestInfo
    //
    void displayClientRequestInfo(PortableInterceptor::ClientRequestInfo_ptr,
				  CORBA::Short);

public:

    CRILogger_impl(PortableInterceptor::ORBInitInfo_ptr,
		   PortableInterceptor::SlotId);
    ~CRILogger_impl();

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
    // This interception point allows an Interceptor to query request
    // information and modify the service context before the request
    // is sent.
    //
    virtual void
    send_request(PortableInterceptor::ClientRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query
    // information during a TimeIndependent Infocation (TII)
    // polling get reply sequence.
    //
    virtual void
    send_poll(PortableInterceptor::ClientRequestInfo_ptr)
	throw(CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query
    // the information on a reply after it is returned from the
    // server and before control is returned to the client.
    // 
    virtual void
    receive_reply(PortableInterceptor::ClientRequestInfo_ptr)
	throw(CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query
    // the exception information before the exception is raised
    // to the client.
    //
    virtual void
    receive_exception(PortableInterceptor::ClientRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

    //
    // This interception point allows an Interceptor to query
    // the information available when a request results in
    // something other thatn a normal reply or an exception.
    //
    virtual void
    receive_other(PortableInterceptor::ClientRequestInfo_ptr)
	throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);
};

#endif
