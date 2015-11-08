/************************************************************************/
/* 
��ȡϵͳms����ʱ���ַ��������
����ʱ�䣺2010-12-3 14:19:41
�����ˣ���Сΰ
�޸ļ�¼��


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

	/*��ȡϵͳʱ�乹�쵱ǰʱ��*/
	TimeStamp();


	/*�����������ʱ��( 00:00:00 1970/1/1 UTC).*/
	TimeStamp(unsigned int seconds, unsigned int microSeconds = 0);

	/*���ص�ǰ����*/
	inline int getSeconds() const {
		return _seconds;
	};

	/*���ص�ǰ������*/
	inline int getMilliSeconds() const {
		return _milliSeconds;
	};


	/*����ʱ����ַ�����ʽ����ʽ��"Fri Dec 03 14:11:12 2010"
	2010-12-28 9:58:27 ��ʽ��Ϊ��: "2010-12-28 09:58:27 "
	mode = 1: ���ȵ���  (Ĭ��)
	mode = 2: ���ȵ�����*/
	string getTimeString(const int mode = 1);

	/*����ʱ����ַ�����ʽ����ʽ��: "2010-12-28 09 58 27" 
	��Ϊ�ļ����в��ܰ��� ":" ����
	���ȵ���*/
	string getTimeStringForFileName();

	/*����Ӧ�ó���ʼִ�е�ʱ��*/
	static inline const TimeStamp& getStartTime() {
		return _startStamp;
	};

protected:
	static TimeStamp _startStamp;

	int _seconds;
	int _milliSeconds;
};


#endif