#include "Operator.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std ;

extern int Test1(void);
extern int Test2(void);
extern int Test3(void);

extern int Test5(void);
extern int Test6(void);
extern void GetLowTest(void);
extern void EnumTest(void);
extern void VectorTest(void);
extern void GetGlobalIDTest();
extern void cintest(void);

class A
{
	void fun0(void)
	{
		;
	};

// 	virtual void fun1(void)
// 	{
// 		;
// 	};

	void fun1(void)
	{
		;
	};

};

int main(int argc, char* argv[])
{

	DAIS::Bijiao b1,b2;

	map<DAIS::Bijiao,long> mp;
	vector<DAIS::Bijiao> vp;
	b1.a =1;
	b1.b =1;

	b2.a =1;
	b2.b =2;

	vp.push_back (b1);


	//insert语句无法编译通过
	mp.insert(pair<DAIS::Bijiao,long>(b1,100));

	bool c = true;
 	c = b1 < b2;

	cout << "bijiaojieguo: " << c << endl;
	//long long a[10];
	//Test1();
	//Test2();
	//strcat();
	//Test5();
	//GetLowTest();
	//Test6();
	//string a = "%";
	//cout << "a: " << a << endl;
	//char b[16] = "";

	////sprintf_s(b,16,"\%",16);
	//strncpy(b,"\%",16);
	//
	//cout << "b: " << b << endl;
	//EnumTest();
	//VectorTest();
	//GetGlobalIDTest();
// 	cintest();

/************************************************************************/
// 	A a;
// 
// 	cout << "Size of long = " << sizeof(long) << endl;
// 	cout << "Size of A = " << sizeof(A) << endl; 


/************************************************************************/



	system("pause");
}