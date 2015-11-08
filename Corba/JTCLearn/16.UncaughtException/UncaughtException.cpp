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

class UESimpleThread : public JTCThread
{
public:

	UESimpleThread(
		const char* name = 0
		)
		: JTCThread(name)
	{
	}

	UESimpleThread(
		JTCThreadGroupHandle& handle
		)
		: JTCThread(handle)
	{
	}

	virtual void
		run()
	{
		throw JTCException("To test");
	}
};

class MyThreadGroup : public JTCThreadGroup
{
public:

	MyThreadGroup(
		const char* name
		)
		: JTCThreadGroup(name)
	{
	}

	virtual void
		uncaughtException(
		JTCThreadHandle,
		const JTCException& e)
	{
		cerr << "Caught exception: " << e.getType()
			<< ": " << e.getMessage() << endl;
	}

	virtual void
		uncaughtException(
		JTCThreadHandle
		)
	{
		cerr << "Caught unknown exception" << endl;
	}
};

int
main()
{
	try
	{
		JTCInitialize boot_jtc;
		JTCThreadHandle t = new UESimpleThread;
		t -> start();

		while (t -> isAlive())
		{
			try
			{
				t -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}

		JTCThreadGroupHandle my_group = new MyThreadGroup("test");
		t = new UESimpleThread(my_group);
		t -> start();
		while (t -> isAlive())
		{
			try
			{
				t -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}