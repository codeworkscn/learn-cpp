

//void kongkong()
//{
//	HANDLE hMutex = CreateMutex (NULL, FALSE, "mMap Mutex");
//
//
//	DWORD dw = WaitForSingleObject(hMutex, INFINITE);
//
//	if (WAIT_FAILED == dw)
//	{
//		printf("Wait for mutex error.");
//		CloseHandle(hMutex); // 释放句柄，当指向同一系统对象的所有句柄释放后，该对象将被删除。
//		return -1;
//	}
//	else if (WAIT_TIMEOUT == dw)
//	{
//		// 另外一个实例正在运行
//		CloseHandle(hMutex);
//		return 1;
//	}
//
//	mMap.insert(pair<long,long>(1,1));
//
//	ReleaseMutex(hMutex); // 释放hMutex的持有权，注意这并不等同于删除Mutex对象
//	CloseHandle(hMutex);
//}