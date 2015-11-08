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

class Global : public JTCMonitor
{
public:

    static void
    increment()
    {
	JTCSynchronized sync(m_mon);
	++m_counter;
    }

    static void
    decrement()
    {
	JTCSynchronized sync(m_mon);
	--m_counter;
    }

    static int
    value()
    {
	JTCSynchronized sync(m_mon);
	return m_counter;
    }

private:

    static int m_counter;
    static JTCMonitor m_mon;
};

int Global::m_counter = 0;
JTCMonitor Global::m_mon;

class CountThread : public JTCThread
{
public:
    CountThread(
	bool countUp
    )
        : m_count_up(countUp)
    {
    }

    virtual void
    run()
    {
        int times = 100;
        while (--times > 0)
        {
            if (m_count_up)
                Global::increment();
            else
                Global::decrement();
            yield();
        }
    }

private:

    bool m_count_up;
};

int
main()
{
    try
    {
	JTCInitialize boot_jtc;
        JTCThreadHandle t[4];
        
        t[0] = new CountThread(true);
        t[1] = new CountThread(true);
        t[2] = new CountThread(false);
        t[3] = new CountThread(false);

        unsigned int i;
        for (i = 0; i < sizeof(t)/sizeof(t[0]); ++i)
        {
            t[i] -> start();
        }

        for (i = 0; i < sizeof(t)/sizeof(t[0]); ++i)
        {
            do
            {
                try
                {
                    t[i] -> join();
                }
                catch(const JTCInterruptedException&)
                {
                }
            }
            while (t[i] -> isAlive());
        }

        if (Global::value() != 0)
        {
            cout << "Test failed." << endl;
            return EXIT_FAILURE;
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
