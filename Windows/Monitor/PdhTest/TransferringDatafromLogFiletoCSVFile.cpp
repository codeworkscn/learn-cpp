#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#include "PdhConfig.h"

void
DisplayCommandLineHelp ()
{
	_tprintf (TEXT("\nSyntax: convertlog <input file name>"));
	_tprintf (TEXT("          <output file name>"));
	_tprintf (TEXT("\n\nThe input log file must be in the Perfmon"));
	_tprintf (TEXT("\nformat. The output log file will be in the"));
	_tprintf (TEXT("\nCSV file format."));
	return;
}

int __cdecl _tmain (int argc, TCHAR **argv)
{

	HQUERY          hQuery;
	HLOG            hOutputLog;
	PDH_STATUS      pdhStatus;
	DWORD           dwOutputLogType = PDH_LOG_TYPE_CSV;
	HCOUNTER        hCounter;
	TCHAR           szCounterPath[45] = 
		TEXT("\\Processor(0)\\% Processor Time");

	if (argc != 3)
	{
		DisplayCommandLineHelp ();
		return -1;
	}

	// Create the query object using the input log file.
	pdhStatus = PdhOpenQuery (argv[1],
		0,
		&hQuery);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhOpenQuery failed with %ld\n"), pdhStatus);
		goto cleanup;
	}

	// Add the counter to the query object.
	pdhStatus = PdhAddCounter (hQuery,
		szCounterPath,
		0,
		&hCounter);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhAddCounter failed with %ld\n"), pdhStatus);
		goto cleanup;
	}

	// Create and open the output log file.
	pdhStatus = PdhOpenLog (argv[2], 
		PDH_LOG_WRITE_ACCESS | 
		PDH_LOG_CREATE_ALWAYS,
		&dwOutputLogType,
		hQuery,
		0, 
		NULL,
		&hOutputLog);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhOpenLog failed with %ld\n"), pdhStatus);
		goto cleanup;
	}

	// Transfer the log records from the input file to the output file.
	while (ERROR_SUCCESS == pdhStatus) 
	{ 
		pdhStatus = PdhUpdateLog (hOutputLog, 
			TEXT("This is a comment."));
	}

	if (PDH_NO_MORE_DATA != pdhStatus)
	{
		_tprintf(TEXT("PdhUpdateLog failed with %ld\n"), pdhStatus);
	}

cleanup:

	// Close the output log file.
	if (hOutputLog)
		PdhCloseLog (hOutputLog, 0);

	// Close the query object and input log file.
	if (hQuery)
		PdhCloseQuery (hQuery);

	return pdhStatus;
}