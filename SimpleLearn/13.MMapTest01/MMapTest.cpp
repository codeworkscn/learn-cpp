//this cpp file is just for test

#include <iostream>
#include "PutHisData.h"
#include "windows.h"

using namespace std;

void main()
{
	//InterfaceStruct ifs;

	byte mData[1024];
	for (long j=0;j<1024;j++)
	{
		mData[j] = (byte)rand()/256;
	}

	InterfaceStruct ifs;
	memset(&ifs,0,sizeof(InterfaceStruct));
	strcpy_s(ifs.name,MAX_NAME_LEN,"interface#kgbw");

	PutHisDataClass puthisdata(ifs);

	puthisdata.PutMemMap(mData,0,1024);

	cout << "PutMemMap Success !" << endl;

//	unsigned char szResult[1024];

// 	DWORD nRet = GetMapMemory(szResult,1024,"interface#kgbw");
// 
// 	if (nRet)
// 	{
// 		cout << "error!" << endl;
// 	}
// 	else
// 	{
// 		cout << "SUCCESS!" << endl;
// 	}


	system("pause");
	return;
}