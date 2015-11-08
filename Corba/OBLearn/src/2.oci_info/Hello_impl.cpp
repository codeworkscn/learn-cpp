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
#include <OB/OCI_IIOP.h>

#include <Hello_impl.h>
#include <stdio.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

// ----------------------------------------------------------------------
// Hello_impl constructor
// ----------------------------------------------------------------------

Hello_impl::Hello_impl(CORBA::ORB_ptr orb, OCI::Current_ptr current)
    : orb_(CORBA::ORB::_duplicate(orb)),
      current_(OCI::Current::_duplicate(current))
{
}

// ----------------------------------------------------------------------
// Hello_impl public member implementation
// ----------------------------------------------------------------------

void
Hello_impl::say_hello()
    throw(CORBA::SystemException)
{
    cout << "Hello_impl::hello()" << endl;

    OCI::TransportInfo_var info = current_ -> get_oci_transport_info();
    OCI::IIOP::TransportInfo_var iiopInfo =
	OCI::IIOP::TransportInfo::_narrow(info);

    if(!CORBA::is_nil(iiopInfo))
    {
        OCI::IIOP::InetAddr_var remoteAddr = iiopInfo -> remote_addr();
        CORBA::UShort remotePort = iiopInfo -> remote_port();

	cout << "Call from: "
	     << remoteAddr << ':'
	     << remotePort << endl;
    }
}

void
Hello_impl::shutdown()
    throw(CORBA::SystemException)
{
    orb_ -> shutdown(false);
}