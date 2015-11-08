#include "MemoryTest.h"

extern void StackHeapTest (void);


int MallocTest(void)
{

	char* getchar;
	long long memorycount = 0;
	long count =0;

	while (1)
	{
		try
		{
			getchar = MallocReturn();
			memorycount += 1024;
			count ++;
			if (!(count%1024))
			{
				cout << "MallocReturn Success! The Memory Getted IS " << memorycount << endl;
			}
		}
		catch (...)
		{
			cout << "MallocReturn Failure! The Memory Getted IS " << memorycount << endl;
			break;
		}
	}

	return 0;
}

char * MallocReturn(void)
{
	char *mchar;
	mchar = (char*)malloc(1024);

/*	char mchar[1024];*/

	return mchar;
}


int main(void)
{

	char aa [1024 * 1024];

	//strcpy_s (aa,sizeof(aa),"lj;lagsjd;lfjal;sdkjf;l");
	aa[1024 +1 ] = 2;

	//Stack Heap Test.
	StackHeapTest();


	return 0;
};