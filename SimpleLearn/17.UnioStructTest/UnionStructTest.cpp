#include <iostream>

using namespace std;

struct S1
{
	long aa;
	char bb[32];
	long cc;
};

struct S2
{
	long aa;
	char bb[32];
	long long cc;
};

union SS
{
	S1 s1;
	S2 s2;
};

int main(void)
{
	S1 ss1;
	SS ss;
	char st[32] = "1";
	ss.s2.aa  = 1;
	strcpy(ss.s2.bb , st);
	ss.s2.cc = 1;
		
	ss1 = ss.s1;
	
	cout << ss1.aa << endl << ss1.bb << endl << ss1.cc << endl;

	system("pause");
	return 0;
}