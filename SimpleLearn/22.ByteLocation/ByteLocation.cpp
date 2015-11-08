/************************************************************************/
/* 
据说windows 和 linux 数据在内存上的对齐方式不一样
linux按照从高到低顺序在内存中排列
windows是相反的。
呃，但是物理层的东西，在调试器里看不出来啊。
算哒，测不了。

2012-7-2

cxw

*/
/************************************************************************/

#include <iostream>
#include <memory.h>

using namespace std;



int main(void)
{

	long long  i = 0;


	i = 0x00001100;


	int j = 0;

	memcpy_s(&j,sizeof(j),&i,4);


	cout << " i = " <<  i << endl;

	cout << " j = " <<  j << endl;




	return 0;
};