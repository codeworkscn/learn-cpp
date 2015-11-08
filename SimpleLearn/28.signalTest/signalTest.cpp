// crt_signal.c
// compile with: /c
// Use signal to attach a signal handler to the abort routine
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <tchar.h>
#include <conio.h>

int exitfunc()
{
	printf("the program terminates normally.\n");
	return 0;
}


void SignalHandler(int signal)
{
	switch(signal)
	{
	case SIGINT   :	
		break;
	case SIGILL   : 
		break;
	case SIGFPE   :
		break;
	case SIGSEGV  : 
		break;
	case SIGTERM  : 
		printf("Software termination signal from kill.\n");
		break;
	case SIGBREAK :
		printf(" Ctrl-Break sequence .\n");
		break;
	case SIGABRT  :
		printf("Application aborting...\n");
		break;
	default:
		break;
	}
}

int main()
{
	signal(SIGABRT, SignalHandler);
	signal(SIGTERM, SignalHandler);

	_onexit( exitfunc );

	int i = 0;

// 	while(1)
// 	{
// 		i ++ ;
// 	}
	_getch();
}
