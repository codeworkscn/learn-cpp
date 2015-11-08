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
#include <OB/BootManager.h>

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


int
run(CORBA::ORB_ptr orb, int /* argc */, char*[])
{
    //
    // Resolve Root POA
    //
    CORBA::Object_var poaObj = orb -> resolve_initial_references("RootPOA");
    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
    
    //
    // Get a reference to the POA manager
    //
    PortableServer::POAManager_var manager = rootPOA -> the_POAManager();
    
    //
    // Create implementation object
    //
    Hello_impl* helloImpl = new Hello_impl(orb, rootPOA);
    PortableServer::ServantBase_var servant = helloImpl;
    Hello_var hello = helloImpl -> _this();

    //
    // Resolve the BootManager and register the server
    //
    CORBA::Object_var obj = orb -> resolve_initial_references("BootManager");
    OB::BootManager_var bootManager = OB::BootManager::_narrow(obj);

    PortableServer::ObjectId_var oid =
        PortableServer::string_to_ObjectId("Hello");
    bootManager -> add_binding(oid, hello);
    
    //
    // Run implementation
    //
    manager -> activate();

    //
    // Main loop
    //
    cout << "Enter 'h' for hello or 'x' for exit:\n";
    char c;
    do
    {
	cout << "> ";
	cin >> c;
	if(c == 'h')
	    hello -> say_hello();
    }
    while(cin.good() && c != 'x');

    orb -> shutdown(true);

    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[], char*[])
{
    int status = EXIT_SUCCESS;
    CORBA::ORB_var orb;

    try
    {
	orb = CORBA::ORB_init(argc, argv, "Hello-Collocated");
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
