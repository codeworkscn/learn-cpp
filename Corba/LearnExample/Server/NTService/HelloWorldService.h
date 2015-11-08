// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef HELLO_WORLD_SERVICE_H
#define HELLO_WORLD_SERVICE_H

#define HELLO_MSG	0x00000000L

//
// This class defines a Hello World service. This is simple NT service
// that exposes a hello world server on port 12345.
//
class HelloWorldService : public OB::NTService
{
    
    bool stopped_;

    void orb_run(OB::Logger_ptr);

public:

    HelloWorldService();
    
    virtual void start(int, char**, OB::Logger_ptr);
    virtual void stop();
};

#endif
