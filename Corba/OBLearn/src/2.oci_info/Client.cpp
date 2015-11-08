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
#include <OB/LocalObject.h>

#include <Hello.h>

#include <stdlib.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

class CloseCB_impl : public OCI::CloseCB,
		     public OBCORBA::RefCountLocalObject
{
public:

    virtual void close_cb(OCI::TransportInfo_ptr transport_info)
    {
        OCI::IIOP::TransportInfo_var iiopInfo =
            OCI::IIOP::TransportInfo::_narrow(transport_info);

        if(!CORBA::is_nil(iiopInfo))
        {
            OCI::IIOP::InetAddr_var remoteAddr = iiopInfo -> remote_addr();
            CORBA::UShort remotePort = iiopInfo -> remote_port();

            cout << "Closing connection to: "
                 << remoteAddr << ':'
                 << remotePort << endl;
        }
    }
};

class ConnectCB_impl : public OCI::ConnectCB,
		       public OBCORBA::RefCountLocalObject
{
public:

    virtual void connect_cb(OCI::TransportInfo_ptr transport_info)
    {
        OCI::IIOP::TransportInfo_var iiopInfo =
            OCI::IIOP::TransportInfo::_narrow(transport_info);

        if(!CORBA::is_nil(iiopInfo))
        {
            OCI::IIOP::InetAddr_var remoteAddr = iiopInfo -> remote_addr();
            CORBA::UShort remotePort = iiopInfo -> remote_port();

            cout << "Connection to: "
                 << remoteAddr << ':'
                 << remotePort << endl;

            char c;
            do
            {
                cout << "Refuse connection (y/n)? ";
                cin >> c;
            }
            while(c != 'y' && c != 'n');

            if(c == 'y')
                throw CORBA::NO_PERMISSION();

            //
            // Add the close callback object
            //
            OCI::CloseCB_var closeCB = new CloseCB_impl();
            iiopInfo -> add_close_cb(closeCB);
        }
    }
};

int
run(CORBA::ORB_ptr orb, int /* argc */, char* argv[])
{
    //
    // Add the connect callback object to the ConFactory for the
    // IIOP OCI Plug-In.
    //
    CORBA::Object_var obj =
        orb -> resolve_initial_references("OCIConFactoryRegistry");
    OCI::ConFactoryRegistry_var registry =
        OCI::ConFactoryRegistry::_narrow(obj);
    OCI::ConFactorySeq_var factories = registry -> get_factories();

    for(CORBA::ULong i = 0 ; i < factories -> length() ; i++)
    {
        OCI::ConFactoryInfo_var info = factories[i] -> get_info();
        OCI::IIOP::ConFactoryInfo_var iiopInfo =
            OCI::IIOP::ConFactoryInfo::_narrow(info);

        if(!CORBA::is_nil(iiopInfo))
        {
            //
            // Add the connect callback object
            //
            OCI::ConnectCB_var connectorCB = new ConnectCB_impl();
            info -> add_connect_cb(connectorCB);
        }
    }

    //
    // Get "hello" object
    //
    obj = orb -> string_to_object("relfile:/Hello.ref");
    if(CORBA::is_nil(obj))
    {
        cerr << argv[0] << ": cannot read IOR from Hello.ref" << endl;
        return EXIT_FAILURE;
    }

    //
    // Display information on the host and port number to which
    // we'll attempt to connect.
    //
    OCI::ConnectorInfo_var info = obj -> _get_oci_connector_info();
    OCI::IIOP::ConnectorInfo_var iiopInfo =
        OCI::IIOP::ConnectorInfo::_narrow(info);

    if(!CORBA::is_nil(iiopInfo))
    {
        OCI::IIOP::InetAddr_var remoteAddr = iiopInfo -> remote_addr();
        CORBA::UShort remotePort = iiopInfo -> remote_port();

        cout << "Will connect to: "
             << remoteAddr << ':'
             << remotePort << endl;

    }

    //
    // Narrow to hello
    //
    Hello_var hello = Hello::_narrow(obj);
    assert(!CORBA::is_nil(hello));

    //
    // Main loop
    //
    cout << "Enter 'h' for hello, 's' for shutdown or 'x' for exit:\n";
    char c;
    do
    {
	cout << "> ";
	cin >> c;
	try
	{
	    if(c == 'h')
                hello -> say_hello();
	    else if(c == 's')
                hello -> shutdown();
	}
        catch(const CORBA::NO_PERMISSION&)
        {
            cout << "Connection was refused" << endl;
        }
    }
    while(cin.good() && c != 'x');

    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[], char*[])
{
    int status = EXIT_SUCCESS;
    CORBA::ORB_var orb;

    try
    {
	orb = CORBA::ORB_init(argc, argv);
	status = run(orb, argc, argv);
    }
    catch(const CORBA::Exception& ex)
    {
	cerr << ex << endl;
	status = EXIT_FAILURE;
    }

    if(!CORBA::is_nil(orb))
    {
	try
	{
	    orb -> destroy();
	}
	catch(const CORBA::Exception& ex)
	{
	    cerr << ex << endl;
	    status = EXIT_FAILURE;
	}
    }
    
    return status;
}
