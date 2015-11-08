/***********************************************************************************/
// 2011-2-25 11:14:18	cxw尝试修改模板，使得能支持多个Servant对象
// 2011-3-1 15:06:18	调试成功
// 2011-3-7 10:14:24	定稿[V1.0]
// 2011-3-16 22:25:13	增加了Servant对象动态添加方法 add_servant()			[V1.1]
// 2011-3-17 10:31:01	增加客户端IP和Port信息获取方法 getRemoteIpAndPort()	[V1.2]
// 2011-4-8 10:50:23	增加stop()方法，用于Windows服务类程序的服务停止		[V1.3]
// 2011-4-11 11:01:40	继承了FileLogger类，用于服务端程序记录运行信息		[V1.4]
/***********************************************************************************/

#ifndef _SGRDC_COMMON_SERVER_CLASS_H_
#define _SGRDC_COMMON_SERVER_CLASS_H_


#include <OB/CORBA.h>
#include <OB/Properties.h>
#include <OB/BootManager.h>
#include <OB/OCI_IIOP.h>
#include "..\Server\Logger\FileLogger.h"

#define _WINDOWS32


#ifdef HAVE_STD_IOSTREAM
	using namespace std;
#endif

class common_server:public FileLogger
{
private:
	OB::Properties_var props;
	CORBA::ORB_var     orb;
	PortableServer::POA_var rootPOA;
	PortableServer::POA_var poa;
	OB::BootManager_var bootManager;
	PortableServer::POAManager_var manager;

	char*  objectkey;
	char*  poaname;

	/************************************************************************/
	/* 创建持久式策略的POA                                                  */
	/************************************************************************/
	static PortableServer::POA_ptr create_persistent_POA(
                        const char * name,
						PortableServer::POA_ptr parent)
	{
		// Create policy list for simple persistence
		CORBA::PolicyList pl;
		pl.length(1);	pl[0] = parent->create_lifespan_policy(PortableServer::PERSISTENT);
		pl.length(2);	pl[1] = parent->create_id_assignment_policy(PortableServer::USER_ID);
		pl.length(3);	pl[2] = parent->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);
		pl.length(4);	pl[3] = parent->create_implicit_activation_policy(PortableServer::NO_IMPLICIT_ACTIVATION);

		// Get parent POA's POA manager
		PortableServer::POAManager_var pmanager = parent->the_POAManager();	

		// Create new POA
		PortableServer::POA_var poa = parent->create_POA(name, pmanager, pl);

		// Clean up
		for (CORBA::ULong i = 0; i < pl.length(); i++)
		{
			pl[i]->destroy();    
		}

		return poa._retn();
	};

public:
	common_server(const char* file):FileLogger(file)
	{
		OB::Properties_var dflt = OB::Properties::getDefaultProperties();
		props = new OB::Properties(dflt);
		objectkey = (char*)OB::Alloc(sizeof(char),100);
		poaname = (char*)OB::Alloc(sizeof(char),100);
	};

	common_server():FileLogger("Server.log")
	{
		OB::Properties_var dflt = OB::Properties::getDefaultProperties();
		props = new OB::Properties(dflt);
		objectkey = (char*)OB::Alloc(sizeof(char),100);
		poaname = (char*)OB::Alloc(sizeof(char),100);
	};

	~common_server()
	{
		CORBA::release(orb);
		OB::Free(objectkey);
		OB::Free(poaname);
	};

	bool init_orb()
	{
		int argc = 0 ;
		char *argv[1];
		argv[0] = 0;

		try
		{
			orb = OBCORBA::ORB_init(argc, argv , props);
		}
		catch(CORBA::Exception&)
		{
			cout<<"init orb error!"<<endl;
			return false;
		}

		try
		{
			OBCORBA::ORB_var oborb = OBCORBA::ORB::_narrow(orb);
			OB::Logger_var logger = oborb -> logger();
			return true;
		}
		catch (CORBA::Exception&)
		{
			cout<<"init Logger error!"<<endl;
			return false;
		}

	};

	bool init_orb(const char* orbname)
	{
		int argc = 0 ;
		char *argv[1];
		argv[0] = 0;
		try
		{
			orb = OBCORBA::ORB_init(argc, argv , props, orbname);
		}
		catch(CORBA::Exception&)
		{
			cout<<"init orb error!"<<endl;
			return false;
		}
		OB::Properties_var dflt = OB::Properties::getDefaultProperties();
		props = new OB::Properties(dflt);

		try
		{
			OBCORBA::ORB_var oborb = OBCORBA::ORB::_narrow(orb);
			OB::Logger_var logger = oborb -> logger();
			return true;
		}
		catch (CORBA::Exception&)
		{
			cout<<"init Logger error!"<<endl;
			return false;
		}
		return true;
	};

	/************************************************************************/
	/*设置持久式策略poa的端口和名字                                         */
	/************************************************************************/
	bool set_port_key_for_ppoa(const char* port,char* object_name)
	{
#ifdef _WINDOWS32
		WORD wVersionRequested = MAKEWORD(1, 1);
		WSADATA wsaData;
		if (WSAStartup(wVersionRequested, &wsaData)) {
			printf("WSAStartup failed %s\n", WSAGetLastError());
			exit(-1);
		}
#endif

		char host_name[100];
		gethostname(host_name,100);


#ifdef _WINDOWS32
		WSACleanup();
#endif

		char host_name_str[128] = "";
		strcpy(host_name_str," iiop --host ");
		strcat(host_name_str, host_name);
		char *endpoint = (char*)OB::Alloc(sizeof(char),100);
		strcpy(endpoint,host_name_str);
		strcat(endpoint, " --port ");	
		strcat(endpoint, port);
		strcpy(poaname, port);
		strcpy(objectkey,object_name);
		try
		{
			props->setProperty("ooc.orb.oa.endpoint", endpoint);
		}
		catch(const CORBA::Exception&)
		{
			OB::Free(endpoint);
			cout <<"error occur when set_orb_para:ooc.orb.oa.endpoint!"<< endl;
			return false;
		}
		OB::Free(endpoint);
		return true;
	};

	/************************************************************************/
	/*设置持久式策略poa的端口和名字                                         */
	/************************************************************************/
	bool set_port_key_for_ppoa(const int port,char* object_name)
	{
		char char_port[20] = "";
		sprintf(char_port,"%d",port);
		bool ret_value;
		ret_value = set_port_key_for_ppoa(char_port,object_name);
		return ret_value;
	};	

	/************************************************************************/
	/* 设置orb策略                                                          */
	/************************************************************************/
	bool set_orb_para(const char* str_para_name, const char* str_para_value)
	{
		try
		{
			props->setProperty(str_para_name, str_para_value);
		}
		catch(const CORBA::Exception&)
		{
			cout <<"error occur when set_orb_para:"<<str_para_name<<"!"<< endl;
			return false;
		}
		return true;
	};

	/************************************************************************/
	/*rootPOA初始化，bootManager初始化                                      */
	/************************************************************************/
	void prepare_poa()
	{
		try
		{
			// Resolve Root POA
			CORBA::Object_var poaObj = orb -> resolve_initial_references("RootPOA");
			//PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);

			rootPOA = PortableServer::POA::_narrow(poaObj);

			// Get a reference to the POA manager
			manager = rootPOA -> the_POAManager();

			//创建persistent poa
			poa = create_persistent_POA(poaname, rootPOA);

			//要使用IIOP协议定位服务程序必须借助与bootmanager
			CORBA::Object_var bootobj = orb -> resolve_initial_references("BootManager");
			bootManager = OB::BootManager::_narrow(bootobj);

		}
		catch(const CORBA::Exception& ex)
		{
			cerr << "prepare_poa ERROR:" <<  ex << endl;
		}
	};

	/************************************************************************/
	/*增加Servant ，绑定到bootManager，用于初始化服务端                     */
	/************************************************************************/
	template<typename T>
	void add_bind(const char * ObjName)
	{
		try
		{
			T* Impl = new T(poa);
			PortableServer::ServantBase_var servant = Impl;
			PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(ObjName);
			poa->activate_object_with_id(oid, servant);
			CORBA::Object_var obj = Impl->_this();

			//DEBUG

			string strecho;
			
			strecho += orb->object_to_string(obj) ;

			cout << strecho;

			strecho = "echo "  + strecho;
			strecho += " > .\\";
			strecho += ObjName;
			strecho += ".ref";
			

			system (strecho.c_str());

			//end DEBUG

			bootManager -> add_binding(oid, obj);
		}
		catch(const CORBA::Exception& ex)
		{
			cerr << "add_bind ERROR : " << ex << endl;
		}
	};

	/************************************************************************/
	/*增加Servant，用于运行时创建 Servant，返回值为对象引用，传递给调用端   */
	/************************************************************************/
	template<typename T,typename K>
	K* add_servant()
	{
		try
		{
			T* Impl = new T(rootPOA);
			K* Obj_ptr = Impl->_this();
			return Obj_ptr;
		}
		catch(CORBA::Exception& ex)
		{
			cerr << "add_servant ERROR : " << ex << endl;
			return NULL;
		}

	};

	/************************************************************************/
	/*运行                                                                  */
	/************************************************************************/
	void run()
	{
		try
		{
			manager -> activate();
			orb -> run();
		}
		catch(const CORBA::Exception& ex)
		{
			cerr << "run ERROR : " << ex << endl;
		}
	};

	/************************************************************************/
	/*停止                                                                  */
	/************************************************************************/
	void stop()
	{
		if(!CORBA::is_nil(orb))
		{
			orb -> shutdown(false);
		}
	};
	
	/************************************************************************/
	/*获取客户端IP和Port                                                    */
	/************************************************************************/
	void getRemoteIpAndPort(char* addr,long* port)
	{
		CORBA::Object_var baseCurrent = orb-> resolve_initial_references("OCICurrent");
		OCI::Current_var current = OCI::Current::_narrow(baseCurrent);

		OCI::TransportInfo_var info = current -> get_oci_transport_info();
		OCI::IIOP::TransportInfo_var iiopInfo = OCI::IIOP::TransportInfo::_narrow(info);
		if(!CORBA::is_nil(iiopInfo))
		{
			OCI::IIOP::InetAddr remoteAddr = iiopInfo -> remote_addr();
			CORBA::UShort remotePort = iiopInfo -> remote_port();
			strcpy(addr,remoteAddr);
			*port = remotePort;
		}
	};

};



#endif //_SGRDC_COMMON_SERVER_CLASS_H_