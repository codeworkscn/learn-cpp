#include <iostream>
#include <Windows.h>
#include <strsafe.h>

#define ErrorHandler(msg) std::cout << msg << std::endl;return -1

// Declare callback functions. 
BOOL EnumTypesFunc( 
				   HMODULE hModule, 
				   LPTSTR lpType, 
				   LONG lParam); 

BOOL EnumNamesFunc( 
				   HMODULE hModule, 
				   LPCTSTR lpType, 
				   LPTSTR lpName, 
				   LONG lParam); 

BOOL EnumLangsFunc( 
				   HMODULE hModule, 
				   LPCTSTR lpType, 
				   LPCTSTR lpName, 
				   WORD wLang, 
				   LONG lParam); 


char szBuffer[80]; // print buffer for EnumResourceTypes 
DWORD cbWritten;   // number of bytes written to res. info. file 
HANDLE hFile;

int main()
{
	size_t cbString;      // length of string in sprintf
	HRESULT hResult;
	HMODULE hExe;        // handle to existing .EXE file 

	// Load the .EXE whose resources you want to list. 
	hExe = LoadLibrary("sgrdp_cluster_server.exe"); 
	if (hExe == NULL) 
	{
		// Add code to fail as securely as possible.
		ErrorHandler("Could not LoadLibrary exe file ."); 
	} 

	// Create a file to contain the resource info. 
	hFile = CreateFile("resinfo.txt",      // name of file 
		GENERIC_READ | GENERIC_WRITE,      // access mode 
		0,                                 // share mode 
		(LPSECURITY_ATTRIBUTES) NULL,      // default security 
		CREATE_ALWAYS,                     // create flags 
		FILE_ATTRIBUTE_NORMAL,             // file attributes 
		(HANDLE) NULL);                    // no template 
	if (hFile == INVALID_HANDLE_VALUE) { 
		ErrorHandler("Could not open file."); 
	} 

	// Find all of the loaded file's resources.
	hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR),  
		// cbString = sprintf(szBuffer, 
		"The file contains the following resources:\n\n");
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		ErrorHandler("StringCchPrintf failure."); 
	}
	hResult = StringCchLength(szBuffer, 80/sizeof(TCHAR), &cbString);
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		ErrorHandler("StringCchLength failure."); 
	} 
	WriteFile(hFile,           // file to hold resource info. 
		szBuffer,              // what to write to the file 
		(DWORD) cbString,      // number of bytes in szBuffer 
		&cbWritten,            // number of bytes written 
		NULL);                 // no overlapped I/O 

	EnumResourceTypes(hExe,              // module handle 
		(ENUMRESTYPEPROC)EnumTypesFunc,  // callback function 
		0);                              // extra parameter 
	// Unload the executable file whose resources were 
	// enumerated and close the file created to contain 
	// the resource information. 
	FreeLibrary(hExe); 
	CloseHandle(hFile); 

};

//    FUNCTION: EnumTypesFunc(HANDLE, LPSTR, LONG) 
// 
//    PURPOSE:  Resource type callback 
BOOL EnumTypesFunc( 
				   HMODULE hModule,   // module handle 
				   LPTSTR lpType,    // address of resource type 
				   LONG lParam)      // extra parameter, could be 
				   // used for error checking 
{ 
	size_t cbString;
	HRESULT hResult;

	// Write the resource type to a resource information file. 
	// The type may be a string or an unsigned decimal 
	// integer, so test before printing. 
	if ((ULONG)lpType & 0xFFFF0000) 
	{ 
		hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR), "Type: %s\n", lpType);
		if (FAILED(hResult))
		{
			// Add code to fail as securely as possible.
			return FALSE;
		}
		// cbString = sprintf(szBuffer, "Type: %s\n", lpType); 
	} 
	else 
	{
		hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR), "Type: %u\n", (USHORT)lpType);
		if (FAILED(hResult))
		{
			// Add code to fail as securely as possible.
			return FALSE;
		}
		//        cbString = sprintf(szBuffer, "Type: %u\n", (USHORT)lpType); 
	} 
	hResult = StringCchLength(szBuffer, 80/sizeof(TCHAR), &cbString);
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		return FALSE;
	} 
	WriteFile(hFile, szBuffer, (DWORD) cbString, 
		&cbWritten, NULL); 
	// Find the names of all resources of type lpType. 
	EnumResourceNames(hModule, 
		lpType, 
		(ENUMRESNAMEPROC)EnumNamesFunc, 
		0); 

	return TRUE; 
} 

//    FUNCTION: EnumNamesFunc(HANDLE, LPSTR, LPSTR, LONG) 
// 
//    PURPOSE:  Resource name callback 
BOOL EnumNamesFunc( 
				   HMODULE hModule,   // module handle 
				   LPCTSTR lpType,   // address of resource type 
				   LPTSTR lpName,    // address of resource name 
				   LONG lParam)      // extra parameter, could be 
				   // used for error checking 
{ 
	size_t cbString; 
	HRESULT hResult;

	// Write the resource name to a resource information file. 
	// The name may be a string or an unsigned decimal 
	// integer, so test before printing. 
	if ((ULONG)lpName & 0xFFFF0000) 
	{
		hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR), "\tName: %s\n", lpName);
		if (FAILED(hResult))
		{
			// Add code to fail as securely as possible.
			return FALSE;
		}
		//        cbString = sprintf(szBuffer, "\tName: %s\n", lpName); 
	} 
	else 
	{
		hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR), "\tName: %u\n", (USHORT)lpName);
		if (FAILED(hResult))
		{
			// Add code to fail as securely as possible.
			return FALSE;
		} 
		//        cbString = sprintf(szBuffer, "\tName: %u\n", 
		// 			(USHORT)lpName); 
	}
	hResult = StringCchLength(szBuffer, 80/sizeof(TCHAR), &cbString);
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		return FALSE;
	} 

	WriteFile(hFile, szBuffer, (DWORD) cbString, 
		&cbWritten, NULL); 
	// Find the languages of all resources of type 
	// lpType and name lpName. 
	EnumResourceLanguages(hModule, 
		lpType, 
		lpName, 
		(ENUMRESLANGPROC)EnumLangsFunc, 
		0); 

	return TRUE; 
} 

//    FUNCTION: EnumLangsFunc(HANDLE, LPSTR, LPSTR, WORD, LONG) 
// 
//    PURPOSE:  Resource language callback 
BOOL EnumLangsFunc( 
				   HMODULE hModule,  // module handle 
				   LPCTSTR lpType,  // address of resource type 
				   LPCTSTR lpName,  // address of resource name 
				   WORD wLang,      // resource language 
				   LONG lParam)     // extra parameter, could be 
				   // used for error checking 
{ 
	HRSRC hResInfo; 
	char szBuffer[80]; 
	size_t cbString = 0; 
	HRESULT hResult;

	hResInfo = FindResourceEx(hModule, lpType, lpName, wLang); 
	// Write the resource language to the resource information file.
	hResult = StringCchPrintf(szBuffer, 80/sizeof(TCHAR), "\t\tLanguage: %u\n", (USHORT) wLang);
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		return FALSE;
	}
	hResult = StringCchLength(szBuffer, 80/sizeof(TCHAR), &cbString);
	if (FAILED(hResult))
	{
		// Add code to fail as securely as possible.
		return FALSE;
	} 
	//    cbString = sprintf(szBuffer, "\t\tLanguage: %u\n", (USHORT)wLang); 
	WriteFile(hFile, szBuffer, (DWORD) cbString, 
		&cbWritten, NULL); 
	// Write the resource handle and size to buffer. 
	cbString = sprintf(szBuffer, 
		"\t\thResInfo == %lx,  Size == %lu\n\n", 
		hResInfo, 
		SizeofResource(hModule, hResInfo)); 
	WriteFile(hFile, szBuffer, (DWORD) cbString, 
		&cbWritten, NULL); 
	return TRUE; 
} 
