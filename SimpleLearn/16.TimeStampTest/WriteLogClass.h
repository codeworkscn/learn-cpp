/************************************************************************/
/*
д����־���ļ�
����ʱ�䣺2010-12-3 16:38:37
�����ˣ���Сΰ
�޸ļ�¼��
                                                                  */
/************************************************************************/
#ifndef _SGRDC_WRITELOGCLASS_H_
#define _SGRDC_WRITELOGCLASS_H_

#include "TimeStamp.h"

class CWriteLogClass : public TimeStamp
{
public:
	CWriteLogClass(void);
	~CWriteLogClass(void);

/************************************************************************/
	/* д��־���ļ�
	���������
	filename����־�ļ���
	module������ģ��
	info����־��Ϣ
	status��״̬(0���ɹ� ��������ʧ��) */
	void WriteLogToFile(const char* filename,
		const char* module,
		const char* info,
		const int status=0);

};

#endif
