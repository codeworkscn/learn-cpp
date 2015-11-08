#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#define MAX_NET_INT_COUNT 64

#pragma comment(lib, "Iphlpapi.lib")

CRITICAL_SECTION myCS;

void WriteLog(char* pMsg)
{
	// write error or other information into log file
	::EnterCriticalSection(&myCS);
	try
	{
		SYSTEMTIME oT;
		::GetLocalTime(&oT);
		FILE* pLog = fopen("netmonitor.log","a");
		fprintf(pLog,"%04d-%02d-%02d, %02d:%02d:%02d   %s\n",
			oT.wYear,oT.wMonth,oT.wDay,oT.wHour,oT.wMinute,oT.wSecond,pMsg); 
		fclose(pLog);
	} catch(...) {}
	::LeaveCriticalSection(&myCS);
}

DWORD WINAPI PrintNetInfo(LPVOID lpParameter)
{
	DWORD dwIn0[MAX_NET_INT_COUNT] = {0}, 
		dwIn1[MAX_NET_INT_COUNT] = {0},
		dwInPSec[MAX_NET_INT_COUNT] = {0};

	DWORD dwOut0[MAX_NET_INT_COUNT] = {0},
		dwOut1[MAX_NET_INT_COUNT] = {0},
		dwOutPSec[MAX_NET_INT_COUNT] = {0};
	BOOL First = TRUE;
	DWORD dwIntNum = 0;

	float dwNetIn = 0, dwNetOut = 0;

	// Declare and initialize variables.

	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	int i;

	/* variables used for GetIfTable and GetIfEntry */
	MIB_IFTABLE *pIfTable;
	MIB_IFROW *pIfRow;

	// Allocate memory for our pointers.
	pIfTable = (MIB_IFTABLE *) malloc(sizeof (MIB_IFTABLE));
	if (pIfTable == NULL) 
	{
		WriteLog("[ERROR] : Error allocating memory needed to call GetIfTable");
		return 1;
	}
	// Make an initial call to GetIfTable to get the
	// necessary size into dwSize
	dwSize = sizeof (MIB_IFTABLE);
	if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) 
	{
		free(pIfTable);
		pIfTable = (MIB_IFTABLE *) malloc(dwSize);
		if (pIfTable == NULL) 
		{
			WriteLog("[ERROR] : Error allocating memory needed to call GetIfTable");
			return 1;
		}
	}
	// Make a second call to GetIfTable to get the actual
	// data we want.
	while (true)
	{
		if ((dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE)) == NO_ERROR) 
		{		
			if (pIfTable->dwNumEntries > MAX_NET_INT_COUNT)
			{
				dwIntNum = MAX_NET_INT_COUNT;
			}
			else
			{
				dwIntNum = pIfTable->dwNumEntries;
			}

			//printf("\tNum Entries: %ld\n\n", pIfTable->dwNumEntries);
			for (i = 0; i < (int) dwIntNum; i++) 
			{
				pIfRow = (MIB_IFROW *) & pIfTable->table[i];

				if(First)
				{
					dwIn1[i] = dwIn0[i] = pIfRow->dwInOctets;
					dwInPSec[i] = 0;

					dwOut1[i] = dwOut0[i] = pIfRow->dwOutOctets;
					dwOutPSec[i] = 0;					
				}
				else
				{
					dwIn1[i] = pIfRow->dwInOctets;
					dwInPSec[i] = dwIn1[i] - dwIn0[i];
					dwIn0[i] = dwIn1[i];

					dwOut1[i] = pIfRow->dwOutOctets;
					dwOutPSec[i] = dwOut1[i] - dwOut0[i];
					dwOut0[i] = dwOut1[i];
					//printf("Interface %ld NetDown = %ld kb/s \n", i, dwInPSec[i]/1000);
					//printf("Interface %ld NetUp = %ld kb/s \n", i, dwOutPSec[i]/1000);
				}				
			}
			if(First)
			{
				First = FALSE;
			}
			else
			{
				dwNetIn = 0;
				dwNetOut = 0;
				for(DWORD i=0; i< dwIntNum; i++)
				{
					dwNetIn += (float)dwInPSec[i]/1000;
					dwNetOut += (float)dwOutPSec[i]/1000;
				}

				printf("Total NetDown = %f kb/s \n", dwNetIn);
				printf("Total NetUp = %f kb/s \n", dwNetOut);
			}
		} 
		else 
		{
			WriteLog("[ERROR] : GetIfTable failed with error");
			if (pIfTable != NULL) 
			{
				free(pIfTable);
				pIfTable = NULL;
			}  
			return 1;
		}
		Sleep(1000);
	}
	if (pIfTable != NULL) 
	{
		free(pIfTable);
		pIfTable = NULL;
	}
	return 0;
}


int main(void)
{

	PrintNetInfo(NULL);

};