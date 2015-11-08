#include<iostream>
#include<string>

using namespace std;

int Test2(void)
{
	const int n = 9 ;

	for(int i=1 ; i!= n+1 ; ++i)
	{
		for(int j=1 ; j!= i+1 ; ++j)
		{
			cout << i << "*" << j << "=" << i*j << "\t";
			if(! (j%10) && j)
			{	
				cout << endl ;
			}
		}
		cout << endl ;
	}
	return 0 ;
}
