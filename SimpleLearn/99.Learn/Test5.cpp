#include<iostream>
#include<vector>
using namespace std;

int Test5(void)
{
	int v2;
	vector<int> v1;
	cout<<"enter numbers(ctrl+z to end):"<<endl;
	while(cin>>v2)
		v1.push_back(v2);
	if(v1.size()==0)
	{
		cout<<"No elements?"<<endl;
		return -1;
	}
	vector<int>::size_type v3 =  0;
	for(v3;v3!=v1.size()-1;++v3)
	{
		cout<<"the result:"<<v1[v3]+v1[v3+1]<<"\t";
		if(v1[v2+1]%4==0)
			cout<<endl;
	}
	if(v1.size()%2!=0)
	{
		cout<<"the last number is summed"
		<<"its value is"
		<<v1[v1.size()-1]<<endl;
	}
	return 0 ;
}


