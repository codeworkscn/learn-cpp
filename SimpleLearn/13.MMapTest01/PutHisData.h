#ifndef _PUT_HIS_DATA_H_
#define _PUT_HIS_DATA_H_

#include <iostream>
// #define DO_USE_MMAP_

#include "windows.h"

//Ԥ������
#define MAP_PREFIX          "Global\\"
#define MAP_SIZE            1024 * 1024
#define VIEW_OFFSET         0
#define VIEW_SIZE           1024 * 1024

using namespace std;

//��������
const long MAX_NAME_LEN = 32;                         //��������
const long MAX_DESC_LEN = 256;                        //����
const long MAX_IP_LEN = 32;                           //IP
const long MAX_HOSTNAME_LEN2 = 32;                     //������
const long MAX_CPU_LEN = 32;                          //CPU�ͺ�
const long MAX_MEMORY_LEN = 32;                       //�ڴ�
const long MAX_BAND_LEN = 32;                         //�������
const long MAX_POINTSOURCE_LEN = 16;                  //��Դ
const long MAX_TYPE_LEN = 32;                         //�ӿ����� 
const long MAX_VERSION_LEN = 32;                      //�ӿڰ汾
const long MAX_PROTOCOL_LEN = 16;                     //�ӿ�Э��
const long MAX_USER_LEN = 64;                         //�û�����



//�ӿ����Խṹ�嶨��
struct InterfaceStruct
{
	long id;
	char name[MAX_NAME_LEN];					//�ӿ���,�ͷ���������һ��
	char desc[MAX_DESC_LEN];					//�ӿ�����
	char ip[MAX_IP_LEN];
	char hostname[MAX_HOSTNAME_LEN2];			//������
	char cpu[MAX_CPU_LEN];						//cpu�ͺ�
	char memory[MAX_MEMORY_LEN];				//�ڴ�
	char band[MAX_BAND_LEN];					//�������
	char pointSource[MAX_POINTSOURCE_LEN];		//��Դ
	char type[MAX_TYPE_LEN];					//�ӿ�����	
	long bStatus;								//�Ƿ��¼״̬��
	char version[MAX_VERSION_LEN];				//�ӿڰ汾
	long bPerformance;							//�Ƿ������ܼ��
	char protocol[MAX_PROTOCOL_LEN];			//�ӿ�Э��
	long bSync;									//�Ƿ�ͬ��
	long sync_period;							//ͬ��ʱ����,��λ�Ƿ��ӣ������0����ʾ��ͬ��
	long update_period;							//�������ڣ���λ����
	long overTime;								//��ʱʱ�䣬��λ����
	long try_times;								//ʧ�ܴ���
	long rety_period;							//�������ڣ���λ����
	long bPing;	
	long ping_period;							//ping���ڣ���λ���룬�����0����ʾ��Ping
	char create_time[32];  //����char[]
	char create_user[MAX_USER_LEN];
	char update_time[32];  //����char[]
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
