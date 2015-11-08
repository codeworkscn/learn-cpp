#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#include "PdhConfig.h"

void
DisplayCommandLineHelp ()
{
	_tprintf (TEXT("\nA valid log name must be specified as the")); 
	_tprintf (TEXT("\ncommand line argument."));
	return;
}

int __cdecl _tmain (int argc, TCHAR **argv)
{

	HQUERY          hQuery;
	HLOG            hLog;
	PDH_STATUS      pdhStatus;
	DWORD           dwLogType = PDH_LOG_TYPE_CSV;
	HCOUNTER        hCounter;
	TCHAR           szCounterPath[45] = 
		TEXT("\\Processor(0)\\% Processor Time");
	DWORD           dwCount;

	if (argc != 2) 
	{
		DisplayCommandLineHelp ();
		return -1;
	}

	// Open a query object.
	pdhStatus = PdhOpenQuery (NULL, 
		0, 
		&hQuery);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhOpenQuery failed with %ld\n"), pdhStatus);
		return -1;
	}

	// Add one counter that will provide the data.
	pdhStatus = PdhAddCounter (hQuery,
		szCounterPath,
		0,
		&hCounter);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhAddCounter failed with %ld\n"), pdhStatus);
		pdhStatus = PdhCloseQuery (hQuery);
		return -1;
	}

	// Open the log file for write access.
	pdhStatus = PdhOpenLog (argv[1], 
		PDH_LOG_WRITE_ACCESS | 
		PDH_LOG_CREATE_ALWAYS,
		&dwLogType,
		hQuery,
		0, 
		NULL,
		&hLog);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhOpenLog failed with %ld\n"), pdhStatus);
		pdhStatus = PdhCloseQuery (hQuery);
		return -1;
	}

	// Write 20 records to the log file.
	for (dwCount = 0; dwCount <= 20; dwCount++) 
	{
		pdhStatus = PdhUpdateLog (hLog, TEXT("This is a comment."));
		// Wait one second between samples for a counter update.
		Sleep(1000); 
	}

	// Close the log file.
	pdhStatus = PdhCloseLog (hLog, 0);

	// Close the query object.
	pdhStatus = PdhCloseQuery (hQuery);

	return 0;
}