#include <iostream>

using namespace std;

int main()
{

	__try {
		// 会异常的函数
		int* pTest = NULL; 
		*pTest = 0; // 为空指针赋值，程序将崩溃
	}
	__except( EXCEPTION_EXECUTE_HANDLER ){
		// 异常处理
		cout << "__except!" << endl;
	}
};
