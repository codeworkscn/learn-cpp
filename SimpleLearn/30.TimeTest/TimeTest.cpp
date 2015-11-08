/************************************************************************/
/* 
2012-12-11 10:38:52，验证GetSystemTimeAsFileTime时间获取精度
验证结论：能够达到 毫秒 的精度。
由此，ACE的时间获取精度，也只能达到 毫秒 的精度。
*/
/************************************************************************/

#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

const DWORDLONG FILETIME_to_timval_skew=116444736000000000;

//return 100ns unit
ULONGLONG get_clock_time_now(void)
{
	FILETIME   tfile;
	::GetSystemTimeAsFileTime (&tfile);

	ULARGE_INTEGER _100ns;
	_100ns.LowPart = tfile.dwLowDateTime;
	_100ns.HighPart = tfile.dwHighDateTime;
	_100ns.QuadPart -= FILETIME_to_timval_skew;

	return _100ns.QuadPart;
};

int main(void)
{
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;
	cout << "nowtime = " << get_clock_time_now () << endl;

	ULONGLONG * nowtime = new ULONGLONG[1000000];

	for (unsigned int i = 0 ; i < 1000000 ; i ++)
	{
		nowtime[i] = get_clock_time_now ();
	}
	for (unsigned int i = 1 ; i < 1000000 ; i ++)
	{
		if (nowtime[i] != nowtime[i-1])
		{
			cout << "nowtime = " << nowtime[i] << "  [" << i << "] ." << endl;
		}
	}

	_getch();
};