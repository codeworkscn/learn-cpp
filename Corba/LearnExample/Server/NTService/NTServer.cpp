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
#include <OB/NTService.h>

#include "HelloWorldService.h"

#include <stdlib.h>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

using namespace OB;

static void
usage(const char* progName)
{
    cerr << "Usage:\n";
    cerr << progName << " [options]\n"
	"\n"
	"Options:\n"
	"-h, --help             Show this message.\n"
	"-i, --install          Install the service.\n"
	"-u, --uninstall        Uninstall the service.\n"
        "-d, --debug            Run in console mode.\n"
	;
}

int
main(int argc, char* argv[])
{
    HelloWorldService service;

    //
    // Next parse the command line.
    //

// 	CORBA::Long i;
// 
// 	for(i = 1 ; i < argc && *argv[i] == '-' ; i++)
// 	{
// 		if(strcmp(argv[i], "--help") == 0 ||
// 			strcmp(argv[i], "-h") == 0)
// 		{
// 			usage(argv[0]);
// 			return EXIT_FAILURE;
// 		}
// 		else if(strcmp(argv[i], "--install") == 0 ||
// 			strcmp(argv[i], "-i") == 0)
// 		{
// 			service.install();
// 			return EXIT_SUCCESS;
// 		}
// 		else if(strcmp(argv[i], "--uninstall") == 0 ||
// 			strcmp(argv[i], "-u") == 0)
// 		{
// 			service.uninstall();
// 			return EXIT_SUCCESS;
// 		}
// 		else if(strcmp(argv[i], "--debug") == 0 ||
// 			strcmp(argv[i], "-d") == 0)
// 		{
// 			service.setDebug();
// 		}
// 		else if(strncmp(argv[i], "-OA", 3) != 0 &&
// 			strncmp(argv[i], "-ORB", 4) != 0)
// 		{
// 			cerr << argv[0] << ": unknown option `"
// 				<< argv[i] << "'\n" << endl;
// 			usage(argv[0]);
// 			return EXIT_FAILURE;
// 		}
// 	}
	service.setDebug();

    service.run(argc, argv);

    return EXIT_SUCCESS;
}
