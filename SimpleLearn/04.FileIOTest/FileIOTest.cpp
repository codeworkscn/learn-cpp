#include "Includes.h"

int main(void)
{

	ofstream out("tst.txt");

	out << "haha"  << endl;

	out << "��ð�" << endl;

	out << "��  ��  ��  �� " << endl;

	

	out.close();

	char chabuf[64];

	ifstream inf("tst.txt");

	while (inf)
	{
		inf.getline (chabuf,sizeof(chabuf),'\n') ;			//һ��һ�ж�ȡ
		cout << "strlen chabuf:  "<<  strlen (chabuf) << " " << chabuf << endl;
	}


	inf.close();

	system("pause");

	return 0;
}
