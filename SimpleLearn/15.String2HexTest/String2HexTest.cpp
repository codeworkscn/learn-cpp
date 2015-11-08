#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void String2HexString(char* stringData , long stringLenth);

int main(void)
{

	char data0[1024];

	while (1)
	{
		for (long i=0;i<1024;i++)
		{
			data0[i] = rand()%255;
		}

		String2HexString(data0,1024);

		cout << data0 << endl;
	}

	system("pause");
	return 0;
}

/************************************************************************/
/* 
功能：char*数据，固定长度，转化为16进制字符串。
	由于长度要求变化，将stringLength/2部分转化为stringLenth长度的16进制
输入输出参数：stringData
输入参数:stringLenth
*/
/************************************************************************/
void String2HexString(char* stringData , long stringLenth)
{
	unsigned char* tempStringData = new unsigned char[stringLenth];
 	memcpy_s(tempStringData,stringLenth,stringData,stringLenth);
 	long realLenth  = stringLenth/2;
 	long tempValue = 0;
 	char tempdata[8];
 	for (long i=0;i<realLenth;i++)
 	{
 		tempValue = tempStringData[i];
 		sprintf_s(tempdata,8,"%02X",tempValue);
 		stringData[i*2] = tempdata[0];
 		stringData[i*2+1] = tempdata[1];
 	}
 	stringData[stringLenth-2]=0;
 	stringData[stringLenth-1]=0;
	delete[] tempStringData;
}