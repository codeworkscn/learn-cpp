#include <iostream>
#include <Windows.h>

using namespace std;


struct StackStruct
{
	char aa[1024];

	StackStruct()
	{
		ZeroMemory(aa,sizeof(aa));
	}
};


void StackHeapTest (void)
{

	//while length = 994 ,stack overflow!!
	const int length = 993 ;
	StackStruct st[length];



	for (int i =0 ;i < length ;i ++)
	{

		sprintf_s(st[i].aa,1024,"HeiheiHaha%08X",i);
	}

	for (int i =0 ;i < length ;i ++)
	{

		cout << st[i].aa << endl;
	}

	int i;
	cin >> i;
}