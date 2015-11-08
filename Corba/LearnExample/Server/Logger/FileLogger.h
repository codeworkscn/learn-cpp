// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <OB/Logger.h>
#include <OB/LocalObject.h>
#include <stdio.h>

//
// This viewer class dumps output to a file in order to capture
// ORBacus diagnostic information. It's very important to use this
// class with the factory, since the factory expects STDOUT to be used
// for the IOR of the Hello server. No other data should be dumped to
// STDOUT during the execution of the server.
//
class FileLogger : public OB::Logger,
		   public OBCORBA::RefCountLocalObject
{
    FILE* fp_;

public:

    FileLogger(const char* file);
    ~FileLogger();

    virtual void info(const char*);
    virtual void error(const char*);
    virtual void warning(const char*);
    virtual void trace(const char*, const char*);
};

#endif
