/***************************************************************************/
/* 
循环调用可行性测试
XDDll.h
创建时间：2010-11-15 17:03:59
创建人：陈小伟
修改记录：
2010-11-20 22:15:39 ：陈小伟，结果集改为由类描述，构造函数里初始化count值
*/
/***************************************************************************/
#ifndef _XDDLL_H_
#define _XDDLL_H_

using namespace std;

#define XDDLL_EXPORTS	//导出需定义，导入请注释

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#ifdef  XDDLL_EXPORTS
#define XDDLL(type) extern "C" __declspec(dllexport) type _stdcall
#else
#define XDDLL(type) extern "C" __declspec(dllimport) type _stdcall
#endif
#else
#define UAPI(type) type
#endif

typedef long HRECORDSET;//结果集句柄

#define SGC_RETCODE_SUCCESS 0					//成功
#define SGRDC_ERRORCODE_HRECORDSET_UNDEFINED -2	//结果集句柄无效
#define SGRDC_HRECORDSET_LENTH 100				//结果集的集合的大小
#define SGRDC_HRECORDSET_START 1				//结果集起始编号
#define SGRDC_HRECORDSET_BUFFER_ERROR -1		//初始化结果集内存错误
#define SGRDC_HRECORDSET_GET_ALL 0				//结果集内数据已经取完
#define SGRDC_HRECORDSET_NOT_GET_ALL 1			//结果集内数据尚未取完

struct Mresult 
{	
public:
	long* mpt;
	long long* sts;
	long count;
	long type;


public:
	Mresult()
	{
		type = 0;
		count = 0;
		mpt = NULL;
		sts = NULL;
	}

	~Mresult()
	{
		RecordsetRelease();
	}

public:
	void RecordsetAlloc(long mtype,long sizecount)//type:数据类型，sizecount分配长度
	{
		switch (mtype)
		{
		case 1:
			{
				if (mpt)
				{
					this->RecordsetRelease();
				}
				mpt = new long[sizecount];
				memset(mpt,0,sizeof(long)*sizecount);

			}break;
		case 2:
			{
				if (sts)
				{
					this->RecordsetRelease();
				}
				sts = new long long[sizecount];
				memset(mpt,0,sizeof(long long)*sizecount);

			}break;
		default:
			break;
		}
		type = mtype;
		count = sizecount;
	}
	void RecordsetRelease(void)
	{
		switch (type)
		{
		case 1:
			{
				if (mpt)
				{
					delete[] mpt;
				}
				mpt = NULL;
			}break;
		case 2:
			{
				if (sts)
				{
					delete[] sts;
				}
				sts = NULL;
			}break;
		default:
			break;
		}
		count = 0;
		type = 0;
	}
};


XDDLL(long) QueryHandleValues(/*IN*/long inputinfo);

XDDLL(long) GetNextValues(/*IN*/const HRECORDSET	hRecordset,
						  /*IN,OUT*/long			*start,
						  /*IN,OUT*/long			*pts,
						  /*IN,OUT*/long			*count);

XDDLL(long) ReleaseHRecordset(/*IN*/const HRECORDSET	hRecordset);

#endif