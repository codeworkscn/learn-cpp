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

class Starter
{
public:

	Starter()
		: m_started(false)
	{
	}

	void
		wait_for_start()
	{
		JTCSynchronized sync(m_mon);
		if (!m_started)
		{
			m_mon.wait();
		}
		m_mon.notify();
	}

	void
		start()
	{
		JTCSynchronized sync(m_mon);
		m_started = true;
		m_mon.notify();

		m_mon.wait();
	}

private:

	JTCMonitor m_mon;
	bool m_started;
};

class Stopper
{
public:

	Stopper()
		: m_stopped(false)
	{
	}

	void waitForTerminate()
	{
		JTCSynchronized sync(m_mon);
		if (!m_stopped)
		{
			m_mon.wait();
		}
	}

	void terminate()
	{
		JTCSynchronized sync(m_mon);
		m_stopped = true;
		m_mon.notify();
	}

private:

	JTCMonitor m_mon;
	bool m_stopped;
};

class TestThread : public JTCThread
{
public:

	TestThread(
		Starter& start,
		Stopper& stop
		)
		: m_stop(stop), m_start(start)
	{
	}

	virtual void
		run()
	{
		m_start.wait_for_start();
		m_stop.waitForTerminate();
	}

private:

	Stopper& m_stop;
	Starter& m_start;
};

int
main()
{
	try
	{
		JTCInitialize boot_jtc;
		assert(JTCThread::currentThread() -> isAlive());

		Starter starter;
		Stopper stop;
		JTCThreadHandle tt = new TestThread(starter, stop);;

		assert(!tt -> isAlive());

		tt -> start();

		assert(tt -> isAlive());

		starter.start();

		assert(tt -> isAlive());

		stop.terminate();
		bool complete = false;
		do
		{
			try
			{
				tt -> join();
				complete = true;
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		while (!complete);

		assert(!tt -> isAlive());
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}
	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}