#include "TimeStamp.h"
#include <time.h>

TimeStamp::TimeStamp(void)
{
	struct timeb tb;
	::ftime(&tb);
	_seconds = (int)tb.time;
	_milliSeconds = tb.millitm;
}



TimeStamp::TimeStamp(unsigned int seconds, unsigned int milliSeconds) :
_seconds(seconds),
_milliSeconds(milliSeconds) 
{

}


string TimeStamp::getTimeString(const int mode)
{
	time_t second_t = _seconds;
	struct tm* ldctm = localtime(&second_t);
	char timebuf[32] = "";
	//asctime_s( timebuf, sizeof(timebuf), ldctm);
	//
	//timebuf[3]=',';
	//timebuf[10]=',';
	//timebuf[19]=',';
	//timebuf[24] =',';//去除换行，改为空格
	sprintf_s(timebuf,32,"%4d-%02d-%02d %02d:%02d:%02d ",
				ldctm->tm_year + 1900,
				ldctm->tm_mon + 1,
				ldctm->tm_mday,
				ldctm->tm_hour,
				ldctm->tm_min,
				ldctm->tm_sec);

	ldctm = NULL;
	string timestring = timebuf;
	char msbuffer[10] = "";
	memset(msbuffer,0,10);
	switch (mode)
	{
	case 2://精度到ms
		{
			sprintf_s(msbuffer,"%03d",_milliSeconds);
			timestring += msbuffer;
			timestring += "ms ";
		}break;	
	default:break;
	}
	return timestring;
}

string TimeStamp::getTimeStringForFileName()
{
	time_t second_t = _seconds;
	struct tm* ldctm = localtime(&second_t);
	char timebuf[32] = "";
	sprintf_s(timebuf,32,"%4d-%02d-%02d %02d %02d %02d",
		ldctm->tm_year + 1900,
		ldctm->tm_mon + 1,
		ldctm->tm_mday,
		ldctm->tm_hour,
		ldctm->tm_min,
		ldctm->tm_sec);
	ldctm = NULL;
	string timestring(timebuf);
	return timestring;
}