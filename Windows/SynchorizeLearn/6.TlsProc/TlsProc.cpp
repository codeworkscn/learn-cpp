// The process code

#include <windows.h> 
#include <stdio.h> 

#define THREADCOUNT 4
#define DLL_NAME    TEXT("6.TlsDll")

#ifdef _DEBUG
#pragma comment(lib,"../debug/6.tlsdll.lib")
#else
#pragma comment(lib,"../release/6.tlsdll.lib")
#endif



VOID ErrorExit(LPSTR); 

extern "C" BOOL WINAPI StoreData(DWORD dw);
extern "C" BOOL WINAPI GetData(DWORD *pdw);

DWORD WINAPI ThreadFunc(VOID) 
{   
	int i;

	if(!StoreData(GetCurrentThreadId()))
		ErrorExit("StoreData error");

	for(i=0; i<5; i++)
	{
		DWORD dwOut;
		if(!GetData(&dwOut))
			ErrorExit("GetData error");
		if( dwOut != GetCurrentThreadId())
			printf("thread %d: data is incorrect (%d)\n", GetCurrentThreadId(), dwOut);
		else printf("thread %d: data is correct\n", GetCurrentThreadId());
		Sleep(0);
	}
	return 0; 
} 

int main(VOID) 
{ 
	DWORD IDThread; 
	HANDLE hThread[THREADCOUNT]; 
	int i; 

	// Load the DLL

	LoadLibrary(DLL_NAME);

	// Create multiple threads. 

	for (i = 0; i < THREADCOUNT; i++) 
	{ 
		hThread[i] = CreateThread(NULL, // default security attributes 
			0,                           // use default stack size 
			(LPTHREAD_START_ROUTINE) ThreadFunc, // thread function 
			NULL,                    // no thread function argument 
			0,                       // use default creation flags 
			&IDThread);              // returns thread identifier 

		// Check the return value for success. 
		if (hThread[i] == NULL) 
			ErrorExit("CreateThread error\n"); 
	} 

	WaitForMultipleObjects(THREADCOUNT, hThread, TRUE, INFINITE); 

	return 0; 
} 

VOID ErrorExit (LPSTR lpszMessage) 
{ 
	fprintf(stderr, "%s\n", lpszMessage); 
	ExitProcess(0); 
}