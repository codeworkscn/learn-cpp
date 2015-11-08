#include<iostream>

using namespace std;


void GetLowTest(void)
{
	long long i = 0x000000017FFFFFFF;
	cout << "i(64) = " << i << endl;
	long j = 0;
	j = *((long*)&i);
	cout << "j(32L) = " << j << endl;
	j = *((long*)&i+1);
	cout << "j(32H) = " << j << endl;
}

void GetGlobalIDTest()
{
	long id = 1234;
	long long ids = id;
	long nodeid = 1;
	ids += (long long)nodeid << 32;
	cout << "ids = " << ids << endl;
	return;
}