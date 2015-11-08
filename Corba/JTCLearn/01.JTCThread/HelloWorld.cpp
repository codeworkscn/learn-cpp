
#include <JTC/JTC.h>
#include <stdlib.h>


#include <iostream>

using namespace std;


// This thread will display HelloWorld when started.
class HelloWorldThread : public JTCThread
{
public:

	virtual void
		run()
	{
		cout << "hello world" << endl;
	}
};

int
main(int argc, char** argv)
{
	try
	{
		//
		// A user of the JTC library must create an instance of this
		// class to initialize the library.
		//
		JTCInitialize boot_jtc(argc, argv);

		//
		// Create an instance of the HelloWorldThread object.
		//
		JTCThreadHandle t = new HelloWorldThread();

		//
		// Start the thread.
		//
		t -> start();
		t -> join ();


	}
	catch(const JTCException& e)
	{
		cerr << "JTCException: " << e.getMessage() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}