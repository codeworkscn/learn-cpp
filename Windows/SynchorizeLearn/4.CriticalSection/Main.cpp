#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 2

// Global variable
CRITICAL_SECTION CriticalSection; 


DWORD WINAPI ThreadProc( LPVOID );

void main()
{
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	int i;

	// Initialize the critical section one time only.
	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 
		0x80000400) ) 
		return;

	// Create worker threads
	for( i=0; i < THREADCOUNT; i++ )
	{
		aThread[i] = CreateThread( 
			NULL,       // default security attributes
			0,          // default stack size
			(LPTHREAD_START_ROUTINE) ThreadProc, 
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

	// Close thread handles
	for( i=0; i < THREADCOUNT; i++ )
		CloseHandle(aThread[i]);

	// Release resources used by the critical section object.
	DeleteCriticalSection(&CriticalSection);
}

DWORD WINAPI ThreadProc( LPVOID lpParameter )
{
	// Request ownership of the critical section.
	EnterCriticalSection(&CriticalSection); 

	// Access the shared resource.



	// Release ownership of the critical section.
	LeaveCriticalSection(&CriticalSection);

	return 0;
}