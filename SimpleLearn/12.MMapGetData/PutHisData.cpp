// PutHisData.cpp

#include <afxinet.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "PutHisData.h"

/**************************************************************************************
*功能:		记录日志
*传入参数：	pMsg：要记录的信息
*返回值：	无
**************************************************************************************/
void PutHisDataClass::WriteLog(char* pMsg)
{
	::EnterCriticalSection(&myCS);
	try
	{
		SYSTEMTIME oT;
		::GetLocalTime(&oT);
		//FILE* pLog = fopen(pLogFile,"a");
		char szInfo[1024];
		HANDLE h = CreateFile(pLogFile,FILE_ALL_ACCESS,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if ( INVALID_HANDLE_VALUE != h )
		{
			DWORD num;
			SetFilePointer (h,0,NULL,FILE_END);
			sprintf_s(szInfo,1024,"%04d-%02d-%02d, %02d:%02d:%02d   %s\r\n",oT.wYear,oT.wMonth,oT.wDay,oT.wHour,oT.wMinute,oT.wSecond,pMsg); 
			WriteFile(h,szInfo,strlen(szInfo),&num,NULL);
			CloseHandle(h);
		}
		//fclose(pLog);
	} catch(...) {}
	::LeaveCriticalSection(&myCS);
}

/**************************************************************************************
*
*						向内存映射文件写入内容 
*
* 
*传入参数：
*			data：要写入到内存文件的数据
*			offset：距离内存映射文件的偏移量，应该小于VIEW_SIZE - sizeof(InterfaceStruct) 
*			size：要写入的数据的长度
*返回值：
*			未作处理
**************************************************************************************/
long PutHisDataClass::PutMemMap(void *data,long offset,long size)
{
	char szError[256];
	if ( NULL == hMapFile )
	{
		WriteLog("不能产生内存映射文件.");
		return -1;
	}
	PVOID pView = MapViewOfFile(
		hMapFile,               // Handle of the map object
		FILE_MAP_ALL_ACCESS,    // Read and write access
		0,                      // High-order DWORD of the file offset 
		VIEW_OFFSET,            // Low-order DWORD of the file offset 
		VIEW_SIZE               // The number of bytes to map to view
		);
	if (pView == NULL)
	{ 
		sprintf_s(szError,256,"Putmemmap failed . error.code is :%d." ,GetLastError());
		WriteLog(_T(szError));
	}
	else
	{
		if ( offset > VIEW_SIZE - sizeof(InterfaceStruct) )
		{
			//WriteLog("E文件超过1M!");
		}
		else
		{
			if( size> MAP_SIZE - sizeof(InterfaceStruct)  -offset)
				size = MAP_SIZE - sizeof(InterfaceStruct)  -offset;
			memcpy_s( (char*)pView+sizeof(InterfaceStruct)+offset ,MAP_SIZE-sizeof(InterfaceStruct)-offset,data,size);
		}
		UnmapViewOfFile(pView);
		pView = NULL;
	}
	return 0;
}

/**************************************************************************************
*
*					创建内存映射文件，并将配置信息写入到内存映射文件的头部
*	内存映射文件的名称是和服务名称一致的，可以保证每个服务都有不同的内存映射文件名称
*
* 
*传入参数：
*			ifs：配置文件信息
*
*返回值：
*			无
**************************************************************************************/
void PutHisDataClass::CreateMemMap(InterfaceStruct &ifs)
{
	PVOID pView = NULL;
	char FULL_MAP_NAME[256];
	char szError[256];
	sprintf_s(FULL_MAP_NAME,256,"%s%s",MAP_PREFIX,_strlwr(ifs.name));

	PSECURITY_DESCRIPTOR pSec = (PSECURITY_DESCRIPTOR)LocalAlloc(LMEM_FIXED, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if(!pSec)
	{
		sprintf_s(szError,256,"Security error.code is :%d.",GetLastError());
		WriteLog(_T(szError));
		return ;

	}
	if(!InitializeSecurityDescriptor(pSec, SECURITY_DESCRIPTOR_REVISION))
	{
		LocalFree(pSec);
		sprintf_s(szError,256,"Security error.code is :%d.",GetLastError());
		WriteLog(_T(szError));
		return ;
	}
	if(!SetSecurityDescriptorDacl(pSec, TRUE, NULL, TRUE))
	{
		LocalFree(pSec);
		sprintf_s(szError,256,"Security error.code is :%d.",GetLastError());
		WriteLog(_T(szError));
		return ;
	}
	SECURITY_ATTRIBUTES attr;
	attr.bInheritHandle = FALSE;
	attr.lpSecurityDescriptor = pSec;
	attr.nLength = sizeof(SECURITY_ATTRIBUTES);

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // Use paging file - shared memory
		&attr,                   // Default security attributes
		PAGE_READWRITE,         // Allow read and write access
		0,                      // High-order DWORD of file mapping max size
		MAP_SIZE,               // Low-order DWORD of file mapping max size
		FULL_MAP_NAME           // Name of the file mapping object
		);
	LocalFree(pSec);


	if (hMapFile == NULL) 
	{
		sprintf_s(szError,256,"CreateFileMapping %s error.code is :%d.",FULL_MAP_NAME ,GetLastError());
		WriteLog(_T(szError));
		return;
	}
	WriteLog(_T(FULL_MAP_NAME));

	pView = MapViewOfFile(
		hMapFile,               // Handle of the map object
		FILE_MAP_ALL_ACCESS,    // Read and write access
		0,                      // High-order DWORD of the file offset 
		VIEW_OFFSET,            // Low-order DWORD of the file offset 
		VIEW_SIZE               // The number of bytes to map to view
		);
	if (pView == NULL)
	{ 
		sprintf_s(szError,256,"MapViewOfFile failed %s error.code is :%d.",FULL_MAP_NAME ,GetLastError());
		WriteLog(_T(szError));
		if (hMapFile)
		{
			CloseHandle(hMapFile);
			hMapFile = NULL;
		}
	}
	else
	{
		memcpy_s(pView, VIEW_SIZE, (const void*)&ifs, sizeof(ifs));
		UnmapViewOfFile(pView);
	}
	return;
}

