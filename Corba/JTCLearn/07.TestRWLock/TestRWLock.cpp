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

class TestObject : public JTCRWMutex
{
public:

};

class ReaderThread : public JTCThread, public JTCMonitor
{
public:

	ReaderThread(
		TestObject& o
		)
		: m_o(o),
		m_in_read(false)
	{
	}

	virtual void
		run()
	{
		m_o.read_lock();
		set_in_read(true);
		JTCThread::sleep(1000);

		//
		// This must be set before the mutex is released.
		//
		set_in_read(false);
		m_o.unlock();
	}

	bool
		wait_in_read()
	{
		JTCSynchronized sync(*this);
		while (!m_in_read)
		{
			try
			{
				wait();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		return m_in_read;
	}

	bool
		in_read()
	{
		JTCSynchronized sync(*this);
		return m_in_read;
	}

private:

	void
		set_in_read(
		bool v
		)
	{
		JTCSynchronized sync(*this);
		m_in_read = v;
		notifyAll();
	}


	TestObject& m_o;

	bool m_in_read;
};

class WriterThread : public JTCThread, public JTCMonitor
{
public:

	WriterThread(
		TestObject& o
		)
		: m_o(o),
		m_in_write(false),
		m_running(false),
		m_has_written(false)
	{
	}

	virtual void
		run()
	{
		set_running(true);
		m_o.write_lock();
		set_in_write(true);
		JTCThread::sleep(1000);
		set_in_write(false);
		m_o.unlock();

		set_running(false);
	}

	bool
		wait_in_write()
	{
		JTCSynchronized sync(*this);
		while (!m_in_write)
		{
			try
			{
				wait();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		return m_in_write;
	}

	bool
		wait_running()
	{
		JTCSynchronized sync(*this);
		while (!m_running)
		{
			try
			{
				wait();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		return m_running;
	}

	bool
		in_write()
	{
		JTCSynchronized sync(*this);
		return m_in_write;
	}

	bool
		has_written()
	{
		JTCSynchronized sync(*this);
		return m_has_written;
	}

private:

	void
		set_in_write(
		bool v
		)
	{
		JTCSynchronized sync(*this);
		m_in_write = v;
		if (m_in_write)
			m_has_written = true;
		notifyAll();
	}

	void
		set_running(
		bool v
		)
	{
		JTCSynchronized sync(*this);
		m_running = v;
		notifyAll();
	}


	TestObject& m_o;

	bool m_in_write;
	bool m_running;
	bool m_has_written;
};

#ifndef HAVE_NO_EXPLICIT_TEMPLATES
template class JTCHandleT<WriterThread>;
template class JTCHandleT<ReaderThread>;
#else
#  ifdef HAVE_PRAGMA_DEFINE
#    pragma define(JTCHandleT<WriterThread>)
#    pragma define(JTCHandleT<ReaderThread>)
#  endif
#endif

int
main()
{
	try
	{
		JTCInitialize bootJTC;

		TestObject o;

		JTCHandleT<WriterThread> writer;
		JTCHandleT<ReaderThread> reader;

		//
		// Verify that it's possible to have more than one reader at a
		// time.
		//
		cout << "Testing concurrent reads..." << flush;
		reader = new ReaderThread(o);
		reader -> start();
		assert(reader -> wait_in_read());
		o.read_lock();
		assert(reader -> in_read());
		o.unlock();
		while (reader -> isAlive())
		{
			try
			{
				reader -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		cout << "OK!" << endl;

		//
		// Verify that it's not possible to have a reader and a writer
		// at a time (reader first, writer second)
		//
		cout << "Testing readers blocking writers..." << flush;
		reader = new ReaderThread(o);
		reader -> start();
		assert(reader -> wait_in_read());
		o.write_lock();
		assert(!reader -> in_read());
		o.unlock();
		while (reader -> isAlive())
		{
			try
			{
				reader -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		cout << "OK!" << endl;

		//
		// Verify that it's not possible to have a reader and a writer
		// at a time (writer first, reader second)
		//
		cout << "Testing writers blocking readers..." << flush;

		writer = new WriterThread(o);
		reader = new ReaderThread(o);

		writer -> start();
		assert(writer -> wait_in_write());

		reader -> start();

		//
		// Wait for the reader to acquire the read lock. At this point
		// the writer should have released the write lock. Since the
		// timeout is 1000 msec it shouldn't be possible for this to
		// be caused by the thread startup times.
		//
		assert(reader -> wait_in_read());
		assert(!writer -> in_write());

		while (writer -> isAlive())
		{
			try
			{
				reader -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}

		while (reader -> isAlive())
		{
			try
			{
				reader -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		cout << "OK!" << endl;

		//
		// Verify that two writers are not permitted to write
		// concurrently.
		//
		cout << "Testing concurrent writers not permitted...";
		writer = new WriterThread(o);
		writer -> start();
		assert(writer -> wait_in_write());
		o.write_lock();
		assert(!writer -> in_write());
		o.unlock();

		while (writer -> isAlive())
		{
			try
			{
				writer -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		cout << "OK!" << endl;

		//
		// Verify that a writer blocks a new reader from acquiring the
		// lock.
		//
		cout << "Testing queuing semantics..." << flush;
		reader = new ReaderThread(o);
		reader -> start();
		assert(reader -> wait_in_read());

		writer = new WriterThread(o);
		writer -> start();
		assert(writer -> wait_running());

		//
		// Just because the writer thread is running it doesn't mean
		// that it's trying to acquire the write lock yet. Wait for a
		// little while.
		//
		JTCThread::sleep(100);

		//
		// Acquire the read lock. At this point the writer should have
		// completed writing.
		//
		o.read_lock();
		assert(writer -> has_written() && !writer -> in_write());

		while (reader -> isAlive())
		{
			try
			{
				reader -> join();
			}
			catch(const JTCInterruptedException&)
			{
			}
		}
		while (writer -> isAlive())
		{
			try
			{
				writer -> join();
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