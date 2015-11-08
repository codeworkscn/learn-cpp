#include <fstream>
#include <iostream>
#include <Windows.h>
#include <time.h>

#include "INIRead.h"

using namespace std;

int main(void)
{
	wchar_t tempchar[64];
	char temp[64];
	size_t count = 0;
	//time_t st;
	//time_t et;
	//st = time(NULL);
	//for (long i=0;i<10000;i++)
	//{
	//	SGRDC_Get_INI_Info(L"SGRDCserver",L"IP",tempchar);
	//}
	//et = time(NULL);
	//cout << "读取ini文件10000次成功，共耗时: " << et - st << " 秒" << endl;

	SGRDC_Get_INI_Info(L"SGRDCserver",L"IP",tempchar);

//	cout << tempchar << endl;


	//if(SGRDC_Get_INI_Info(L"SGRDCserver",L"IP",tempchar))
	//{
	//	cerr << "获取SGRDCserver IP失败" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "SGRDCserver IP : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"ServerName",tempchar))
	//{
	//	cerr << "获取ORACLEServer ServerName失败" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer ServerName : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"UserName",tempchar))
	//{
	//	cerr << "获取ORACLEServer UserName失败" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer UserName : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"UserPassWord",tempchar))
	//{
	//	cerr << "获取ORACLEServer UserPassWord失败" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer UserPassWord : " << temp << endl;
	//}

	system("pause");
	return 0;

}