#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include "INIRead.h"



INIREAD(long) SGRDC_Get_INI_Info(/*IN*/const wchar_t *name,
								 /*IN*/const wchar_t *info,
								 /*OUT*/wchar_t *iniName)
{
	const int nBufferSize = 1024;
	wchar_t pServiceName[nBufferSize];
	wchar_t pName[nBufferSize];
	GetCurrentDirectory(nBufferSize,pServiceName);
	swprintf(pName,nBufferSize,L"%s\\SGRDC_Config.ini",pServiceName);
	DWORD ret = GetPrivateProfileString(name,info,L"",iniName,nBufferSize,pName);
	if(!ret)
	{
		return ERROR_GET_ERROR;
	}
	return SUCCESS_GET_SUCCESS;
}
