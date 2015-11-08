#include <iostream>
#include "XDDLL.h" 

using namespace std;

//Mresult* mpts = new Mresult[SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START];
Mresult mpts[SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START];

XDDLL(long) QueryHandleValues(/*IN*/long inputinfo)
{
	long mcount = SGRDC_HRECORDSET_BUFFER_ERROR;
	for (long i = SGRDC_HRECORDSET_START ;i<SGRDC_HRECORDSET_LENTH+SGRDC_HRECORDSET_START;i++)		//��1��99������ܴ�Ź�99�������
	{
		if (! mpts[i].count && mpts[i].mpt == NULL)
		{
			mcount = i;//����õ���������
			
			//---------------���´��������---------------//
			mpts[mcount].RecordsetAlloc(1,100010);//����ռ�

			for (long i = 0 ; i < 100010 ; i ++)	//��ֵ
			{
				mpts[mcount].mpt[i] = i;
			}
			//----------------���ϴ��������--------------//

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
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;	//����������Ч
	}
	long nRet  = 0;
	long i = 0 ;

	//���������û��ȡ�����ݣ�����*start������Ŀ�������ȡ���ݣ����������Ѿ�ȡ�꣬���ͷŽ����
	if (*start >= mpts[hRecordset].count)	
	{
		ReleaseHRecordset(hRecordset);//�ͷŽ����	
		*count = 0;
		return SGRDC_HRECORDSET_GET_ALL; //�����Ѿ�ȡ��
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
	if (*start == mpts[hRecordset].count)	//��������ˣ����ͷŽ����
	{
		nRet = SGRDC_HRECORDSET_GET_ALL;	//�����Ѿ�ȡ��
		ReleaseHRecordset(hRecordset);		//�ͷŽ����
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
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;//����������Ч
	}
	else if (mpts[hRecordset].mpt != NULL)
	{
		mpts[hRecordset].RecordsetRelease();
		return SGC_RETCODE_SUCCESS ;//�ɹ�
	}
	else
	{
		return SGRDC_ERRORCODE_HRECORDSET_UNDEFINED;//����������Ч
	}
}