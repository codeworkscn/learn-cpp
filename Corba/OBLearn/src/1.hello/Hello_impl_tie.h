// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef HELLO_IMPL_TIE_H
#define HELLO_IMPL_TIE_H

class Hello_impl_tie
{
    CORBA::ORB_ptr orb_;

public:

    Hello_impl_tie(CORBA::ORB_ptr);

    virtual void say_hello();
    virtual void shutdown();
};

#endif
