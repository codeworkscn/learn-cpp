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

static int lsd_nobjs = 0;
static JTCMutex lsd_mutex;

class Test
{
public:

    Test()
    {
        JTCSynchronized sync(lsd_mutex);
        ++lsd_nobjs;
    }

    ~Test()
    {
        JTCSynchronized sync(lsd_mutex);
        --lsd_nobjs;
    }
};

static void
cleanup(
    void *data
)
{
    delete (Test*)data;
}

static JTCThreadKey key;

class TSSSimpleThread : public JTCThread
{
public:

    TSSSimpleThread(
	const char* name = 0
    )
        : JTCThread(name)
    {
    }
    
    virtual void
    run()
    {
        Test* t = new Test;
        JTCTSS::set(key, t);
    }
};

int
main()
{
    try
    {
	JTCInitialize boot_jtc;

        key = JTCTSS::allocate(cleanup);

	JTCThreadHandle t1 = new TSSSimpleThread("Jamaica");
	cout << "t1: " << t1 -> getName() << endl;

	JTCThreadHandle t2 = new TSSSimpleThread("Fiji");
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

	//
	// Due to a bug with glibc 2.1.3-15 (and perhaps other
	// versions) pthread_key_delete can cause memory corruptions
	// when called when threads are still active.
	//
#if !defined(__linux__)
	JTCTSS::release(key);
#endif
        assert(lsd_nobjs == 0);
    }
    catch(const JTCException& e)
    {
	cout << "Test failed: " << e.getMessage() << endl;
	return EXIT_FAILURE;
    }

    cout << "Test successful." << endl;
    return EXIT_SUCCESS;
}
