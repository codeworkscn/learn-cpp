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
#include <assert.h>

#ifdef HAVE_IOSTREAM
#  include <iostream>
#else
#  include <iostream.h>
#endif

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

class TestThread : public JTCThread
{
public:

	TestThread()
	{
	}

	virtual void
		run()
	{
	}
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<TestThread>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<TestThread>)
#  endif
#endif

int
main()
{
	try
	{
		JTCInitialize boot_jtc;
		JTCThreadId null_id1;
		JTCThreadId null_id2;

		//
		// Test that null id's are equal.
		//
		assert(JTCThreadId() == JTCThreadId());
		assert(null_id1 == null_id2);
		assert(null_id1 == JTCThreadId());

		//
		// Test assignment, equality.
		//
		JTCThreadId this_thread_id = JTCThread::currentThread() -> getId();
		assert(this_thread_id != JTCThreadId());
		assert(this_thread_id == JTCThread::currentThread() -> getId());

		JTCHandleT<TestThread> tt = new TestThread;
		tt -> start();
#ifndef NDEBUG // Avoid warnings
		JTCThreadId tt_id = tt -> getId();
		assert(tt_id == tt -> getId());
		assert(tt_id != JTCThreadId());
		assert(tt_id != this_thread_id);
#endif
		tt -> join();
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}