// ******************************************************************
//
// Copyright(c) 2002 - 2010 Progress Software Corporation (PSC).  All
// rights reserved.  Use, reproduction, transfer, publication or 
// disclosure is prohibited except as specifically provided for in 
// your License Agreement with PSC.
//
// ******************************************************************

#include <JTC/JTC.h>

#include <stdlib.h>

#ifdef HAVE_IOSTREAM
#  include <iostream>
#else
#  include <iostream.h>
#endif

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

class BaseClass : public JTCMonitor
{
public:

	virtual
		~BaseClass()
	{
		cout << "BaseClass" << endl;
	}
};

class TestThread : public BaseClass, public JTCThread
{
public:

	TestThread()
	{
	}

	virtual
		~TestThread()
	{
		cout << "TestThread" << endl;
	}

	virtual void
		run()
	{
		cout << "Done." << endl;
	}
};

int
main()
{
	try
	{
		JTCInitialize boot_jtc;

		JTCThreadHandle t = new TestThread();
		t -> start();
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}