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

class TETSimpleThread : public JTCThread
{
public:

	TETSimpleThread()
		: m_stopped(false)
	{
	}

	void
		stop()
	{
		m_stopped = true;
	}

	virtual void
		run()
	{
		while (!m_stopped)
		{
			JTCThread::sleep(100);
		}
	}

private:

	bool m_stopped;
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<TETSimpleThread>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<TETSimpleThread>)
#  endif
#endif

typedef JTCHandleT<TETSimpleThread> TETSimpleThreadHandle;

class JoinerThread : public JTCThread
{
public:

	virtual void
		run()
	{
		cout << "Before join (should see second pause)" << endl;
		try
		{
			join(1000);
		}
		catch(const JTCInterruptedException&)
		{
			cout << "Interrupted Exception" << endl;
		}
		cout << "After join" << endl;
	}
};

int
main()
{
	try
	{
		JTCInitialize boot_jtc;

		//
		// Create an extraneous thread.  Eventually we'll let this
		// block exit, and ensure that this termination still occurs
		// correctly.  Note that this will cause apparent memory leaks
		// in this test -- this is obviously expected.
		//
		new JTCThread;

		TETSimpleThreadHandle t1 = new TETSimpleThread;
		t1 -> start();

		//
		// Test the timed join.
		//
		cout << "You should see 10 dots, 250 msecs between each: " << flush;
		for (int i = 0; i < 10; ++i)
		{
			cout << "." << flush;
			t1 -> join(250);
		}
		cout << endl;
		t1 -> stop();

		JTCThreadHandle jt = new JoinerThread;
		jt -> start();
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}