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
#include <OB/Properties.h>
#include <OB/NTService.h>
#include <OB/Logger.h>

#include "HelloWorldService.h"
#include "..\TestSrvObj_impl.h"
#include "..\SGRDC_common_server_class.h"
#include "..\Logger\FileLogger.h"
#include <iostream>

#ifdef HAVE_FSTREAM
#include <fstream>

#else
#include <fstream.h>
#endif

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif


// #define  USE_BI_DIR

using namespace OB;
using namespace SERVICEOBJ;

common_server* fs;


// ----------------------------------------------------------------------
// HelloWorldService constructor
// ----------------------------------------------------------------------
HelloWorldService::HelloWorldService()
    : NTService("SERVICEOBJ", "SERVICEOBJ", HELLO_MSG),
      stopped_(false)
{
}

// ----------------------------------------------------------------------
// HelloWorldService public member implementation
// ----------------------------------------------------------------------
void HelloWorldService::orb_run(Logger_ptr logger)
{

	CORBA::String_var logfile;

	const char* env = getenv("TEMP");
	if(env == 0)
		env = "C:";
	logfile = env;
	logfile += "\\Server.log";

// 	fs = new common_server(logfile);
	fs = new common_server();

// 	fs->set_port_key_for_ppoa(1234,"CXW");

	fs->set_orb_para("ooc.orb.trace.connections", "3000");
	fs->set_orb_para ("ooc.orb.oa.conc_model","threaded");

#ifdef USE_BI_DIR

	fs->set_orb_para ("ooc.oci.plugin.bidir","OCI_bidir432d.dll");
	fs->set_orb_para ("ooc.oci.client","iiop, bidir --protocol iiop");
	fs->set_orb_para ("ooc.oci.server","iiop, bidir --protocol iiop");
	fs->set_orb_para ("ooc.orb.oa.endpoint","bidir_iiop --numeric --port 1234");
	fs->set_orb_para ("ooc.bidir.peer","HelloServer");

#else

	fs->set_orb_para ("ooc.orb.oa.endpoint","iiop --numeric --port 1234");

#endif

	fs->init_orb();
	fs->prepare_poa();

	fs->add_bind<AB_impl>("MyServer");

	cout << "add_bind 1" << endl;

// 	fs->add_bind<AB_impl>("MyServer2");
// 
// 	cout << "add_bind 2" << endl;

	//
    // Inform the status manager that the service is running.
    //
    statusUpdate(SERVICE_RUNNING);
        
    //
    // Run implementation
    //
	if(!stopped_)
	{
		fs->run();
	}

}

void HelloWorldService::start(int argc, char** argv, Logger_ptr logger)
{
	try
	{
		orb_run(logger);
	}
	catch(const CORBA::Exception& ex)
	{
		CORBA::String_var err = ex._to_string();
		logger -> error(err);
	}

}

void HelloWorldService::stop()
{
    //
    // The service manager calls this in a seperate thread. So first
    // we have inform JTC to adopt this thread.
    //
    JTCAdoptCurrentThread adopt;
    stopped_ = true;
	fs->stop();
	delete fs;
}

