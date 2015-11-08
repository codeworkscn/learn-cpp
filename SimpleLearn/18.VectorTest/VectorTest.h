#include <iostream>
#include <vector>

using namespace std;

//结构体定义
struct TestStruct
{
	long longdata[16];
	double doubledata;
	char chardata[128];
	union
	{
		long lval;
		double dval;
		char sval[64];
	};
};


//函数声明
extern int VecterAsArrayTest(void);
extern int VectorMemoryTest(void);
extern int VectorReserveTest(void);