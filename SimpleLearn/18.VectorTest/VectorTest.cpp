#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "VectorTest.h"

using namespace std;

typedef vector<long long> LLVector;
typedef vector<TestStruct> TestStructVector;

TestStructVector mtVector;

int VectorMemoryTest(void)
{

	TestStruct mtStruct;
	memset(&mtStruct,0,sizeof(TestStruct));
	long maxtimes =1000;
	long timecount = maxtimes;
	string inputchar;
	while (timecount--)
	{
		for (long i=0;i<1024*128;i++)
		{
			mtVector.push_back(mtStruct);
		}
		cout<<" the " << maxtimes - timecount << " times push_backs (\"e\" to exit)/ " ;
		cin >> inputchar;
		if (inputchar == "e" || inputchar == "E")
		{
			break;
		}
		mtVector.clear();
		cout<<" the " << maxtimes - timecount << " times clear vector size is :" << mtVector.size() << " (\"e\" to exit) / ";
		cin >> inputchar;

		if (inputchar == "e" || inputchar == "E")
		{
			break;
		}
		//system("pause");

	}
	return 0;
}


int VecterAsArrayTest(void)
{
	LLVector lvr;

	lvr.push_back(1);
	lvr.push_back(2);
	lvr.push_back(3);

	long long ls[3];

	memcpy(ls,&lvr[0],sizeof(long long)*3);

	cout << "ls[0]: " << ls[0] << endl;
	cout << "ls[1]: " << ls[1] << endl;
	cout << "ls[2]: " << ls[2] << endl;
	

	system("pause");
	return 0;
}


int VectorReserveTest(void)
{
	typedef vector<int> IntVector;

	int count = 1;

	int* countPtr = &count;

	IntVector tv;

	cout << "--------------------------" << endl;
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;

	tv.reserve (1);
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;

	tv.reserve (*countPtr / 10);
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;

	tv.push_back (1234);
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;

	tv.push_back (4321);
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;


	tv.reserve (16);
	cout << "tv.size() = " << tv.size() << endl;
	cout << "tv.capacity () = " << tv.capacity () << endl;
	cout << "--------------------------" << endl;


	return 0;
}