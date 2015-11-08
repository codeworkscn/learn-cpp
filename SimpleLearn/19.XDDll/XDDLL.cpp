#include <iostream>
#include "XDDLL.h" 

using namespace std;

//Mresult* mpts = new Mresult[SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START];
Mresult mpts[SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START];

XDDLL(long) QueryHandleValues(/*IN*/long inputinfo)
{
	long mcount = SGRDC_HRECORDSET_BUFFER_ERROR;
	for (long i = SGRDC_HRECORDSET_START ;i<SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START;i++)		//从1到99，最多能存放共99个结果集
	{
		if (! mpts[i].count && mpts[i].mpt == NULL)
		{
			mcount = i;//计算得到结果集句柄
			
			//---------------以下创建结果集---------------//
			mpts[mcount].RecordsetAlloc(1,100010);//分配空间

			for (long i = 0 ; i < 100010 ; i ++)	//赋值
			{
				mpts[mcount].mpt[i] = i;
			}
			//----------------以上创建结果集--------------//

			break; 
		}
	}
	return mcount;
}

XDDLL(long) GetNextValues(/*IN*/const HRECORDSET	hRecordset,
						  /*IN,OUT*/long			*start,
						  /*IN,OUT*/long			*pts,
						  /*IN,OUT*/long			*count)
{
	if (mpts[hRecordset].mpt == NULL)
	{
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;	//结果集句柄无效
	}
	long nRet  = 0;
	long i = 0 ;

	//加入调用者没有取完数据，就用*start超过数目的入参来取数据，返回数据已经取完，并释放结果集
	if (*start >= mpts[hRecordset].count)	
	{
		ReleaseHRecordset(hRecordset);//释放结果集	
		*count = 0;
		return SGRDC_HRECORDSET_GET_ALL; //数据已经取完
	}
	for (i = 0 ; i < *count ; i ++)
	{
		if (*start + i < mpts[hRecordset].count)
		{
			pts[i] = mpts[hRecordset].mpt[*start + i];

		}
		else
		{
			break;
		}
	}
	*count = i;
	*start += i;
	if (*start == mpts[hRecordset].count)	//如果输完了，就释放结果集
	{
		nRet = SGRDC_HRECORDSET_GET_ALL;	//数据已经取完
		ReleaseHRecordset(hRecordset);		//释放结果集
	}
	else
	{
		nRet = SGRDC_HRECORDSET_NOT_GET_ALL;
	}
	return nRet;
}

XDDLL(long) ReleaseHRecordset(/*IN*/const HRECORDSET	hRecordset)
{
	if ( hRecordset < SGRDC_HRECORDSET_START || hRecordset >= SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START)
	{
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;//结果集句柄无效
	}
	else if (mpts[hRecordset].mpt != NULL)
	{
		mpts[hRecordset].RecordsetRelease();
		return SGC_RETCODE_SUCCESS ;//成功
	}
	else
	{
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;//结果集句柄无效
	}
}