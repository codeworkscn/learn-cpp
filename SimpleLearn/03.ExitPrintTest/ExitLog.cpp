#include "ExitLog.h"

ExitLog::ExitLog(void)
{
}

ExitLog::~ExitLog(void)
{
	FILE * fp = fopen("cxw.txt","w+");
	fwrite("ExitLog",1,8,fp);
	fclose(fp);
}
