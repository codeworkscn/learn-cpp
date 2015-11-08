#include <iostream>
#include <map>
#include <string>

using namespace std;

struct PIconnects
{
	long port;
};

typedef map<long,PIconnects> HandleMap; 
typedef pair<long,PIconnects> HandlePair;
typedef map<long,PIconnects>::iterator HandleMapIterator;
typedef pair<HandleMapIterator,bool> HandleMapInsertReturn;

HandleMap mhandleMap;


long SGRDC_Connect(long port)
{
	HandleMap::iterator miter;

	for(miter=mhandleMap.begin();miter!=mhandleMap.end();miter++)
	{
		if(port == miter->second.port)
		{
			return miter->first;
		}
	}
	/************************************************************************/

	//调用PI的连接函数

	/************************************************************************/

	//如果连接成功
	return 0;//暂时为0.
}

int main()
{

	//test map

	const int count = 5;
	PIconnects piconn[count];

	for (int i = 0;i < count ;i++)
	{
		piconn[i].port = i;
	}

	cout << "insert " << piconn[1].port <<  " ,success = "  
		<< mhandleMap.insert (HandlePair(1,piconn[1])).second << endl;

	cout << "insert " << piconn[1].port <<  " ,success = "  
		<< mhandleMap.insert (HandlePair(1,piconn[1])).second << endl;

	cout << "insert " << piconn[2].port <<  " ,success = "  
		<< mhandleMap.insert (HandlePair(2,piconn[2])).second << endl;

	cout << "insert " << piconn[2].port <<  " ,success = "  
		<< mhandleMap.insert (HandlePair(2,piconn[2])).second << endl;

	cout << "insert " << piconn[3].port <<  " ,success = "  
		<< mhandleMap.insert (HandlePair(3,piconn[3])).second << endl;

	return 0;
}