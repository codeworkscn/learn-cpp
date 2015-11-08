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

#define ERROR_GET_ERROR		-1	//获取成功
#define SUCCESS_GET_SUCCESS 0	//获取失败

/************************************************************************/
INIREAD(long) SGRDC_Get_INI_Info(/*IN*/const wchar_t *name,
								 /*IN*/const wchar_t *info,
								 /*OUT*/wchar_t *iniName);
/*
函数功能：读取配置文件，条目信息
输入参数:name名称
		 info信息条目	
输出参数:iniName信息内容
返回参数:
ERROR_GET_ERROR		失败
SUCCESS_GET_SUCCESS	成功
*/
/************************************************************************/



#endif
