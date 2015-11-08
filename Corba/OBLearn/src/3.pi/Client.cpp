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

#include <PIDemo.h>
#include <LoggerPolicy_impl.h>
#include <RILogger.h>

#include <errno.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

// ---------------------------------------------------------------------
// Menu string
// ---------------------------------------------------------------------

static const char* menu =
    "Portable Interceptor Demo\n"
    "~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    "m: Display this menu\n"
    "l: Enable/disable logging\n"
    "q: Quit client and shutdown server\n"
    "1: Invoke \"void   noargs()\"\n"
    "2: Invoke \"void   noargs_oneway()\"\n"
    "3: Invoke \"string noargs_return()\"\n"
    "4: Invoke \"void   withargs(in string, inout string, out string)\"\n"
    "5: Invoke \"void   systemexception()\"\n"
    "6: Invoke \"void   userexception()\"\n"
    "7: Invoke \"void   switch_to_static_impl()\"\n"
    "8: Invoke \"void   switch_to_dynamic_impl()\"\n"
    "9: Invoke \"void   call_other_impl(in short)\"\n";

// ---------------------------------------------------------------------
// Client code
// ---------------------------------------------------------------------

int
run(CORBA::ORB_ptr orb, int argc, char* argv[])
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
    // Get PIDemo object reference
    //
    CORBA::Object_var obj = orb -> string_to_object("relfile:/PIDemo.ref");
    if(CORBA::is_nil(obj))
    {
	cerr << "Cannot read IOR from PIDemo.ref" << endl;
	return EXIT_FAILURE;
    }

    //
    // Narrow the object reference
    //
    PIDemo_var piDemoWithoutLogging = PIDemo::_narrow(obj);
    if(CORBA::is_nil(piDemoWithoutLogging))
    {
	cerr << "IOR in PIDemo.ref is not a PIDemo IOR" << endl;
	return EXIT_FAILURE;
    }

    //
    // Create a policy set on the object reference to set the
    // logging level
    //
    CORBA::Any any;
    any <<= logLevel;
    CORBA::PolicyList pl(1);
    pl.length(1);
    pl[0] = orb -> create_policy(LOGGER_POLICY_ID, any);
    obj = obj -> _set_policy_overrides(pl, CORBA::ADD_OVERRIDE);

    //
    // Narrow new object reference
    //
    PIDemo_var piDemoWithLogging = PIDemo::_narrow(obj);
    if(CORBA::is_nil(piDemoWithLogging))
    {
	cerr << "IOR in PIDemo.ref is not a PIDemo IOR" << endl;
	return EXIT_FAILURE;
    }

    //
    // Main loop
    //
    PIDemo_ptr piDemo = piDemoWithLogging;
    bool logging = true;
    char cmd = 0;

    cout << menu;
    do
    {
	cout << "> ";
	cin >> cmd;
	switch(cmd)
	{
	case 'm':
	    cout << menu;
	    break;

	case 'l':
	    logging = !logging;
	    piDemo = logging ? piDemoWithLogging.in() 
		             : piDemoWithoutLogging.in();
	    cout << "Client logging is now "
	         << (logging ? "enabled" : "disabled")
		 << endl;
	    break;

	case 'q':
	    piDemo -> deactivate();
	    break;

	case '1':
	    cout << "void PIDemo::noargs()" << endl;
	    piDemo -> noargs();
	    break;

	case '2':
	    cout << "void PIDemo::noargs_oneway()" << endl;
	    piDemo -> noargs_oneway();
	    break;

	case '3':
	{
	    cout << "string PIDemo::noargs_return()" << endl;
	    CORBA::String_var str = piDemo -> noargs_return();
	    break;
	}

	case '4':
	{
	    cout << "void PIDemo::withargs(in string, "
	    	 << "inout string, out string)"
		 << endl;
	    CORBA::String_var str1 = CORBA::string_dup("");
	    CORBA::String_var str2 = CORBA::string_dup("");
	    CORBA::String_var str3;
	    piDemo -> withargs(str1.in(), str2.inout(), str3.out());
	    break;
	}

	case '5':
	    cout << "void PIDemo::systemexception()" << endl;
	    try
	    {
		piDemo -> systemexception();
	    }
	    catch(const CORBA::SystemException&)
	    {
		
	    }
	    break;

	case '6':
	    cout << "void PIDemo::userexception()" << endl;
	    try
	    {
		piDemo -> userexception();
	    }
	    catch(const PIDemo::User&)
	    {
	    }
	    break;

	case '7':
	    cout << "void PIDemo::switch_to_static_impl()" << endl;
	    piDemo -> switch_to_static_impl();
	    break;

	case '8':
	    cout << "void PIDemo::switch_to_dynamic_impl()" << endl;
	    piDemo -> switch_to_dynamic_impl();
	    break;

	case '9':
	{
	    cout << "void PIDemo::call_other_impl(in short level)" << endl;
	    cout << "Enter level> ";

	    CORBA::Short level;
	    cin >> level;

	    piDemo -> call_other_impl(level);
	    break;
	}
	}
    }
    while(cin.good() && cmd != 'q');

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
	// Start the client
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
