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

#include <Hello_skel_tie.h>
#include <Hello_impl_tie.h>

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

class POA_Hello_refcount_tie : public POA_Hello_tie< Hello_impl_tie >,
			       public PortableServer::RefCountServantBase
{
public:

    POA_Hello_refcount_tie(Hello_impl_tie* impl, PortableServer::POA_ptr poa)
	: POA_Hello_tie< Hello_impl_tie >(impl, poa, true)
    {
    }

    virtual
    ~POA_Hello_refcount_tie()
    {
    }
};

int
run(CORBA::ORB_ptr orb, int /* argc */, char* argv[])
{
    //
    // Resolve Root POA
    //
    CORBA::Object_var poaObj =
        orb -> resolve_initial_references("RootPOA");
    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);

    //
    // Get a reference to the POA manager
    //
    PortableServer::POAManager_var manager = rootPOA -> the_POAManager();

    //
    // Create implementation object
    //
    Hello_impl_tie* helloTie = new Hello_impl_tie(orb);
    POA_Hello_refcount_tie* helloImpl
    	= new POA_Hello_refcount_tie(helloTie, rootPOA);
    PortableServer::ServantBase_var servant = helloImpl;
    Hello_var hello = helloImpl -> _this();

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

    try
    {
	orb = CORBA::ORB_init(argc, argv, "Hello-Server-TIE");
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
