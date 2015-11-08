#ifndef _PUT_HIS_DATA_H_
#define _PUT_HIS_DATA_H_

#include <iostream>
// #define DO_USE_MMAP_

#include "windows.h"

//预处理定义
#define MAP_PREFIX          "Global\\"
#define MAP_SIZE            1024 * 1024
#define VIEW_OFFSET         0
#define VIEW_SIZE           1024 * 1024

using namespace std;

//常量定义
const long MAX_NAME_LEN = 32;                         //点名长度
const long MAX_DESC_LEN = 256;                        //描述
const long MAX_IP_LEN = 32;                           //IP
const long MAX_HOSTNAME_LEN2 = 32;                     //机器名
const long MAX_CPU_LEN = 32;                          //CPU型号
const long MAX_MEMORY_LEN = 32;                       //内存
const long MAX_BAND_LEN = 32;                         //网络带宽
const long MAX_POINTSOURCE_LEN = 16;                  //电源
const long MAX_TYPE_LEN = 32;                         //接口类型 
const long MAX_VERSION_LEN = 32;                      //接口版本
const long MAX_PROTOCOL_LEN = 16;                     //接口协议
const long MAX_USER_LEN = 64;                         //用户长度



//接口属性结构体定义
struct InterfaceStruct
{
	long id;
	char name[MAX_NAME_LEN];					//接口名,和服务名称是一个
	char desc[MAX_DESC_LEN];					//接口描述
	char ip[MAX_IP_LEN];
	char hostname[MAX_HOSTNAME_LEN2];			//机器名
	char cpu[MAX_CPU_LEN];						//cpu型号
	char memory[MAX_MEMORY_LEN];				//内存
	char band[MAX_BAND_LEN];					//网络带宽
	char pointSource[MAX_POINTSOURCE_LEN];		//点源
	char type[MAX_TYPE_LEN];					//接口类型	
	long bStatus;								//是否记录状态点
	char version[MAX_VERSION_LEN];				//接口版本
	long bPerformance;							//是否开启性能监控
	char protocol[MAX_PROTOCOL_LEN];			//接口协议
	long bSync;									//是否同步
	long sync_period;							//同步时间间隔,单位是分钟，如果是0，表示不同步
	long update_period;							//更新周期，单位是秒
	long overTime;								//超时时间，单位是秒
	long try_times;								//失败次数
	long rety_period;							//重连周期，单位是秒
	long bPing;	
	long ping_period;							//ping周期，单位是秒，如果是0，表示不Ping
	char create_time[32];  //暂用char[]
	char create_user[MAX_USER_LEN];
	char update_time[32];  //暂用char[]
	char update_user[MAX_USER_LEN];
	long  auto_update;

};

class PutHisDataClass
{

public:
	PutHisDataClass(InterfaceStruct ifs)
	{
		hMapFile = NULL;
		::InitializeCriticalSection(&myCS);
		sprintf_s(pLogFile,256,"%s_MMap.log",ifs.name);
		CreateMemMap(ifs);
	}
	~PutHisDataClass()
	{

	}

public:
	char pLogFile[256];
	CRITICAL_SECTION myCS;
	HANDLE hMapFile;
	InterfaceStruct ifs;

private:

	void WriteLog(char* pMsg);
	void CreateMemMap(InterfaceStruct &ifs);

public:
	long PutMemMap(void *data,long offset,long size);


};

extern DWORD GetMapMemory(unsigned char *szResult,long len,const char* svcname);

#endif
