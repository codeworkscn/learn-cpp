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

#include <Hello_impl.h>

#include <stdlib.h>
#include <errno.h>

#ifdef HAVE_FSTREAM
#   include <fstream>
#else
#   include <fstream.h>
#endif

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

            cout << "Closing connection from: "
                 << remoteAddr << ':'
                 << remotePort << endl;
        }
    }
};

class AcceptCB_impl : public OCI::AcceptCB,
		      public OBCORBA::RefCountLocalObject
{
public:

    virtual void accept_cb(OCI::TransportInfo_ptr transport_info)
    {
        OCI::IIOP::TransportInfo_var iiopInfo =
            OCI::IIOP::TransportInfo::_narrow(transport_info);

        if(!CORBA::is_nil(iiopInfo))
        {
            OCI::IIOP::InetAddr_var remoteAddr = iiopInfo -> remote_addr();
            CORBA::UShort remotePort = iiopInfo -> remote_port();

            cout << "Connection from: "
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
    // Resolve the Root POA
    //
    CORBA::Object_var obj = orb -> resolve_initial_references("RootPOA");
    PortableServer::POA_var root = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var poaManager = root -> the_POAManager();
    OBPortableServer::POAManager_var obManager =
        OBPortableServer::POAManager::_narrow(poaManager);

    //
    // Get the OCI Current object
    //
    obj = orb -> resolve_initial_references("OCICurrent");
    OCI::Current_var ociCurrent = OCI::Current::_narrow(obj);

    //
    // Create implementation object
    //
    Hello_impl* helloImpl = new Hello_impl(orb, ociCurrent);
    PortableServer::ServantBase_var servant = helloImpl;
    Hello_var p = helloImpl -> _this();

    //
    // Save reference
    //
    CORBA::String_var s = orb -> object_to_string(p);

    const char* refFile = "Hello.ref";
    ofstream out(refFile);
    if(out.fail())
    {
        cerr << argv[0] << ": can't open `" << refFile << "': "
             << strerror(errno) << endl;
        return EXIT_FAILURE;
    }

    out << s << endl;
    out.close();

    //
    // Display the host and port
    //
    OCI::AcceptorSeq_var acceptors = obManager -> get_acceptors();

    for(CORBA::ULong i = 0 ; i < acceptors -> length() ; i++)
    {
        OCI::AcceptorInfo_var info = acceptors[i] -> get_info();
        OCI::IIOP::AcceptorInfo_var iiopInfo =
            OCI::IIOP::AcceptorInfo::_narrow(info);

        if(!CORBA::is_nil(iiopInfo))
        {
            CORBA::StringSeq_var hosts = iiopInfo -> hosts();
            CORBA::UShort port = iiopInfo -> port();
// 			OCI::IIOP::InetAddr_var addr = iiopInfo -> addr();//IP看起来是无效的  0.0.0.0

            cout << "*** Running on host `" << hosts[0]
// 					<<",ip " << addr 
                 << "', port number " << port << endl;

            //
            // Add the accept callback object
            //
            OCI::AcceptCB_var acceptorCB = new AcceptCB_impl();
            iiopInfo -> add_accept_cb(acceptorCB);
        }
    }

    //
    // Run implementation
    //
    poaManager -> activate();
    orb -> run();

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
