/************************************************************************/
/* ���ڲ���ID�������
	2010-11-18 10:42:10
	��Сΰ
*/
/************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int GetID(long* ids,long count)
{
	long reID = 0;
	if (0 == count)//���û�е�
	{
		return 1;
	}
	sort(ids,ids+count);//����
	if (ids[0] < 1)
	{
		return -1;
	}
	if (ids[0] > 1)//�����С�ĵ�ID����1
	{
		return 1;
	}
	for (long i = 1 ; i < count ; i ++)
	{
		if (ids[i] - ids[i-1] > 1)//�������һ��ID��1����
		{
			reID = ids[i-1] + 1;//��ô������һ��ID��1
			break;
		}
	}
	if (reID == 0)//�������û���ֵ�ID��˵����Ŷ��Ǵ�1��ʼ������
	{
		reID = count + 1;//��ô�м���ID���ͷָ����ID��
	}
	return reID;
}

int main(void)
{
	long mID = 0;
	long ids[16]={1,3,4,9,6,24};

	mID = GetID(ids,0);
	if (mID < 0)
	{
		cout << "��ȡIDʧ�ܣ�����Ƿ���������룺 " << mID << endl;
	}
	cout << "mID = " << mID << endl << endl;
	for (long i =0;i<10;i++)
	{
		mID = GetID(ids,6 + i);
		for (long j=0;j<i+6;j++)
		{
			cout << ids[j] << " " ;
		}
		cout << endl << "�õ���IDֵΪ: " << mID  << endl;
		ids[6+i] = mID;

	}
	system("pause");
	return 0 ;
}