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
#include <OB/PortableInterceptor.h>

#include <PIDemo_impl.h>
#include <PIDemoDSI_impl.h>
#include <LoggerPolicy_impl.h>
#include <RILogger.h>

#ifdef HAVE_FSTREAM
#   include <fstream>
#else
#   include <fstream.h>
#endif

#include <errno.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

//
// ServantLocator implementation to demonstrate location forwarding
//
class PIDemoLocator_impl : public POA_PortableServer::ServantLocator,
			   public PortableServer::RefCountServantBase
{
    //
    // My ORB
    //
    CORBA::ORB_var orb_;

    //
    // The PIDemo static implementation
    //
    PortableServer::ServantBase_var piDemoImpl_;

    //
    // The PIDemo dynamic implementation
    //
    PortableServer::ServantBase_var piDemoDSIImpl_;

public:

    // -----------------------------------------------------------------
    // PIDemoLocator_impl constructor/destructor
    // -----------------------------------------------------------------

    PIDemoLocator_impl(CORBA::ORB_ptr orb,
		       const PortableServer::ServantBase_var& piDemoImpl,
    		       const PortableServer::ServantBase_var& piDemoDSIImpl)
        : orb_(CORBA::ORB::_duplicate(orb)),
	  piDemoImpl_(piDemoImpl),
	  piDemoDSIImpl_(piDemoDSIImpl)
    {
    }

    ~PIDemoLocator_impl()
    {
    }

    // -----------------------------------------------------------------
    // Standard IDL to C++ mapping
    // -----------------------------------------------------------------

    PortableServer::Servant
    preinvoke(const PortableServer::ObjectId& oid,
              PortableServer::POA_ptr poa,
              const char* operation,
              PortableServer::ServantLocator::Cookie& /* the_cookie */)
        throw(PortableServer::ForwardRequest,
	      CORBA::SystemException)
    {
        CORBA::String_var oidString = PortableServer::ObjectId_to_string(oid);

        if(strcmp("PIDemo", oidString) == 0)
	{
	    //
	    // Request for the static implementation
	    //

	    if(strcmp(operation, "switch_to_dynamic_impl") == 0)
	    {
		//
		// switch_to_dynamic_impl() was called -- throw
		// LOCATION_FORWARD with the object associated with
		// dynamic implementation
		//

		oidString = CORBA::string_dup("PIDemoDSI");
		PortableServer::ObjectId_var oid =
		    PortableServer::string_to_ObjectId(oidString);

                CORBA::Object_var obj =
                    poa -> create_reference_with_id(oid, "IDL:PIDemo:1.0");

                throw PortableServer::ForwardRequest(obj);
	    }

	    return piDemoImpl_;
	}
	else if(strcmp("PIDemoDSI", oidString) == 0)
        {
	    //
	    // Request for the dynamic implementation
	    //

            if(strcmp(operation, "switch_to_static_impl") == 0)
            {
		//
		// switch_to_static_impl() was called -- throw
		// LOCATION_FORWARD with the object associated with
		// static implementation
		//

		oidString = CORBA::string_dup("PIDemo");
		PortableServer::ObjectId_var oid =
		    PortableServer::string_to_ObjectId(oidString);

                CORBA::Object_var obj =
                    poa -> create_reference_with_id(oid, "IDL:PIDemo:1.0");

                throw PortableServer::ForwardRequest(obj);
            }

            return piDemoDSIImpl_;
        }

        //
        // Unknown object id -- throw OBJECT_NOT_EXIST
        //
        throw CORBA::OBJECT_NOT_EXIST();
        return 0; // Some compilers need this
    }

    void
    postinvoke(const PortableServer::ObjectId& /*oid*/,
               PortableServer::POA_ptr /*poa*/,
               const char* /*operation*/,
               PortableServer::ServantLocator::Cookie /*the_cookie*/,
               PortableServer::Servant /*the_servant*/)
        throw(CORBA::SystemException)
    {
	//
	// Nothing to do here
	//
    }
};

// ---------------------------------------------------------------------
// Server code
// ---------------------------------------------------------------------

int
run(CORBA::ORB_ptr orb, int argc, char* argv[])
    throw(CORBA::Exception)
{
    //
    // Get the logging level from the command-line
    //
    if(argc > 2)
    {
	cerr << "Usage: " << argv[0] << " [log-level]" << endl;
	return EXIT_FAILURE;
    }

    CORBA::Short logLevel = 1;
    if(argc > 1)
	logLevel = (CORBA::Short)atoi(argv[1]);
    
    //
    // Resolve Root POA
    //
    CORBA::Object_var obj = orb -> resolve_initial_references("RootPOA");
    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(obj);
    assert(!CORBA::is_nil(rootPOA));

    //
    // Get a reference to the POA manager
    //
    PortableServer::POAManager_var manager = rootPOA -> the_POAManager();

    //
    // Create a persistent POA for the servants (use the logger policy
    // to set the logging level)
    //
    CORBA::Any any;
    CORBA::PolicyList policies(6);
    policies.length(6);

    any <<= PortableServer::PERSISTENT;
    policies[0] = orb -> create_policy(PortableServer::LIFESPAN_POLICY_ID,any);

    any <<= PortableServer::USER_ID;
    policies[1] =
        orb -> create_policy(PortableServer::ID_ASSIGNMENT_POLICY_ID, any);

    any <<= PortableServer::USE_SERVANT_MANAGER;
    policies[2] =
        orb -> create_policy(PortableServer::REQUEST_PROCESSING_POLICY_ID,any);

    any <<= PortableServer::NON_RETAIN;
    policies[3] =
        orb -> create_policy(PortableServer::SERVANT_RETENTION_POLICY_ID, any);

    any <<= PortableServer::NO_IMPLICIT_ACTIVATION;
    policies[4] = 
        orb -> create_policy(PortableServer::IMPLICIT_ACTIVATION_POLICY_ID,
                             any);

    any <<= logLevel;
    policies[5] = orb -> create_policy(LOGGER_POLICY_ID, any);

    PortableServer::POA_var persistentPOA =
	rootPOA -> create_POA("persistent", manager, policies);
    
    //
    // Create implementation objects
    //
    PIDemo_impl* piDemoImpl = new PIDemo_impl(orb, persistentPOA);
    PortableServer::ServantBase_var piDemoServant = piDemoImpl;
    PIDemoDSI_impl* piDemoDSIImpl = new PIDemoDSI_impl(orb, persistentPOA);
    PortableServer::ServantBase_var piDemoDSIServant = piDemoDSIImpl;

    //
    // Create the servant locator and register it with the POA
    //
    PIDemoLocator_impl* locatorImpl =
	new PIDemoLocator_impl(orb, piDemoServant, piDemoDSIServant);
    PortableServer::ServantBase_var locatorServant = locatorImpl;
    PortableServer::ServantLocator_var locator = locatorImpl -> _this();
    persistentPOA -> set_servant_manager(locator);

    //
    // The PIDemo::call_other_impl method results in calls between
    // the two implementations.  Hence, the servers are also clients.
    // Create policy to enable client logging.
    //
    policies.length(1);
    any <<= logLevel;
    policies[0] = orb -> create_policy(LOGGER_POLICY_ID, any);

    //
    // Get the object references (with the logging policy) for each
    // implementation
    //
    PortableServer::ObjectId_var oid =
	PortableServer::string_to_ObjectId("PIDemo");
    obj = persistentPOA -> create_reference_with_id(oid, "IDL:PIDemo:1.0");
    obj = obj -> _set_policy_overrides(policies, CORBA::ADD_OVERRIDE);
    PIDemo_var piDemo = PIDemo::_narrow(obj);
    oid = PortableServer::string_to_ObjectId("PIDemoDSI");
    obj = persistentPOA -> create_reference_with_id(oid, "IDL:PIDemo:1.0");
    obj = obj -> _set_policy_overrides(policies, CORBA::ADD_OVERRIDE);
    PIDemo_var piDemoDSI = PIDemo::_narrow(obj);
    assert(!CORBA::is_nil(piDemo));
    assert(!CORBA::is_nil(piDemoDSI));

    //
    // Pass each implementation the other's corresponding object reference
    //
    piDemoImpl -> setOtherObj(piDemoDSI);
    piDemoDSIImpl -> setOtherObj(piDemo);

    //
    // Write IOR of first object to file
    //
    ofstream out("PIDemo.ref");
    if(out.fail())
    {
	cerr << "Can't open `" << "PIDemo.ref" << "': "
	     << strerror(errno) << endl;
	return EXIT_FAILURE;
    }
    CORBA::String_var s = orb -> object_to_string(piDemo);
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

    try
    {
	//
	// Initialize the request interceptors
	//
	RILogger::init();

	//
	// Initialize the ORB
	//
	orb = CORBA::ORB_init(argc, argv);

	//
	// Start the server
	//
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
