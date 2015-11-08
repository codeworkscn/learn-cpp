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
#include <Hello_impl_tie.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

Hello_impl_tie::Hello_impl_tie(CORBA::ORB_ptr orb)
    : orb_(CORBA::ORB::_duplicate(orb))
{
}

void
Hello_impl_tie::say_hello()
{
    cout << "Hello World!" << endl;
}

void
Hello_impl_tie::shutdown()
{
    orb_ -> shutdown(false);
}
