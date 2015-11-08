#include<stdio.h>
#include <iostream>
#include <vector>

using namespace std;


struct Mstruct
{
	long i;
	char aa[128];
	double dd;
public:
	Mstruct()
	{
		i=0;
		strcpy_s(aa,128,"haha");
		dd=0.99;
	}
};
void VectorTest(void)
{

	vector<Mstruct> mVector;
	Mstruct nihao;
	for (int i=0;i<1000000;i++)
	{
		mVector.push_back(nihao);
		if (! (i%1000))
		{
			cout << "插入第 " << i  << " 个数据成功！" << endl;
		}
	}

}   