#include "SafeMap.h"
#include <JTC/JTC.h>
#include <string>

#define THREADCOUNT 2

using namespace std;

typedef SafeMap<int,string>				Int2StringMap;

class SafeMapTest:public JTCRunnable
// class SafeMapTest:public JTCThread
{
public:
	SafeMapTest()
	{
		_mMap = new Int2StringMap();
	};

	~SafeMapTest()
	{
		if (_mMap)
		{
			delete _mMap;
		}
	}

private:

	Int2StringMap *_mMap;

public:

	virtual void run()
	{
		bool insertSuccess;
		for (int i = 0; i < 10; i++)
		{
			stringstream  str; ;
			str << "value_" << i << "_thread_"<< JTCThread::currentThread()->getId () ;
			insertSuccess = _mMap->insert(i,str.str ().c_str());

			_mMap->output(i,str.str ().c_str(),insertSuccess);

// 			JTCThread::yield ();

		}

		cout << "--------------------------------" << endl;

		Int2StringMap::Miterator _iter;

		for (int i = 0; i < 10; i++)
		{
			_iter = _mMap->find(i);
			_mMap->output(_iter);
// 			JTCThread::yield ();
		}
		return;
	}
};

void main()
{
	JTCInitialize jtcInitialize;

 	typedef JTCHandleT<SafeMapTest> SafeMapTestHandle;
// 	SafeMapTestHandle sHandle = new SafeMapTest();
// 	sHandle->start();

	JTCRunnableHandle safeMapHandle = new SafeMapTest();			
 	JTCThreadHandle sHandle1 = new JTCThread(safeMapHandle);
 	JTCThreadHandle sHandle2 = new JTCThread(safeMapHandle);
  	sHandle1->start();
 	sHandle2->start();

//  sHandle1->join ();
// 	sHandle2->join ();

	return;
}

