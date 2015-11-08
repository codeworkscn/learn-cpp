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

#include "FileLogger.h"

#include <stdio.h>
#include <time.h>
#include <errno.h>

// ----------------------------------------------------------------------
// FileLogger constructor/destructor
// ----------------------------------------------------------------------

FileLogger::FileLogger(const char* file)
{
    fp_ = fopen(file, "a");
    assert(fp_ != 0);
}
    
FileLogger::~FileLogger()
{
    fclose(fp_);
}

// ----------------------------------------------------------------------
// FileLogger public member implementation
// ----------------------------------------------------------------------

void
FileLogger::info(const char* msg)
{
    time_t now = time(0);
    struct tm* tm = localtime(&now);
    char tbuf[128];
    strftime(tbuf, sizeof(tbuf), "%c", tm);
    fprintf(fp_, "%s: %s\n", tbuf, msg);
    fflush(fp_);
}

void
FileLogger::error(const char* msg)
{
    time_t now = time(0);
    struct tm* tm = localtime(&now);
    char tbuf[128];
    strftime(tbuf, sizeof(tbuf), "%c", tm);
    fprintf(fp_, "%s: ERROR: %s\n", tbuf, msg);
    fflush(fp_);
}

void
FileLogger::warning(const char* msg)
{
    time_t now = time(0);
    struct tm* tm = localtime(&now);
    char tbuf[128];
    strftime(tbuf, sizeof(tbuf), "%c", tm);
    fprintf(fp_, "%s: WARNING: %s\n", tbuf, msg);
    fflush(fp_);
}

void
FileLogger::trace(const char* category, const char* msg)
{
    time_t now = time(0);
    struct tm* tm = localtime(&now);
    char tbuf[128];
    strftime(tbuf, sizeof(tbuf), "%c", tm);
    fprintf(fp_, "%s: %s: %s\n", tbuf, category, msg);
    fflush(fp_);
}
