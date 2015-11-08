#include "StdInOutTest.h"

#include <iostream>

using namespace std;

StdInOutTest::StdInOutTest(void)
{
}

StdInOutTest::~StdInOutTest(void)
{
}


void StdInOutTest::CinTest(void)
{

}

void StdInOutTest::CoutTest(void)
{
	const char* teststr = "this is a cout test string."; 
	int maxlengh = strlen (teststr);

	for (int length = 1;length <= maxlengh ;length ++)
	{
		cout.write (teststr,length) << endl;
	}
	cout << "for wait" << endl;


	cout << "numeric : " << true <<" or " << false << endl ;              // 1 or 0
	cout << "literals : " << boolalpha << true << " or " << false << endl ; // true or false
	cout << "literals : " << boolalpha << 0 << endl ;                     // 0    ԭ��: 0 ��cout�в��ȼ��� false

	cout << "numeric : " << noboolalpha << true <<" or " << false << endl ;// 1 or 0

	const int ival = 17 ;        // 'ival' is constant, so value never change
	cout << "oct : " << oct << ival <<endl ;     // 21 : 8 ����
	cout << "dec : " << dec << ival <<endl ;     // 17 : 10 ����
	cout << "hex : " << hex << ival <<endl ;     // 11 : 16 ����
	cout << "hex : " << hex << 17.01 <<endl ;    // 17.01 : ����Ӱ��

	cout <<showbase ;                            // Show base when printing integral values
	cout << "oct : " << oct << ival <<endl ;     // 021 : 8 ����
	cout << "dec : " << dec << ival <<endl ;     // 17	: 10 ����
	cout << "hex : " << hex << ival <<endl ;     // 0x11 : 16 ����
	cout << "hex : " << hex << 17.01 <<endl ;    // 17.01 : ����Ӱ��
	cout << noshowbase ;                         // Reset state of the stream
}