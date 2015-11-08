#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class A
{

	A operator ()(A& i)
	{
		return i;
	}
public:
	int data;
};





int main(void)
{
// 
// 	int i = 0;
// 	int j(i);
// 
// 
// 	A a;
// 
// 	A b(a);
// 
// 	b.data = 0;



	int cpui = 0;
	int cpuj = 0;

	while (1)
	{
		cpuj = cpui + 1;
		cpui = cpuj +1 ;
	}

// 	long mina = 0xffffffff;
// 	long maxb = 0x7fffffff;
// 
// 	string maxo = (maxb > mina)? "maxb":"mina";
// 
// 	cout << "max is : " << maxo << endl;
 
// 	long xixi =	1;
// 	string aa("NULL");
// 	aa = xixi;
// 
// 	cout << aa << endl;

	//double a = 1;
	//double b = 3;

	//double c = 0;

	//c = a / b;

	//cout << "c = " << c << endl;


	//c = c * b;

	//cout << "c = " << c << endl;

	//c = 0.3333333 * b;

	//cout << "c = " << c << endl;

	//c = (a / b) * b;

	//cout << "c = " << c << endl;

	//c = 0.3333333;

	//c *= 3;

	//cout << "c = " << c << endl;

	system("pause");
	return 0;
}