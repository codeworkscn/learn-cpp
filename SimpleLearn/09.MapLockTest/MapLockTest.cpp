#include <iostream>
#include <map>
#include <afxmt.h>


using namespace std;

map<long,long> mMap;
HANDLE hMutex,hMutex1;

int InsertMap(long m_key,long m_value)
{
	DWORD dw = WaitForSingleObject(hMutex, INFINITE);
	mMap.insert(pair<long,long>(m_key,m_value));
	ReleaseMutex(hMutex); // �ͷ�hMutex�ĳ���Ȩ��ע���Ⲣ����ͬ��ɾ��Mutex����
	return 0;
}

int main(void)
{
	hMutex = CreateMutex (NULL, FALSE, "nihaoma");
	hMutex1 = CreateMutex (NULL, FALSE, "nihaoma");

	OpenMutex(NULL,false,"nihaoma");


	DWORD dw = WaitForSingleObject(hMutex, INFINITE);
	//mMap.insert(pair<long,long>(1,1));
	InsertMap(2,2);
	system("pause");
	return 0;
}