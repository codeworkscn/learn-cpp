#include <iostream>
#include "../19.XDDll/XDDLL.h"

using namespace std;


long main()
{
	long nRet = 0;

	HRECORDSET mhrecordset = 0;

	for (long i=1;i<100;i++)
	{
		mhrecordset = QueryHandleValues(0);
	}
	
	if (mhrecordset < 0)
	{
		cout << "��ʼ�������ʧ�ܣ��ڴ��쳣��" << endl;
		system("pause");
		return -1;
	}
	else
	{
		cout << "��ʼ��������ɹ��� ��������Ϊ " << mhrecordset << endl;
	}

	long start = 0;
	long* ml = new long[1000];
	long count = 1000;
	long times = 0;

	while (1)
	{
		nRet = GetNextValues(mhrecordset,&start,ml,&count);
		
		if (nRet < 0)
		{
			cout << "�����ˣ�����������Ч! " << endl;
			break;
		}
		//for (long i = 0 ; i < count ; i++)
		//{
		//	cout <<	"the num is : " << ml[i] << endl;
		//}
		cout << "�� " << ++times << " ��ȡ1000������ɣ���ȡ�� "  << count << " ������" << endl;
		if (nRet == SGRDC_HRECORDSET_GET_ALL)
		{
			break;
		}	
	}

	for (long i=0;i<100;i++)
	{
		ReleaseHRecordset(i);
	}
	

	system("pause");

	return 0;
}