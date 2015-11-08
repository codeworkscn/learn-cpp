#include "Includes.h"

int main(void)
{

	ofstream out("tst.txt");

	out << "haha"  << endl;

	out << "你好啊" << endl;

	out << "我  想  你  啦 " << endl;

	

	out.close();

	char chabuf[64];

	ifstream inf("tst.txt");

	while (inf)
	{
		inf.getline (chabuf,sizeof(chabuf),'\n') ;			//一行一行读取
		cout << "strlen chabuf:  "<<  strlen (chabuf) << " " << chabuf << endl;
	}


	inf.close();

	system("pause");

	return 0;
}
