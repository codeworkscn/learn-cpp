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

#include <Hello.h>

#include <stdlib.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

int
run(CORBA::ORB_ptr orb, int /* argc */, char* argv[])
{
    //
    // Get "hello" object
    //
    CORBA::Object_var obj;

    try
    {
// 		obj  = orb -> string_to_object("relfile:/Hello.ref");
		obj  = orb -> string_to_object("corbaloc::127.0.0.1:12345/Hello");		
    }
    catch(const CORBA::BAD_PARAM&)
    {
    }

    if(CORBA::is_nil(obj))
    {
	cerr << argv[0] << ": cannot read IOR from Hello.ref" << endl;
	return EXIT_FAILURE;
    }
    
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
	if(c == 'h')
	    hello -> say_hello();
	else if(c == 's')
	    hello -> shutdown();
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
	orb = CORBA::ORB_init(argc, argv, "Hello-Client");
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
