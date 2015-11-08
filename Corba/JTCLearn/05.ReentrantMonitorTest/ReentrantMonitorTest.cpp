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

// JTCMonitor use JTCRecursiveMutex inner to lock
//
// Unlike the JTCMutex class this mutex can be locked recursively.
// That is it can be locked by a thread that already has the mutex
// locked.
//


class Reentrant : public JTCMonitor
{
public:

	void
		a()
	{
		JTCSynchronized sync(*this);
		b();
		cout << "here I am, in a()" << endl;
	}

	void
		b()
	{
		JTCSynchronized sync(*this);
		cout << "here I am, in b()" << endl;
	}
};

int
main()
{
	try
	{
		JTCInitialize boot_jtc;

		Reentrant r;
		r.a();
	}
	catch(const JTCException& e)
	{
		cout << "Test failed: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	cout << "Test successful." << endl;
	return EXIT_SUCCESS;
}