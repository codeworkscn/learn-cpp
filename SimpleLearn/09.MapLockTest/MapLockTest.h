

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
//		CloseHandle(hMutex); // �ͷž������ָ��ͬһϵͳ��������о���ͷź󣬸ö��󽫱�ɾ����
//		return -1;
//	}
//	else if (WAIT_TIMEOUT == dw)
//	{
//		// ����һ��ʵ����������
//		CloseHandle(hMutex);
//		return 1;
//	}
//
//	mMap.insert(pair<long,long>(1,1));
//
//	ReleaseMutex(hMutex); // �ͷ�hMutex�ĳ���Ȩ��ע���Ⲣ����ͬ��ɾ��Mutex����
//	CloseHandle(hMutex);
//}