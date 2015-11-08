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

class TrylockThreadFail : public JTCThread
{
public:

    virtual void
    run()
    {
	assert(!m_mut.trylock());
    }

    JTCMutex m_mut;
};

class TrylockThreadSucc : public JTCThread
{
public:

    virtual void
    run()
    {
	assert(m_mut.trylock());
	m_mut.unlock();
    }

    JTCMutex m_mut;
};

class TrylockThreadRecFail : public JTCThread
{
public:

    virtual void
    run()
    {
	assert(!m_mut.trylock());
    }

    JTCRecursiveMutex m_mut;
};

class TrylockThreadRecSucc : public JTCThread
{
public:

    virtual void
    run()
    {
	assert(m_mut.trylock());
	m_mut.unlock();
    }

    JTCRecursiveMutex m_mut;
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<TrylockThreadFail>;
template class JTCHandleT<TrylockThreadSucc>;
template class JTCHandleT<TrylockThreadRecFail>;
template class JTCHandleT<TrylockThreadRecSucc>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<TrylockThreadFail>)
#    pragma define(JTCHandleT<TrylockThreadSucc>)
#    pragma define(JTCHandleT<TrylockThreadRecFail>)
#    pragma define(JTCHandleT<TrylockThreadRecSucc>)
#  endif
#endif

int
main()
{
    try
    {
	JTCInitialize boot_jtc;

	//
	// Under WIN32 mutexes are actually recursive
	//
#if !defined(HAVE_WIN32_THREADS)
	cout << "Testing JTCMutex::lock()..." << flush;
	JTCMutex mut;
	mut.lock();
	assert(!mut.trylock());
	mut.unlock();
	cout << "OK!" << endl;
#endif

	cout << "Testing JTCRecursiveMutex::lock()..." << flush;
	JTCRecursiveMutex rm;
	rm.lock();
	assert(rm.trylock());
	rm.unlock();
	rm.unlock();
	cout << "OK!" << endl;

	cout << "Testing JTCMutex::trylock() fail..." << flush;
	JTCHandleT<TrylockThreadFail> t1 = new TrylockThreadFail();
	t1 -> m_mut.lock();
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
	t1 -> m_mut.unlock();
	cout << "OK!" << endl;

#if (defined(HAVE_WIN32_THREADS) && !(_WIN32_WINNT >= 0x0400))
	cout << "Testing JTCMutex::trylock() always fail ()..." << flush;
	JTCMutex m;
	assert(!m.trylock());
	cout << "OK!" << endl;
#else
	cout << "Testing JTCMutex::trylock() succ..." << flush;
	JTCHandleT<TrylockThreadSucc> t2 = new TrylockThreadSucc();
	t2 -> start();
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
	cout << "OK!" << endl;
#endif

	cout << "Testing JTCRecursiveMutex::trylock() fail..." << flush;
	JTCHandleT<TrylockThreadRecFail> t3 = new TrylockThreadRecFail();
	t3 -> m_mut.lock();
	t3 -> start();
	while (t3 -> isAlive())
	{
	    try
	    {
		t3 -> join();
	    }
	    catch(const JTCInterruptedException&)
	    {
	    }
	}
	t3 -> m_mut.unlock();
	cout << "OK!" << endl;

	cout << "Testing JTCRecursiveMutex::trylock() succ..." << flush;
	JTCHandleT<TrylockThreadRecSucc> t4 = new TrylockThreadRecSucc();
	t4 -> start();
	while (t4 -> isAlive())
	{
	    try
	    {
		t4 -> join();
	    }
	    catch(const JTCInterruptedException&)
	    {
	    }
	}
	cout << "OK!" << endl;
    }
    catch(const JTCException& e)
    {
	cout << "Test failed: " << e.getMessage() << endl;
	return EXIT_FAILURE;
    }
    cout << "Test successful." << endl;
    return EXIT_SUCCESS;
}
