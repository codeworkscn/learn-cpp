//#include "MutexTest.h"

#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 2

HANDLE ghMutex; 

DWORD WINAPI WriteToDatabase( LPVOID );

void main()
{
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	int i;

	// Create a mutex with no initial owner

	ghMutex = CreateMutex( 
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL) 
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return;
	}

	// Create worker threads
	for( i=0; i < THREADCOUNT; i++ )
	{
		aThread[i] = CreateThread( 
			NULL,       // default security attributes
			0,          // default stack size
			(LPTHREAD_START_ROUTINE) WriteToDatabase, 
			NULL,       // no thread function arguments
			0,          // default creation flags
			&ThreadID); // receive thread identifier

		if( aThread[i] == NULL )
		{
			printf("CreateThread error: %d\n", GetLastError());
			return;
		}
	}

	// Wait for all threads to terminate

	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// Close thread and mutex handles

	for( i=0; i < THREADCOUNT; i++ )
		CloseHandle(aThread[i]);

	CloseHandle(ghMutex);
}

DWORD WINAPI WriteToDatabase( LPVOID lpParam )
{ 
	DWORD dwCount=0, dwWaitResult; 
	DWORD time_out = 30;	//time_out Milliseconds while WaitForSingleObject
	DWORD sleep_time = 29;	//sleep_time Milliseconds while WritetoDatabase

	// Request ownership of mutex.

	while( dwCount < 10 )
	{
// 		dwWaitResult = WaitForSingleObject( 
// 			ghMutex,    // handle to mutex
// 			INFINITE);  // no time-out interval

		dwWaitResult = WaitForSingleObject( 
			ghMutex,    // handle to mutex
			time_out);	//wait for time_out Milliseconds

// 		dwWaitResult = WaitForSingleObject( 
// 			ghMutex,    // handle to mutex
// 			IGNORE);	//ignore

		switch (dwWaitResult) 
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0: 
			__try { 
				// TODO: Write to the database
				printf("Thread %d writing to database...\n", 
					GetCurrentThreadId());
				dwCount++;
 				Sleep (sleep_time);
			} 
			__finally { 
				// Release ownership of the mutex object
				if (! ReleaseMutex(ghMutex)) 
				{ 
					// Deal with error.
					printf("Thread %d ReleaseMutex error!\n",
						GetCurrentThreadId ());
				} 
			} 
			break; 

			// The thread got ownership of the mutex time-out
		case WAIT_TIMEOUT:
			{
				// Deal with error.
				printf("Thread %d WaitForSingleObject time-out! dwWaitResult = 0X%08X\n",
					GetCurrentThreadId (),dwWaitResult);
			}
			break;

			// The thread got ownership of an abandoned mutex
		case WAIT_ABANDONED: 
			{
				// Deal with error.
				printf("Thread %d got ownership of an abandoned mutex!\n",
					GetCurrentThreadId ());
			}
			return FALSE;

			//The WaitForSingleObject function failed
		case WAIT_FAILED :
			{
				// Deal with error.
				printf("The WaitForSingleObject function failed!\n");
			}
			return FALSE; 

		default:
			break;
		}
	}
	return TRUE; 
}