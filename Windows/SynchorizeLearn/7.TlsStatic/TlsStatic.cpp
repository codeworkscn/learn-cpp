/*
������̬���̵߳ı��ض���ͱ���ʱ������������ԭ��

thread ����ֻ��Ӧ�������������Ͷ��塣���������ں����������塣���磬����Ĵ�������һ������������ 

���ƴ��� 
#define Thread  __declspec( thread )
Thread void func();     // This will generate an error.


ֻ���ھ��� static ���������������ָ�� thread ���η�������ȫ�����ݶ��󣨰��� static �� extern�������ؾ�̬����� C++ ��ľ�̬���ݳ�Ա���������� thread ���������Զ����ݶ�������Ĵ������ɱ��������� 

���ƴ��� 
#define Thread  __declspec( thread )
void func1()
{
Thread int tls_i;            // This will generate an error.
}

int func2( Thread int tls_i )    // This will generate an error.
{
return tls_i;
}


�̱߳��ض���������Ͷ������ȫ��ָ�� thread ���ԡ����磬����Ĵ��뽫���ɴ��� 

���ƴ��� 
#define Thread  __declspec( thread )
extern int tls_i;        // This will generate an error, since the
int Thread tls_i;        // declaration and definition differ.


thread ���Բ��������������η������磬����Ĵ�������һ������������ 

���ƴ��� 
char __declspec( thread ) *ch;        // Error


C++ �಻��ʹ�� thread ���ԡ����ǣ�����ʹ�� thread ����ʵ���� C++ ��������磬����Ĵ�������һ������������ 

���ƴ��� 
#define Thread  __declspec( thread )
class Thread C       // Error: classes cannot be declared Thread.
{
// Code
};
C CObject;


��Ϊ����ʹ�� thread ���Ե� C++ ����������������������ʾ�����������ǵ�Ч�ģ�

���ƴ��� 
#define Thread  __declspec( thread )
Thread class B
{
// Code
} BObject;               // OK--BObject is declared thread local.

class B
{
// Code
};
Thread B BObject;        // OK--BObject is declared thread local.


�����̱߳��ض���ĵ�ַ��Ϊ�����������漰�����ַ���κα��ʽ������Ϊ�������ڱ�׼ C �У�����������Ч���ǽ�ֹ���̱߳��ر����ĵ�ַ���������ָ��ĳ�ʼֵ�趨����磬C �������Ὣ����Ĵ�����Ϊ����

���ƴ��� 
#define Thread  __declspec( thread )
Thread int tls_i;
int *p = &tls_i;       //This will generate an error in C.


���ǣ������Ʋ������� C++����Ϊ C++ ����̬��ʼ�����ж�����˿�����ʹ���̱߳��ر�����ַ�ı��ʽ��ʼ������ʵ�ִ˲����ķ�ʽ��ʵ���̱߳��ض���ṹ�ķ�ʽ��ͬ�����磬������ʾ�Ĵ�������Ϊ C++ Դ�ļ�����ʱ�������ɴ�����ע�⣺ֻ�������л�ȡ��ַ���߳���Ȼ���ڵ�����£��̱߳��ر����ĵ�ַ����Ч��

��׼ C ����ʹ���漰��������ı��ʽ��ʼ��������������ֻ�����ڷǾ�̬������Ķ�����Ȼ C++ ͨ������ʹ���漰��������ı��ʽ��̬��ʼ�����󣬵����������͵ĳ�ʼ�������������̱߳��ض������磺

���ƴ��� 
#define Thread  __declspec( thread )
Thread int tls_i = tls_i;                // Error in C and C++ 
int j = j;                               // OK in C++, error in C
Thread int tls_i = sizeof( tls_i )       // Legal in C and C++


ע�⣬�������ڳ�ʼ���Ķ���� sizeof ���ʽ��������������������� C �� C++ �ж��ǺϷ��ġ� 

C++ �����������߳����ݵĶ�̬��ʼ������Ϊ��������Ҫ���̱߳��ش洢���ܽ�����ǿ��

��� DLL ���κηǱ������ݻ��������Ϊ __declspec���̣߳�����̬���ظ� DLL ʱ�ᵼ�±�������ʹ�� LoadLibrary �������� DLL ��ÿ���������÷Ǳ��� __declspec���̣߳�����ʱ��������ϵͳ���ϡ������̵߳�ȫ�ֱ����ռ���������ʱ����ģ���˴˿ռ�Ĵ�С����Ӧ�ó������������о�̬���ӵ� DLL ���������Ϊ������������ġ�ʹ�� LoadLibrary ʱ���޷���չ�˿ռ������������ __declspec���̣߳��������̱߳��ر�������� DLL �������� LoadLibrary ���صģ����� DLL ��ʹ�� TLS API���� TlsAlloc�������� TLS��

*/

#include <windows.h> 
#include <stdio.h> 

#define Thread  __declspec( thread )

Thread int tls_i = 1;

#define THREADCOUNT 4 


VOID ErrorExit(LPSTR); 

DWORD WINAPI ThreadFunc(VOID) 
{ 
	int threadi = 0;
	int i;

	tls_i = GetCurrentThreadId();
	

	for(i=0; i<5; i++)
	{
		threadi = tls_i;

		printf("thread %d: lpvData=%d\n", GetCurrentThreadId(),threadi); 

		Sleep(10); 
	}
	return 0; 
} 

int main(VOID) 
{ 
	DWORD IDThread; 
	HANDLE hThread[THREADCOUNT]; 
	int i; 

	// Create multiple threads. 

	for (i = 0; i < THREADCOUNT; i++) 
	{ 
		hThread[i] = CreateThread(NULL, // default security attributes 
			0,                           // use default stack size 
			(LPTHREAD_START_ROUTINE) ThreadFunc, // thread function 
			NULL,                    // no thread function argument 
			0,                       // use default creation flags 
			&IDThread);              // returns thread identifier 

		// Check the return value for success. 
		if (hThread[i] == NULL) 
			ErrorExit("CreateThread error\n"); 
	} 

	for (i = 0; i < THREADCOUNT; i++) 
		WaitForSingleObject(hThread[i], INFINITE); 

	return 0; 
} 

VOID ErrorExit (LPSTR lpszMessage) 
{ 
	fprintf(stderr, "%s\n", lpszMessage); 
	ExitProcess(0); 
}
