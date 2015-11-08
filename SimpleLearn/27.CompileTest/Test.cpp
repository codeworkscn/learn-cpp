#include <iostream>

#include <string>


using namespace std;

int main (void)
{

	string str;
	str = "test";

	cout << "str = " << str << endl; 

	char chars[64];

	strcpy_s(chars,sizeof(chars),str.c_str());

	cout << "chars = " << chars << endl;


	system("pause");
	return 0;
};