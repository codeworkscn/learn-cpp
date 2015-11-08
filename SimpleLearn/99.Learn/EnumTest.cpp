#include <iostream>

using namespace std ;

enum mEnum
{
	AAA = 100000,
	BBB,
	CCC,
	DDD
};	

void EnumTest(void)
{

	long i = 0 ;
	i  = AAA;
	mEnum j = BBB;
	cout << "i = " << i << endl;
}