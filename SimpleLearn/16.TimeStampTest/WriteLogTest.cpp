#include <Windows.h>
#include <fstream>
#include "WriteLogClass.h"


int main(void)
{

	CWriteLogClass wrg; 
	string filename = "Server";
	filename += wrg.getTimeStringForFileName();
	filename += ".log";

	cout << filename << endl;

	//wrg.WriteLogToFile("SGRDC_Server.log","�û���֤","admin",2);
 	int mcount = 100;
 	while(mcount--)
 	{
 		wrg.WriteLogToFile(filename.c_str(),"�û���֤","admin",0);
		_sleep(10);
 	}
	return 0;
}