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
���ܣ�char*���ݣ��̶����ȣ�ת��Ϊ16�����ַ�����
	���ڳ���Ҫ��仯����stringLength/2����ת��ΪstringLenth���ȵ�16����
�������������stringData
�������:stringLenth
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