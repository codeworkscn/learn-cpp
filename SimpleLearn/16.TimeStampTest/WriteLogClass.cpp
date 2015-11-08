#include "WriteLogClass.h"

CWriteLogClass::CWriteLogClass(void)
{
}

CWriteLogClass::~CWriteLogClass(void)
{
}


void CWriteLogClass::WriteLogToFile(const char* filename,const char* module,const char* info,const int status)
{
	TimeStamp ts;
	string mlog = ts.getTimeString(2).c_str() ;
	mlog += module;
	mlog += ",";
	mlog += info;
	mlog += ",";
	if (!status)
	{
		mlog += "³É¹¦";
	}
	else
	{
		mlog += "Ê§°Ü";
	}
	mlog += "\n";
	cout << mlog << endl;
	FILE * fp = fopen(filename,"a+");
	fwrite(mlog.c_str(),1,mlog.size(),fp);
	fclose(fp);
}