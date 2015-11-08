#include<iostream>
#include<string>

//using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::string;


int Test1(void)
{
	string v1,v2;
	cin>>v1>>v2;
	if(v1 >= v2)
		cout<<v1<<endl;
	else
		cout<<v2<<endl;

	string result,str;
	cout<<"please enter strings:"<<endl;
	while(cin>>str)
	{
		result=str+result;
	}
	cout<<endl<<result<<endl;
	return 0;

	return 0;
}
