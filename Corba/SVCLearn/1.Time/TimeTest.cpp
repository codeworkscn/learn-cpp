#include <iostream>
#include <time.h>
#include <OB/CORBA.h>
#include <OB/TimeHelper.h>
#include <OB/CosTime.h>

#include "TimeTest.h"

using namespace std;

int main(void)
{
	TimeBase::UtcT utc;

	utc = OB::TimeHelper::utcMin ();
	cout << "utcMin  " << utc.time << endl;

	utc = OB::TimeHelper::utcMax ();
	cout << "utcMax  " << utc.time << endl;

	utc = OB::TimeHelper::utcNow ();
	cout << "utcNow  " << utc.time << endl;

	timeval tt;

	tt = OB::TimeHelper::toTimeval (utc.time);


	cout << "time_t:    " << time(NULL) << endl;
	cout << "tt tv_sec  " << tt.tv_sec << endl;
	cout << "tt tv_usec	" << tt.tv_usec << endl;

	time_t seconds = tt.tv_sec;

	struct tm* tmnow = localtime (&seconds);
	printf("localtime: %04d-%02d-%02d %02d:%02d:%02d\n",
		tmnow->tm_year + 1900,tmnow->tm_mon + 1,tmnow->tm_mday,
		tmnow->tm_hour,tmnow->tm_min,tmnow->tm_sec);

	char *timestr = new char[128];
	timestr =  OB::TimeHelper::toString (utc);
	cout << "toString      " << timestr << endl;

	timestr =  OB::TimeHelper::toTimeString (utc);
	cout << "toTimeString  " << timestr << endl;



	//1970.01.01 00:00:00µÄutcTÊ±¼ä£º



	system ("pause");
	return 0;
}


