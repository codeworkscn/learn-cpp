// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef _RILogger_h_
#define _RILogger_h_

#include <OB/LocalObject.h>

#include <CorbaOut.h>

//
// Request interceptor logger base class
//
class RILogger : public OBCORBA::RefCountLocalObject
{
protected:

    //
    // Service context identifiers
    //
    const IOP::ServiceId REQUEST_CONTEXT_ID;
    const IOP::ServiceId REPLY_CONTEXT_ID;

    //
    // Used to display CORBA::Any
    //
    CorbaOut* out_;

    //
    // Used to encode/decode the call stack information so that
    // it can be used as the service context
    //
    IOP::Codec_var cdrCodec_;

    //
    // My slot id
    //
    PortableInterceptor::SlotId mySlotId_;

    //
    // Convert CORBA::Octet to string
    //
    char* getOctet(CORBA::Octet);

    //
    // Display PortableInterceptor::RequestInfo
    //
    void displayRequestInfo(PortableInterceptor::RequestInfo_ptr,
			    CORBA::Short);

public:

    RILogger(PortableInterceptor::ORBInitInfo_ptr,
	     PortableInterceptor::SlotId);
    virtual ~RILogger();

    //
    // Register the Request Interceptor loggers
    //
    static void init();
};

#endif
