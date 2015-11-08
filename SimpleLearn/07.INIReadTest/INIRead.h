#ifndef _C_INIREAD_DLL_H_
#define _C_INIREAD_DLL_H_

#define  INIREAD_EXPORTS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	#if defined  INIREAD_EXPORTS
		#define INIREAD(type) extern "C" __declspec(dllexport) type _stdcall
	#elif defined INIREAD_EXPORTS
		#define INIREAD(type) extern "C" __declspec(dllimport) type _stdcall
	#else
		#define INIREAD(type) type
	#endif
#endif

#define ERROR_GET_ERROR		-1	//��ȡ�ɹ�
#define SUCCESS_GET_SUCCESS 0	//��ȡʧ��

/************************************************************************/
INIREAD(long) SGRDC_Get_INI_Info(/*IN*/const wchar_t *name,
								 /*IN*/const wchar_t *info,
								 /*OUT*/wchar_t *iniName);
/*
�������ܣ���ȡ�����ļ�����Ŀ��Ϣ
�������:name����
		 info��Ϣ��Ŀ	
�������:iniName��Ϣ����
���ز���:
ERROR_GET_ERROR		ʧ��
SUCCESS_GET_SUCCESS	�ɹ�
*/
/************************************************************************/



#endif
