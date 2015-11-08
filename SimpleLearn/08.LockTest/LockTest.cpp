// msl_lock_lock.cpp
// compile with: /clr
#include <msclr/lock.h>
#include <iostream>

using namespace System;
using namespace System::Threading;
using namespace msclr;

ref class CounterClass {
private:
	int Counter;   

public:
	property int ThreadCount;

	// function called by multiple threads, use lock to keep Counter consistent
	// for each thread
	void UseCounter() {
		try {
			lock l(this); // wait infinitely

			Console::WriteLine("In thread {0}, Counter = {1}", Thread::CurrentThread->ManagedThreadId, 
				Counter);

			for (int i = 0; i < 10; i++) {
				Counter++;
 				Thread::Sleep(10);

				//do not sleep
  			//	int jiajia = 0;
  			//	for (int j = 0 ; j < 1024 ; j ++)
  			//	{s
  			//		for (int j1 = 0 ; j1 < 1024 ; j1 ++)
  			//		{
  			//			for (int j2 = 0 ; j2 < 100 ; j2 ++)
  			//			{
  			//				jiajia ++;
  			//			}
  			//		}
 				//}
			}

			Console::WriteLine("In thread {0}, Counter = {1}", Thread::CurrentThread->ManagedThreadId, 
				Counter);

			Counter = 0;
			// lock is automatically released when it goes out of scope and its destructor is called
		}
		catch (...) {
			Console::WriteLine("Couldn't acquire lock!");
		}

		ThreadCount--;
	}
};

int main() {
	// create a few threads to contend for access to the shared data
	CounterClass^ cc = gcnew CounterClass;
	array<Thread^>^ tarr = gcnew array<Thread^>(5);
	ThreadStart^ startDelegate = gcnew ThreadStart(cc, &CounterClass::UseCounter);
	for (int i = 0; i < tarr->Length; i++) {
		tarr[i] = gcnew Thread(startDelegate);
		cc->ThreadCount++;
		tarr[i]->Start();
	}

	// keep our main thread alive until all worker threads have completed
	lock l(cc, lock_later); // don't lock now, just create the object
	while (true) {
 		if (l.try_acquire(50)) { // try to acquire lock, don't throw an exception if can't
			if (0 == cc->ThreadCount) {
				Console::WriteLine("All threads completed.");
				break; // all threads are gone, exit while
			}
			else {
				Console::WriteLine("{0} threads exist, continue waiting...", cc->ThreadCount);
				l.release(); // some threads exist, let them do their work
			}
		} 
		else
		{
			Console::WriteLine("try_acquire fail,waiting...");
		}
	}
	system("pause");
}