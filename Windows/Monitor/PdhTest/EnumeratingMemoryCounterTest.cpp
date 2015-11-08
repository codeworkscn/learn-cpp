#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE  1
#endif
#define tmain     wmain
#else
#define tmain     main
#endif


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>


#include <iostream>
#include <vector>
using namespace std;

#include "PdhConfig.h"

#define SAMPLE_INTERVAL_MS  1000


struct MemoryCounter
{
	string		name	;//名称
	HCOUNTER	counter	;//计数值
};

typedef vector<MemoryCounter> MemoryCounters;

int
tmain ()
{
	PDH_STATUS  pdhStatus               = ERROR_SUCCESS;
	LPTSTR      szCounterListBuffer     = NULL;
	DWORD       dwCounterListSize       = 0;
	LPTSTR      szInstanceListBuffer    = NULL;
	DWORD       dwInstanceListSize      = 0;
	LPTSTR      szThisInstance          = NULL;
	LPTSTR      szCounterInstance       = NULL;
	SYSTEMTIME      stSampleTime;


	const LPTSTR CategoryName = TEXT("Memory");

	// Determine the required buffer size for the data. 
	pdhStatus = PdhEnumObjectItems (
		NULL,                   // real time source
		NULL,                   // local machine
		CategoryName,        // object to enumerate
		szCounterListBuffer,    // pass NULL and 0
		&dwCounterListSize,     // to get length required
		szInstanceListBuffer,   // buffer size 
		&dwInstanceListSize,    // 
		PERF_DETAIL_WIZARD,     // counter detail level
		0); 

	DWORD counter_num = 0;

	MemoryCounters	counters	;

	if (pdhStatus == PDH_MORE_DATA) 
	{
		// Allocate the buffers and try the call again.
		szCounterListBuffer = (LPTSTR)malloc (
			(dwCounterListSize * sizeof (TCHAR)));
		szInstanceListBuffer = (LPTSTR)malloc (
			(dwInstanceListSize * sizeof (TCHAR)));

		if ((szCounterListBuffer != NULL) &&
			(szInstanceListBuffer != NULL)) 
		{
			pdhStatus = PdhEnumObjectItems (
				NULL,                 // real time source
				NULL,                 // local machine
				CategoryName,		 // object to enumerate
				szCounterListBuffer,  // buffer to receive counter list
				&dwCounterListSize, 
				szInstanceListBuffer, // buffer to receive instance list 
				&dwInstanceListSize,    
				PERF_DETAIL_WIZARD,   // counter detail level
				0);

			if (pdhStatus == ERROR_SUCCESS) 
			{
				_tprintf (TEXT("\n\nCounter Enumerating %s:"),CategoryName);
				for (szCounterInstance = szCounterListBuffer;
					*szCounterInstance != 0;
					szCounterInstance += lstrlen(szCounterInstance) + 1) 
				{
					_tprintf (TEXT("\n  %s"), szCounterInstance);
					counter_num ++;

					MemoryCounter	tempcounter	;
					tempcounter.name = "\\";
					tempcounter.name += CategoryName;
					tempcounter.name += "\\";
					tempcounter.name += szCounterInstance;
					counters.push_back (tempcounter);
				}
			}
			else 
			{
				_tprintf(TEXT("\nPdhEnumObjectItems failed with %ld."), pdhStatus);
			}
		} 
		else 
		{
			_tprintf (TEXT("\nUnable to allocate buffers"));
			pdhStatus = ERROR_OUTOFMEMORY;
		}

	} 
	else 
	{
		_tprintf(TEXT("\nPdhEnumObjectItems failed with %ld.\n\n"), pdhStatus);
	}

	_tprintf(TEXT("\n\n"));

	HQUERY          hQuery;

	// Create a query.
	pdhStatus = PdhOpenQuery(NULL, NULL, &hQuery);
	if (ERROR_SUCCESS != pdhStatus)
	{
		_tprintf(TEXT("PdhOpenQuery failed with %ld.\n"), pdhStatus);
		goto cleanup;
	}

	for (unsigned int i = 0 ; i < counters.size (); i ++)
	{
		// Add the selected counter to the query.
		pdhStatus = PdhAddCounter (hQuery,
			counters[i].name.c_str(), 
			0, 
			&counters[i].counter);
		if (ERROR_SUCCESS != pdhStatus)
		{
			_tprintf(TEXT("PdhAddCounter [%s] failed with %ld.\n"), 
				counters[i].name.c_str(),pdhStatus);
			// 		goto cleanup;
		}
	}


	DWORD           ctrType;
	PDH_FMT_COUNTERVALUE   fmtValue;


	// Print counter values until a key is pressed.
	while (!_kbhit()) {

		// Wait one interval.
		Sleep(SAMPLE_INTERVAL_MS);

		// Get the sample time.
		GetLocalTime (&stSampleTime);

		// Get the current data value.
		pdhStatus = PdhCollectQueryData (hQuery);

		// Print the time stamp for the sample.
		_tprintf (
			TEXT("\n\"%2.2d/%2.2d/%4.4d %2.2d:%2.2d:%2.2d.%3.3d\":"),
			stSampleTime.wMonth, 
			stSampleTime.wDay, 
			stSampleTime.wYear,
			stSampleTime.wHour, 
			stSampleTime.wMinute, 
			stSampleTime.wSecond,
			stSampleTime.wMilliseconds);


		for (unsigned int i = 0 ; i < counters.size (); i ++)
		{
			// Compute a displayable value for the counter.
			pdhStatus = PdhGetFormattedCounterValue (counters[i].counter,
				PDH_FMT_DOUBLE,
				&ctrType,
				&fmtValue);

			if (pdhStatus == ERROR_SUCCESS)
			{
				_tprintf (TEXT("\n[%s]\t\t%f"), 
					counters[i].name.c_str(),fmtValue.doubleValue);
			}
			else
			{
				_tprintf(TEXT("\n[%s] PdhGetFormattedCounterValue failed with %ld.\n"),
					counters[i].name.c_str(),pdhStatus);
			}
		}
		_tprintf (TEXT("\n------------------------------------\n\n"));
	}

	if (szCounterListBuffer != NULL) 
		free (szCounterListBuffer);

	if (szInstanceListBuffer != NULL) 
		free (szInstanceListBuffer);

cleanup:

	system("pause");

	return pdhStatus;
}
