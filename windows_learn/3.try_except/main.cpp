#include <iostream>

using namespace std;

int main()
{

	__try {
		// ���쳣�ĺ���
		int* pTest = NULL; 
		*pTest = 0; // Ϊ��ָ�븳ֵ�����򽫱���
	}
	__except( EXCEPTION_EXECUTE_HANDLER ){
		// �쳣����
		cout << "__except!" << endl;
	}
};
