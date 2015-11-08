#include <iostream>
#include <Windows.h>


#define ErrorHandler(msg) std::cout << msg << std::endl;return -1

int main()
{

	HGLOBAL hResLoad;     // handle to loaded resource 
	HMODULE hExe;        // handle to existing .EXE file 
	HRSRC hRes;         // handle/ptr. to res. info. in hExe 
	HANDLE hUpdateRes;  // update resource handle 
	void *lpResLock;    // pointer to resource data 
	BOOL result; 
	// Load the .EXE file that contains the dialog box you want to copy. 
	hExe = LoadLibrary("hand.exe"); 
	if (hExe == NULL) 
	{ 
		ErrorHandler("Could not load exe."); 
	} 

	// Locate the dialog box resource in the .EXE file. 
	hRes = FindResource(hExe, "AboutBox", RT_DIALOG); 
	if (hRes == NULL) 
	{ 
		ErrorHandler("Could not locate dialog box."); 
	} 

	// Load the dialog box into global memory. 
	hResLoad = LoadResource(hExe, hRes); 
	if (hResLoad == NULL) 
	{ 
		ErrorHandler("Could not load dialog box."); 
	} 

	// Lock the dialog box into global memory. 
	lpResLock = LockResource(hResLoad); 
	if (lpResLock == NULL) 
	{ 
		ErrorHandler("Could not lock dialog box."); 
	} 

	// Open the file to which you want to add the dialog box resource. 
	hUpdateRes = BeginUpdateResource("foot.exe", FALSE); 
	if (hUpdateRes == NULL) 
	{ 
		ErrorHandler("Could not open file for writing."); 
	} 

	// Add the dialog box resource to the update list. 
	result = UpdateResource(hUpdateRes,       // update resource handle 
		RT_DIALOG,                   // change dialog box resource 
		"AboutBox",                  // dialog box name 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
		lpResLock,                   // ptr to resource info 
		SizeofResource(hExe, hRes)); // size of resource info. 
	if (result == FALSE) 
	{ 
		ErrorHandler("Could not add resource."); 
	} 

	// Write changes to FOOT.EXE and then close it. 
	if (!EndUpdateResource(hUpdateRes, FALSE)) 
	{ 
		ErrorHandler("Could not write changes to file."); 
	} 

	// Clean up. 
	if (!FreeLibrary(hExe)) 
	{ 
		ErrorHandler("Could not free executable."); 
	} 

};