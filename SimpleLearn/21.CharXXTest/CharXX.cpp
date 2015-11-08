#include <iostream>

#include "CharXX.h"

using namespace std;

typedef char TAG_NAME[64];

long CharXXTest(const TAG_NAME * strArray,long count)
{
	
	if (NULL == strArray || count < 1)
	{
		return -1;
	}	
	for (long i = 0 ;i < count ; i++ )
	{
		cout << "str[" << i << "] : " << strArray[i] << endl;
	}
	return 0;
}


int main(void)
{

	const char strArray[4][64] =
	{
		"�ɻ��ɻ�����",
		"̹��̹��û��",
		"��ֽ��ֽƯ��",
		"˧��˧���ѿ�"
	};

	long nRet = CharXXTest (
	strArray,
	4);

	if (nRet)
	{
		cout << "error!!!" << endl;
	}

	system ("pause");
	return 0;
}