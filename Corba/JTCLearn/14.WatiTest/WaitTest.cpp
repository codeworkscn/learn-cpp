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

class Thread1 : public JTCThread, public JTCMonitor
{
public:

	Thread1()
		: m_done(0) { }

	virtual void
		run()
	{
		JTCSynchronized sync(*this);
		cout << "waiting" << endl;
		while (!m_done)
		{
			try
			{
				wait();
			}
			catch(JTCInterruptedException&)
			{
				continue;
			}
			m_done = 1;
		}
		cout << "run complete" << endl;
	}

private:

	int m_done;
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<Thread1>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<Thread1>)
#  endif
#endif

int
main()
{
	try
	{
		JTCInitialize boot_jtc;

		JTCHandleT<Thread1> t = new Thread1;
		t -> start();
		JTCThread::sleep(500);
		cout << "notify." << endl;
		{
			JTCSynchronized guard(*t);
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

		t = new Thread1;
		t -> start();
		JTCThread::sleep(500);
		cout << "notifyAll." << endl;
		{
			JTCSynchronized guard(*t);
			t -> notifyAll();
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
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}