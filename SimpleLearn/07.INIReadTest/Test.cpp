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
	//cout << "��ȡini�ļ�10000�γɹ�������ʱ: " << et - st << " ��" << endl;

	SGRDC_Get_INI_Info(L"SGRDCserver",L"IP",tempchar);

//	cout << tempchar << endl;


	//if(SGRDC_Get_INI_Info(L"SGRDCserver",L"IP",tempchar))
	//{
	//	cerr << "��ȡSGRDCserver IPʧ��" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "SGRDCserver IP : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"ServerName",tempchar))
	//{
	//	cerr << "��ȡORACLEServer ServerNameʧ��" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer ServerName : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"UserName",tempchar))
	//{
	//	cerr << "��ȡORACLEServer UserNameʧ��" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer UserName : " << temp << endl;
	//}

	//if(SGRDC_Get_INI_Info(L"ORACLEServer",L"UserPassWord",tempchar))
	//{
	//	cerr << "��ȡORACLEServer UserPassWordʧ��" << endl;
	//}
	//else
	//{
	//	wcstombs_s(&count,temp,64,tempchar,64);
	//	cerr << "ORACLEServer UserPassWord : " << temp << endl;
	//}

	system("pause");
	return 0;

}