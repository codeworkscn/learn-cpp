/************************************************************************/
/* 
获取系统ms数，时间字符输出功能
创建时间：2010-12-3 14:19:41
创建人：陈小伟
修改记录：


*/
/************************************************************************/
#ifndef _SGRDC_TIMESTAMP_H_
#define _SGRDC_TIMESTAMP_H_


#include <cstring>
#include <iostream>
#include <string>
#include <sys/timeb.h>

using namespace std;

class TimeStamp
{
public:

	/*获取系统时间构造当前时间*/
	TimeStamp();


	/*输入参数构造时间( 00:00:00 1970/1/1 UTC).*/
	TimeStamp(unsigned int seconds, unsigned int microSeconds = 0);

	/*返回当前秒数*/
	inline int getSeconds() const {
		return _seconds;
	};

	/*返回当前毫秒数*/
	inline int getMilliSeconds() const {
		return _milliSeconds;
	};


	/*返回时间的字符串格式，格式如"Fri Dec 03 14:11:12 2010"
	2010-12-28 9:58:27 格式改为如: "2010-12-28 09:58:27 "
	mode = 1: 精度到秒  (默认)
	mode = 2: 精度到毫秒*/
	string getTimeString(const int mode = 1);

	/*返回时间的字符串格式，格式如: "2010-12-28 09 58 27" 
	因为文件名中不能包含 ":" 符号
	精度到秒*/
	string getTimeStringForFileName();

	/*返回应用程序开始执行的时间*/
	static inline const TimeStamp& getStartTime() {
		return _startStamp;
	};

protected:
	static TimeStamp _startStamp;

	int _seconds;
	int _milliSeconds;
};


#endif