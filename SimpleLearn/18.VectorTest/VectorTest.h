#include <iostream>
#include <vector>

using namespace std;

//�ṹ�嶨��
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


//��������
extern int VecterAsArrayTest(void);
extern int VectorMemoryTest(void);
extern int VectorReserveTest(void);