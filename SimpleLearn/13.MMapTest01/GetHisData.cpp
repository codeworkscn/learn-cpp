
#include "PutHisData.h"


DWORD GetMapMemory(unsigned char *szResult,long len,const char* svcname)
{
	HANDLE hMapFile = NULL;
	PVOID pView = NULL;
	DWORD dwError = 0;
	char fullmapname[_MAX_FNAME+1];
	char tempsvcname[256];
	strcpy_s(tempsvcname,128,svcname);
	sprintf_s(fullmapname,_MAX_FNAME+1,"%s%s",MAP_PREFIX,strlwr((char*)tempsvcname));
	hMapFile = OpenFileMapping(
		FILE_MAP_READ,          // Read access
		FALSE,                  // Do not inherit the name
		fullmapname           // File mapping name 
		);
	if (hMapFile == NULL) 
	{
		dwError = GetLastError();
		goto Cleanup;
	}
	// Map a view of the file mapping into the address space of the current 
	// process.
	pView = MapViewOfFile(
		hMapFile,               // Handle of the map object
		FILE_MAP_READ,          // Read access
		0,                      // High-order DWORD of the file offset 
		VIEW_OFFSET,            // Low-order DWORD of the file offset
		VIEW_SIZE               // The number of bytes to map to view
		);
	if (pView == NULL)
	{
		dwError = GetLastError();
		goto Cleanup;
	}
	memcpy(szResult,pView,len);
	dwError = 0;
Cleanup:

	if (hMapFile)
	{
		if (pView)
		{
			UnmapViewOfFile(pView);
			pView = NULL;
		}
		CloseHandle(hMapFile);
		hMapFile = NULL;
	}
	return dwError;
}