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

class TestThread : public JTCThread, public JTCMonitor
{
public:

	TestThread()
		: m_started(false)
	{
	}

	virtual void
		run()
	{
		//
		// Sleep before acquiring the mutex to allow the main thread
		// to enter the wait_start method.
		//
		JTCThread::sleep(1000);

		JTCSynchronized sync(*this);
		m_started = true;
		notify();
		wait();
	}

	void
		wait_start()
	{
		JTCSynchronized sync(*this);
		while (!m_started)
		{
			wait();
		}
	}

private:

	bool m_started;
};

class WaitThread : public JTCThread
{
public:

	WaitThread(JTCMonitor& mon)
		: m_mon(mon)
	{
	}

	virtual void
		run()
	{
		JTCSynchronized sync(m_mon);
		m_mon.wait();
	}

private:

	JTCMonitor& m_mon;
};

class WaitThread2 : public JTCThread
{
public:

	WaitThread2(JTCMonitor& m, int count)
		: m_mon(m), m_count(count)
	{
	}

	virtual void
		run()
	{
		JTCSynchronized sync(m_mon);
		while (m_count > 0)
		{
			m_mon.wait();
		}
	}

	//
	// Call with monitor locked
	//
	void
		consume()
	{
		--m_count;
	}

private:

	JTCMonitor& m_mon;
	int m_count;
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<TestThread>;
template class JTCHandleT<WaitThread>;
template class JTCHandleT<WaitThread2>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<TestThread>)
#    pragma define(JTCHandleT<WaitThread>)
#    pragma define(JTCHandleT<WaitThread2>)
#  endif
#endif

int
main()
{
	JTCInitialize boot_jtc;

	try
	{
		//
		// TEST: Verify notify() or notifyAll() occur when wait() is
		// called.
		//
		JTCHandleT<TestThread> t = new TestThread;
		t -> start();

		//
		// Wait for the thread to start
		//
		t -> wait_start();

		//
		// Notify the thread. Note that the monitor cannot be notified
		// until the lock is obtained which should mean that the
		// monitor is already waiting.
		//
		{
			JTCSynchronized sync(*t);
			t -> notify();
		}

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

		//
		// TEST: Verify that one call to notify() will take one
		// thread (not two!)
		//
		JTCMonitor mon;
		JTCHandleT<WaitThread> t1 = new WaitThread(mon);
		JTCHandleT<WaitThread> t2 = new WaitThread(mon);
		t1 -> start();
		t2 -> start();

		//
		// Wait until the threads enter wait().
		//
		JTCThread::sleep(1000);

		{
			JTCSynchronized sync(mon);
			mon.notify();
		}

		//
		// Sleep a second.  Either t1 or t2 might can stop -- but not
		// both.
		//
		JTCThread::sleep(1000);
		assert((t1 -> isAlive() && !t2 -> isAlive()) ||
			(t2 -> isAlive() && !t1 -> isAlive()));

		{
			JTCSynchronized sync(mon);
			mon.notify();
		}

		while (t1 -> isAlive() || t2 -> isAlive())
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
		// TEST: Verify that two calls to notify() will take two
		// threads.
		//
		t1 = new WaitThread(mon);
		t2 = new WaitThread(mon);
		t1 -> start();
		t2 -> start();

		//
		// Wait until the threads enter wait().
		//
		JTCThread::sleep(1000);

		{
			JTCSynchronized sync(mon);
			mon.notify();
			mon.notify();
		}

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
		// TEST: Verify that a call to notifyAll() will take two
		// threads.
		//
		t1 = new WaitThread(mon);
		t2 = new WaitThread(mon);
		t1 -> start();
		t2 -> start();

		//
		// Wait until the threads enter wait().
		//
		JTCThread::sleep(1000);

		{
			JTCSynchronized sync(mon);
			mon.notifyAll();
		}

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
		// TEST: Verify that a call to notifyAll() actually wakes both
		// threads.
		//
		int count = 1000;
		JTCHandleT<WaitThread2> wt1 = new WaitThread2(mon, count);
		JTCHandleT<WaitThread2> wt2 = new WaitThread2(mon, count);
		wt1 -> start();
		wt2 -> start();

		//
		// Wait until the threads enter wait().
		//
		JTCThread::sleep(1000);

		while (count > 0)
		{
			JTCSynchronized sync(mon);
			wt1 -> consume();
			wt2 -> consume();
			mon.notifyAll();
			--count;
		}
		while (wt1 -> isAlive())
		{
			try
			{
				wt1 -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		while (wt2 -> isAlive())
		{
			try
			{
				wt2 -> join();
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