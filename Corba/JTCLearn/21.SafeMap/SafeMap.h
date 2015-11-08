#pragma once

//#include <JTC/Monitor.h>
#include <JTC/Mutex.h>
#include <map>

using namespace std;

template <typename T,typename K>
class SafeMap:public map<T,K>
{
public:
	typedef map<T,K>::iterator	Miterator;
	typedef pair<T,K>			Mpair;

private:
	JTCMutex _mutex;


public:


public:
	SafeMap()
	{

	};

	~SafeMap()
	{
		clear();
	};

	//return true if success
	bool insert (T t,K k)
	{
		pair<Miterator,bool> _pRe;
		_mutex.lock();
		_pRe = map<T,K>::insert(Mpair(t,k));
		//if failed, means has been exist,then replace value
		if (! _pRe.second)
		{
			_pRe.first->second = k;
		}
		_mutex.unlock ();
// 		return _pRe.second;
		return true;
	};

	Miterator find(T t)
	{	
		Miterator iter;
		_mutex.lock();
		iter = map<T,K>::find(t);
		_mutex.unlock ();
		return iter;
	};

	virtual void erase (T t)
	{
		_mutex.lock();
		map<T,K>::erase (t);
		_mutex.unlock ();
	};

	virtual void clear(void)
	{
		_mutex.lock();
		map<T,K>::clear();
		_mutex.unlock ();
	};


	//output for test.
	virtual void output(Miterator _iter)
	{
		_mutex.lock();
		if (map<T,K>::end() != _iter)
		{
			cout << "thread:" << JTCThread::currentThread ()->getId () 
				<<  " key = " << _iter->first << " value = " << _iter->second << endl;
		}
		//find failed
		else
		{
			cout << "thread:" << JTCThread::currentThread ()->getId () 
				<< " key = " << _iter->first << " value : " << " FIND FAIL" << endl;
		}
		_mutex.unlock ();
	};

	//output for test.
	virtual void output(T t,K k,bool success)
	{
		_mutex.lock();
		if (success)
		{
			cout << "thread:" << JTCThread::currentThread ()->getId () 
				<<  " key = " << t << " value = " << k <<  " insert success. "<< endl;
		}
		else
		{
			cout << "thread:" << JTCThread::currentThread ()->getId () 
				<<  " key = " << t << " value = " << k <<  " insert fail. "<< endl;
		}
		_mutex.unlock ();
	};
};