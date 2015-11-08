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
#include <OB/Properties.h>

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
run(CORBA::ORB_ptr orb, int /* argc */, char* argv[])
{
	//
	// Resolve Root POA
	//
	CORBA::Object_var poaObj = orb -> resolve_initial_references("RootPOA");
	PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);

	//
	// Create Persistent POA
	//
	CORBA::PolicyList pl;
	pl.length (4);
 	pl[0] = rootPOA->create_lifespan_policy(PortableServer::PERSISTENT);
  	pl[1] = rootPOA->create_id_assignment_policy(PortableServer::USER_ID);
  	pl[2] = rootPOA->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);
  	pl[3] = rootPOA->create_implicit_activation_policy(PortableServer::NO_IMPLICIT_ACTIVATION);

	//
	// Get a reference to the POA manager
	//
	PortableServer::POAManager_var manager = rootPOA -> the_POAManager();

	//
	// Create Persistent POA
	//
	PortableServer::POA_var stapoa = rootPOA->create_POA ("stapoa",manager,pl) ;

	//
	// Resolve the BootManager and register the server
	//
	CORBA::Object_var obj = orb -> resolve_initial_references("BootManager");
	OB::BootManager_var bootManager = OB::BootManager::_narrow(obj);
	
	//
	// Create implementation object
	//
	Hello_impl* helloImpl = new Hello_impl(stapoa);
	PortableServer::ServantBase_var servant = helloImpl;
	PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId("Hello");
	stapoa->activate_object_with_id(oid, servant);
	Hello_var hello = helloImpl -> _this();

	//
	// add binding to  BootManager
	//
	bootManager -> add_binding(oid, hello);

	//
	// Save reference
	//
	CORBA::String_var s = orb -> object_to_string(hello);

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
	// Run implementation
	//
	manager -> activate();
	orb -> run();

	return EXIT_SUCCESS;
}

int
main(int argc, char* argv[], char*[])
{
	int status = EXIT_SUCCESS;
	CORBA::ORB_var orb;

	OB::Properties_var dflt =
		OB::Properties::getDefaultProperties();
	OB::Properties_var props = new OB::Properties(dflt);


  	//从 server.conf 文件载入配置，
  	bool loadsuccess = props -> load("server.conf");
  
  	if (!loadsuccess)
  	{
  		cerr << "load server.conf error!" << endl;
  		return -1;
  	}

// 	props->setProperty ("ooc.orb.trace.connections", "3000");
// 	props->setProperty ("ooc.orb.oa.conc_model","threaded");
// 	props->setProperty ("ooc.orb.oa.endpoint","iiop --numeric --port 12345");
// 	
	try
	{
		orb = OBCORBA::ORB_init(argc, argv,props);
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