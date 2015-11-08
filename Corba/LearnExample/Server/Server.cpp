#include <OB/CORBA.h>
#include "InterfaceTest_impl.h"
#include "SGRDC_common_server_class.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace InterfaceTest;

int main(int argc,char* argv[])
{

	common_server fs;

	fs.set_port_key_for_ppoa(1234,"MyServer");
	fs.set_orb_para("ooc.orb.trace.connections", "3000");
	fs.init_orb();
	fs.prepare_poa();

	fs.add_bind<Interface1_impl>("MyServer1");
	fs.add_bind<Interface2_impl>("MyServer2");

	fs.run();

	return EXIT_SUCCESS;

}

