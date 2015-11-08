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

#if defined(HAVE_POSIX_THREADS)
static int lsd_called = 0;

static void
lsf_attr_hook(pthread_attr_t*)
{
    ++lsd_called;
}
#endif

class TCTSimpleThread : public JTCThread
{
public:

    TCTSimpleThread(
	const char* name = 0
    )
	: JTCThread(name)
    {
    }

    virtual void
    run()
    {
	for (int i = 0; i < 10; ++i)
	{
	    cout << i << " " << getName() << endl;
	    JTCThread::sleep(50);
	}
	cout << "DONE! "  << getName() << endl;
    }
};

class EmptyThread : public JTCThread
{
public:

    virtual void
    run()
    {
    }
};

int
main()
{
    try
    {
	JTCInitialize boot_jtc;

#if defined(HAVE_POSIX_THREADS)
	JTCThread::setAttrHook(lsf_attr_hook);
#endif
	cout << "getName(): " << JTCThread::currentThread() -> getName()
	     << endl;
	JTCThreadHandle t1 = new TCTSimpleThread("Jamaica");
	cout << "t1: " << t1 -> getName() << endl;
	JTCThreadHandle t2 = new TCTSimpleThread("Fiji");
	cout << "t2: " << t2 -> getName() << endl;

	t1 -> start();
	t2 -> start();

	while (t1 -> isAlive())
	{
	    try
	    {
		t1 -> join();
	    }
	    catch(const JTCInterruptedException&)
	    {
	    }
	}

	while (t2 -> isAlive())
	{
	    try
	    {
		t2 -> join();
	    }
	    catch(const JTCInterruptedException&)
	    {
	    }
	}

	int max = 1024*5;
	for (int i = 0; i < max; ++i)
	{
	    t1 = new EmptyThread;
	    t1 -> start();
	    while (t1 -> isAlive())
	    {
		try
		{
		    t1 -> join();
		}
		catch(const JTCInterruptedException&)
		{
		}
	    }
	}
	cout << "Spawned " << max << " threads." << endl;

#if defined(HAVE_POSIX_THREADS)
	assert(lsd_called = max + 2);
#endif
    }
    catch(const JTCException& e)
    {
	cout << "Test failed: " << e.getMessage() << endl;
	return EXIT_FAILURE;
    }

    cout << "Test successful." << endl;
    return EXIT_SUCCESS;
}
