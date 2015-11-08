/************************************************************************/
/*
写入日志到文件
创建时间：2010-12-3 16:38:37
创建人：陈小伟
修改记录：
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
	/* 写日志到文件
	输入参数：
	filename：日志文件名
	module：所属模块
	info：日志信息
	status：状态(0：成功 ，其它：失败) */
	void WriteLogToFile(const char* filename,
		const char* module,
		const char* info,
		const int status=0);

};

#endif
