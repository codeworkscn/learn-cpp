/***************************************************************************/
/* 
ѭ�����ÿ����Բ���
XDDll.h
����ʱ�䣺2010-11-15 17:03:59
�����ˣ���Сΰ
�޸ļ�¼��
2010-11-20 22:15:39 ����Сΰ���������Ϊ�������������캯�����ʼ��countֵ
*/
/***************************************************************************/
#ifndef _XDDLL_H_
#define _XDDLL_H_

using namespace std;

#define XDDLL_EXPORTS	//�����趨�壬������ע��

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#ifdef  XDDLL_EXPORTS
#define XDDLL(type) extern "C" __declspec(dllexport) type _stdcall
#else
#define XDDLL(type) extern "C" __declspec(dllimport) type _stdcall
#endif
#else
#define UAPI(type) type
#endif

typedef long HRECORDSET;//��������

#define SGC_RETCODE_SUCCESS 0					//�ɹ�
#define SGRDC_ERRORCODE_HRECORDSET_UNDEFINED -2	//����������Ч
#define SGRDC_HRECORDSET_LENTH 100				//������ļ��ϵĴ�С
#define SGRDC_HRECORDSET_START 1				//�������ʼ���
#define SGRDC_HRECORDSET_BUFFER_ERROR -1		//��ʼ��������ڴ����
#define SGRDC_HRECORDSET_GET_ALL 0				//������������Ѿ�ȡ��
#define SGRDC_HRECORDSET_NOT_GET_ALL 1			//�������������δȡ��

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
	void RecordsetAlloc(long mtype,long sizecount)//type:�������ͣ�sizecount���䳤��
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