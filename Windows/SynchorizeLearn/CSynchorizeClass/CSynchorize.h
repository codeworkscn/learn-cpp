#pragma once

#include <afxmt.h>


class CSynchorize
{
	CCriticalSection mlock;

	int mValue;


	CSynchorize()
	{
		mValue = 0;
	};


	~CSynchorize()
	{

	};

	
	bool setValue(int _value)
	{
		if (mlock.Lock(100)) // Wait 100 ms...
		{


		}
	}
};

 