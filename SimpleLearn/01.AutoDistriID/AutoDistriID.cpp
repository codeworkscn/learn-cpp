/************************************************************************/
/* 用于测试ID分配策略
	2010-11-18 10:42:10
	陈小伟
*/
/************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int GetID(long* ids,long count)
{
	long reID = 0;
	if (0 == count)//如果没有点
	{
		return 1;
	}
	sort(ids,ids+count);//排序
	if (ids[0] < 1)
	{
		return -1;
	}
	if (ids[0] > 1)//如果最小的点ID不是1
	{
		return 1;
	}
	for (long i = 1 ; i < count ; i ++)
	{
		if (ids[i] - ids[i-1] > 1)//如果比上一个ID大1以上
		{
			reID = ids[i-1] + 1;//那么就是上一个ID加1
			break;
		}
	}
	if (reID == 0)//如果还是没被分到ID，说明序号都是从1开始连续的
	{
		reID = count + 1;//那么有几个ID，就分给这个ID号
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
		cout << "获取ID失败，输入非法！错误代码： " << mID << endl;
	}
	cout << "mID = " << mID << endl << endl;
	for (long i =0;i<10;i++)
	{
		mID = GetID(ids,6 + i);
		for (long j=0;j<i+6;j++)
		{
			cout << ids[j] << " " ;
		}
		cout << endl << "得到的ID值为: " << mID  << endl;
		ids[6+i] = mID;

	}
	system("pause");
	return 0 ;
}