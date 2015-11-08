// C++
#include <OB/CORBA.h>
#include <OB/Properties.h>
#include <OB/OCI_IIOP.h>
#include "TestSrvObj.h"
#include "TestSrvObj_impl.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace SERVICEOBJ;

// #define  USE_BI_DIR


int main(int argc, char* argv[])
{
	int status = EXIT_SUCCESS;

	CORBA::ORB_var orb_;
	OB::Properties_var props = new OB::Properties( OB::Properties::getDefaultProperties() );

	props->setProperty ("ooc.orb.policy.connect_timeout","10000");

#ifdef USE_BI_DIR

	props->setProperty ("ooc.oci.plugin.bidir","OCI_bidir432d.dll");
	props->setProperty ("ooc.oci.client","iiop, bidir --protocol iiop");
	props->setProperty ("ooc.oci.server","iiop, bidir --protocol iiop");
	props->setProperty ("ooc.orb.oa.endpoint","bidir_iiop --callback");
	props->setProperty ("ooc.orb.oa.conc_model","threaded");
	props->setProperty ("ooc.bidir.peer","HelloClient");

#endif



	// 	props->setProperty ("ooc.oci.client","udp");
	// 	props->setProperty ("ooc.oci.plugin.udp","OCI_udp432d.dll");
	// 	props->setProperty ("ooc.oci.client", "iiop, bidir --protocol iiop --port 1200");
	//	props->setProperty("ooc.orb.policy.request_timeout", "110000");

	//	pl.length(1);	pl[0] = parent->create_lifespan_policy(PortableServer::PERSISTENT);
	//	pl.length(2);	pl[1] = parent->create_id_assignment_policy(PortableServer::USER_ID);

	// 	orb_->create_policy ();

	try
	{
		orb_ = OBCORBA::ORB_init(argc, argv, props);
	}
	catch(const CORBA::Exception& ex)
	{

		cerr << ex << endl;
	}


//  	CORBA::Any boolAny;
//  	boolAny <<= CORBA::Any::from_boolean(true);//默认是true！！
//  	CORBA::PolicyList policies;
//  	policies.length(1);
//  	policies[0] = orb_ -> create_policy(OB::CONNECTION_REUSE_POLICY_ID, boolAny);


// 	CORBA::Object_var pmObj = orb_ -> resolve_initial_references("ORBPolicyManager");
// 
//  CORBA::PolicyManager_var pm =	CORBA::PolicyManager::_narrow(pmObj);
//  pm -> set_policy_overrides(policies, CORBA::ADD_OVERRIDE);


	CORBA::Object_var obj;



	AB_var iface;

	try
	{

#ifndef USE_BI_DIR
		obj = orb_->string_to_object(
			"corbaloc:iiop:192.168.205.52:1234/MyServer"
			);
#else
		obj = orb_->string_to_object(
			"corbaloc:bidir_iiop:HelloServer:192.168.205.52:1234/MyServer"
			);

#endif


// 		CORBA::Object_var policyObject = obj -> _set_policy_overrides(policies, CORBA::ADD_OVERRIDE);
// 		iface = AB::_narrow(policyObject);

		iface = AB::_narrow(obj);


		//DEBUG
		// 		string strecho;
		// 		strecho += orb_->object_to_string(obj) ;
		// 		cout << strecho;
		// 		strecho = "echo "  + strecho;
		// 		strecho += " > .\\";
		// 		strecho += "client.ref";
		// 		system (strecho.c_str());
		//END DEBUG

		OCI::ConnectorInfo_var connInfo = obj->_get_oci_connector_info ();
		//	cout << connInfo->describe() << endl;

		OCI::IIOP::ConnectorInfo_var iiopInfo = OCI::IIOP::ConnectorInfo::_narrow (connInfo);

		if (!CORBA::is_nil(iiopInfo))
		{
			OCI::IIOP::InetAddr_var remoteAddr = iiopInfo ->
				remote_addr();
			CORBA::UShort remotePort = iiopInfo -> remote_port();
			cout << "Will connect to: "
				<< remoteAddr << ":" << remotePort << endl;
		}

		cout << "Connect Server Success!" << endl;
	}
	catch(const CORBA::Exception& ex)
	{
		cerr << ex << endl;
		cout<<"Connect Server Error！"<<endl;
		system("pause");
		return -10;
	}

	/*
	try
	{
	//初始化POA
	CORBA::Object_var poaObj = orb_ -> resolve_initial_references("RootPOA");
	PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
	PortableServer::POAManager_var manager = rootPOA -> the_POAManager();

	//创建回调对象
	SERVICEOBJ::CallBack_impl* cb = new SERVICEOBJ::CallBack_impl(rootPOA);

	//隐式激活对象，并获取对象引用
	SERVICEOBJ::CallBack_var cb_var = cb->_this();

	manager -> activate();

	cout << "create callback obj success!" << endl << endl;

	iface->opetater_setCallBack(cb_var);


	}
	catch(const CORBA::Exception& ex)
	{
	cerr << ex << endl;
	}

	*/



	while (1)
	{
		string iinput;
		cout << "Please Input ‘S’to SayHello,‘B’to SayByeBye ,'E'to Exit : " ;
		cin >> iinput;
		if (iinput == "S" || iinput == "s")
		{
			try
			{
				iface->a_ ();

			}
			catch (const CORBA::Exception& ex)
			{
				cout << "CORBA ERROR: " << ex << endl;
			}
		}
		else if (iinput == "B" || iinput == "b")
		{
			try
			{
				iface->b_ ();

			}
			catch (const CORBA::Exception& ex)
			{
				cout << "CORBA ERROR: " << ex << endl;
			}
		}
		else if (iinput == "E" || iinput == "e")
		{
			orb_ -> destroy();
			break;
		}
		else
		{
			continue;
		}
	}


	system("pause");

	return status;

}