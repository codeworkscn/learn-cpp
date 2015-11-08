#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define _SECOND 10000000		//100ns count per second

typedef struct _MYDATA {
	TCHAR *szText;
	DWORD dwValue;
} MYDATA;

VOID CALLBACK TimerAPCProc(
						   LPVOID lpArg,               // Data value
						   DWORD dwTimerLowValue,      // Timer low value
						   DWORD dwTimerHighValue )    // Timer high value
{
	MYDATA *pMyData = (MYDATA *)lpArg;

	_tprintf( TEXT("Message: %s\nValue: %d\n\n"), pMyData->szText,
		pMyData->dwValue );
	MessageBeep(0);
}

void main( void ) 
{
	HANDLE          hTimer;
	BOOL            bSuccess;
	__int64         qwDueTime;
	LARGE_INTEGER   liDueTime;
	MYDATA          MyData;

	MyData.szText = TEXT("This is my data");
	MyData.dwValue = 100;

	hTimer = CreateWaitableTimer(
		NULL,                   // Default security attributes
		FALSE,                  // Create auto-reset timer
		TEXT("MyTimer"));       // Name of waitable timer
	if (hTimer != NULL)
	{
		__try 
		{
			// Create an integer that will be used to signal the timer 
			// 5 seconds from now.
			qwDueTime = -5 * _SECOND;

			// Copy the relative time into a LARGE_INTEGER.
			liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
			liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );

			bSuccess = SetWaitableTimer(
				hTimer,           // Handle to the timer object
				&liDueTime,       // When timer will become signaled
				2000,             // Periodic timer interval of 2 seconds
				TimerAPCProc,     // Completion routine
				&MyData,          // Argument to the completion routine
				FALSE );          // Do not restore a suspended system

			if ( bSuccess ) 
			{
				for ( ; MyData.dwValue < 1000; MyData.dwValue += 100 ) 
				{
					SleepEx(
						INFINITE,     // Wait forever
						TRUE );       // Put thread in an alertable state
				}

			} 
			else 
			{
				printf("SetWaitableTimer failed with error %d\n",
					GetLastError());
			}

		} 
		__finally 
		{
			CloseHandle( hTimer );
		}
	} 
	else 
	{
		printf("CreateWaitableTimer failed with error %d\n",
			GetLastError());
	}
}


// int main()
// {
// 	HANDLE hTimer = NULL;
// 	LARGE_INTEGER liDueTime;
// 
// 	liDueTime.QuadPart=-20000000;	//2seconds
// 
// // 	liDueTime.QuadPart=-100000000;	//10seconds
// 	//10,000,0000 = 10 * 1000(ms/s)*1000(100ns/ms).
// 	//表示10秒，100ns单位。
// 
// 	// Create a wait able timer.
// 	hTimer = CreateWaitableTimer(NULL, TRUE, "WaitableTimer");//Create manual reset timer
// 	if (NULL == hTimer)
// 	{
// 		printf("CreateWaitableTimer failed (%d)\n", GetLastError());
// 		return 1;
// 	}
// 
// 	printf("Waiting for 10 seconds...\n");
// 
// 	// Set a timer to wait for 10 seconds.
// 	if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0))
// 	{
// 		printf("SetWaitableTimer failed (%d)\n", GetLastError());
// 		return 2;
// 	}
// 
// 	// Wait for the timer.
// 
// 	// 	if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
// 	if (WaitForSingleObject(hTimer, 2500) != WAIT_OBJECT_0)	//wait time_out=2.5seconds
// 	{
// 		printf("WaitForSingleObject failed (%d)\n", GetLastError());
// 	}
// 	else
// 	{
// 		printf("Timer was signaled.\n");
// 	}
// 
// 	return 0;
// }