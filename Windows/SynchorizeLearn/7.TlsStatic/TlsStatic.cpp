/*
声明静态绑定线程的本地对象和变量时必须遵守下列原则：

thread 属性只能应用于数据声明和定义。它不能用于函数声明或定义。例如，下面的代码生成一个编译器错误： 

复制代码 
#define Thread  __declspec( thread )
Thread void func();     // This will generate an error.


只能在具有 static 作用域的数据项上指定 thread 修饰符。包括全局数据对象（包括 static 和 extern）、本地静态对象和 C++ 类的静态数据成员。不可以用 thread 属性声明自动数据对象。下面的代码生成编译器错误： 

复制代码 
#define Thread  __declspec( thread )
void func1()
{
Thread int tls_i;            // This will generate an error.
}

int func2( Thread int tls_i )    // This will generate an error.
{
return tls_i;
}


线程本地对象的声明和定义必须全都指定 thread 属性。例如，下面的代码将生成错误： 

复制代码 
#define Thread  __declspec( thread )
extern int tls_i;        // This will generate an error, since the
int Thread tls_i;        // declaration and definition differ.


thread 属性不能用作类型修饰符。例如，下面的代码生成一个编译器错误： 

复制代码 
char __declspec( thread ) *ch;        // Error


C++ 类不能使用 thread 属性。但是，可以使用 thread 属性实例化 C++ 类对象。例如，下面的代码生成一个编译器错误： 

复制代码 
#define Thread  __declspec( thread )
class Thread C       // Error: classes cannot be declared Thread.
{
// Code
};
C CObject;


因为允许使用 thread 属性的 C++ 对象的声明，因此下面两个示例在语义上是等效的：

复制代码 
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


不将线程本地对象的地址视为常数，并且涉及此类地址的任何表达式都不视为常数。在标准 C 中，这种作法的效果是禁止将线程本地变量的地址用作对象或指针的初始值设定项。例如，C 编译器会将下面的代码标记为错误：

复制代码 
#define Thread  __declspec( thread )
Thread int tls_i;
int *p = &tls_i;       //This will generate an error in C.


但是，此限制不适用于 C++。因为 C++ 允许动态初始化所有对象，因此可以用使用线程本地变量地址的表达式初始化对象。实现此操作的方式与实现线程本地对象结构的方式相同。例如，以上显示的代码在作为 C++ 源文件编译时不会生成错误。请注意：只有在其中获取地址的线程仍然存在的情况下，线程本地变量的地址才有效。

标准 C 允许使用涉及引用自身的表达式初始化对象或变量，但只适用于非静态作用域的对象。虽然 C++ 通常允许使用涉及引用自身的表达式动态初始化对象，但是这种类型的初始化不允许用于线程本地对象。例如：

复制代码 
#define Thread  __declspec( thread )
Thread int tls_i = tls_i;                // Error in C and C++ 
int j = j;                               // OK in C++, error in C
Thread int tls_i = sizeof( tls_i )       // Legal in C and C++


注意，包含正在初始化的对象的 sizeof 表达式不建立对自身的引用且在 C 和 C++ 中都是合法的。 

C++ 不允许此类对线程数据的动态初始化，因为将来可能要对线程本地存储功能进行增强。

如果 DLL 将任何非本地数据或对象声明为 __declspec（线程），动态加载该 DLL 时会导致保护错误。使用 LoadLibrary 加载所有 DLL 后，每当代码引用非本地 __declspec（线程）数据时，将导致系统故障。由于线程的全局变量空间是在运行时分配的，因此此空间的大小是以应用程序的需求和所有静态链接的 DLL 的需求相加为基础计算出来的。使用 LoadLibrary 时，无法扩展此空间以允许放置用 __declspec（线程）声明的线程本地变量。如果 DLL 可能是用 LoadLibrary 加载的，请在 DLL 中使用 TLS API（如 TlsAlloc）来分配 TLS。

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
