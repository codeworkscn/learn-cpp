#include "Includes.h"


//Map��Hash_MapЧ�ʶԱȲ���
//2012-4-24
//��Сΰ
void MyBenchMark(void)
{
	time_t timecount1 = 0;
	time_t timecount2 = 0;
	time_t timejg = 0;
	double ssss1 = 0.0;
	double ssss2 = 0.0;
	MapStr2LL mymap;
	HashName2ID myhashmap;

	MapStr2LL::iterator mymapIter;
	HashName2ID::iterator myhashmapIter;

	long long temp = 0;

	const long STR_LEN  = 64;
	char niaodan[STR_LEN];

	long everyaa = 100;
	long everybb = 100000;

	cout << "map config: " << endl;
	cout << "size : " << mymap.size () << endl;
	cout << "max_size : " << mymap.max_size() << endl;

	cout << endl;

	cout << "hash_map config: " << endl;
	cout << "bucket_count : " << myhashmap.bucket_count () << endl;
	cout << "max_bucket_count : " << myhashmap.max_bucket_count () << endl;
	cout << "max_size : " << myhashmap.max_size () << endl;

	LARGE_INTEGER   t1,   t2,   tc , startt, endt ;   
	QueryPerformanceFrequency(&tc); 
	double frequency = 1.0;
	frequency = (double)tc.QuadPart/1000000;

	cout << "frequency = " << frequency << endl; 

	QueryPerformanceCounter(&startt);
	for (long i=0;i<everyaa;i++)
	{
		QueryPerformanceCounter(&t1); 
		for (long j=0;j<everybb;j++)
		{
			mymap[itoa(i*everybb+j,niaodan,10)]=i*everybb+j;
		}
		QueryPerformanceCounter(&t2);  
		timejg = (t2.QuadPart-t1.QuadPart)/frequency;
		cout << "�� " << i << " �β���" << everybb << "���ɹ�����ʱ "  << timejg <<" us" << endl;
		timecount1 += timejg;
	}
	QueryPerformanceCounter(&endt);

	ssss1 = (double)everyaa*everybb/((double)(endt.QuadPart - startt.QuadPart)/tc.QuadPart);
	cout << "Map����" << everyaa*everybb << "���ɹ�������ʱ " << (double)everyaa*everybb / ssss1 << " s������ƽ��������: " << ssss1 << endl;
	cout << "��ȥ��ӡʱ�䣬��ʱ " << (double)timecount1/1000000 << " s������ƽ��������: " << (double)everyaa*everybb*1000000/(double)timecount1 << endl;

	QueryPerformanceCounter(&startt);
	for (long i=0;i<everyaa;i++)
	{
		QueryPerformanceCounter(&t1); 
		for (long j=0;j<everybb;j++)
		{
			myhashmap[itoa(i*everybb+j,niaodan,10)]=i*everybb+j;
		}
		QueryPerformanceCounter(&t2);  
		timejg = (t2.QuadPart-t1.QuadPart)/frequency;
		cout << "�� " << i << " �β���" << everybb << "���ɹ�����ʱ "  << timejg <<" us" << endl;
		timecount2 += timejg;
	}
	QueryPerformanceCounter(&endt);

	ssss2 = (double)everyaa*everybb/((double)(endt.QuadPart - startt.QuadPart)/tc.QuadPart);
	cout << "HashMap���� " << everyaa*everybb << " ���ɹ�������ʱ " << (double)everyaa*everybb / ssss2 << " s������ƽ��������: " << ssss2 << endl;
	cout << "��ȥ��ӡʱ�䣬��ʱ " << (double)timecount2/1000000 << " s������ƽ��������: " << (double)everyaa*everybb*1000000/(double)timecount2 << endl;

	timecount1 = 0 ;
	timecount2 = 0 ;	

	QueryPerformanceCounter(&startt);
	for (long i=0;i<everyaa;i++)
	{
		QueryPerformanceCounter(&t1); 
		for (long j=0;j<everybb;j++)
		{
			mymapIter = mymap.find(itoa(i*everybb+j,niaodan,10));
		}
		QueryPerformanceCounter(&t2);  
		timejg = (t2.QuadPart-t1.QuadPart)/frequency;
		timecount1 += timejg;

		cout << "key :" << mymapIter->first.c_str() << " value : " << mymapIter->second << endl;
		cout << "Map�� " << i << " �β�ѯ" << everybb << "���ɹ�����ʱ "  << timejg <<" us" << endl;
	}
	QueryPerformanceCounter(&endt);
	ssss1 = (double)everyaa*everybb/((double)(endt.QuadPart - startt.QuadPart)/tc.QuadPart);
	cout << "Map��ѯ " << everyaa*everybb << " ���ɹ�������ʱ " << (double)everyaa*everybb / ssss1 << " s������ƽ��������: " << ssss1 << endl;
	cout << "��ȥ��ӡʱ�䣬��ʱ " << (double)timecount1/1000000 << " s������ƽ��������: " << (double)everyaa*everybb*1000000/(double)timecount1 << endl;

	QueryPerformanceCounter(&startt);
	for (long i=0;i<everyaa;i++)
	{
		QueryPerformanceCounter(&t1); 
		for (long j=0;j<everybb;j++)
		{
			myhashmapIter = myhashmap.find(itoa(i*everybb+j,niaodan,10));
		}
		QueryPerformanceCounter(&t2);  

		timejg = (t2.QuadPart-t1.QuadPart)/frequency;
		timecount2 += timejg;

		cout << "key :" << myhashmapIter->first.c_str() << " value : " << myhashmapIter->second << endl;
		cout << "HashMap�� " << i << " �β�ѯ" << everybb << "���ɹ�����ʱ "  << timejg <<" us" << endl;
	}
	QueryPerformanceCounter(&endt);
	ssss2 = (double)everyaa*everybb/((double)(endt.QuadPart - startt.QuadPart)/tc.QuadPart);

	cout << "HashMap��ѯ " << everyaa*everybb << " ���ɹ�������ʱ " << (double)everyaa*everybb / ssss2 << " s������ƽ��������: " << ssss2 << endl;
	cout << "��ȥ��ӡʱ�䣬��ʱ " << (double)timecount2/1000000 << " s������ƽ��������: " << (double)everyaa*everybb*1000000/(double)timecount2 << endl;

	cout << "map config: " << endl;
	cout << "size : " << mymap.size () << endl;
	cout << "max_size : " << mymap.max_size() << endl;
	cout << endl;
	cout << "hash_map config: " << endl;
	cout << "bucket_count : " << myhashmap.bucket_count () << endl;
	cout << "max_bucket_count : " << myhashmap.max_bucket_count () << endl;
	cout << "max_size : " << myhashmap.max_size () << endl;

	cout << endl << "clear..." << endl << endl;

	mymap.clear();
	myhashmap.clear ();

	cout << "map config: " << endl;
	cout << "size : " << mymap.size () << endl;
	cout << "max_size : " << mymap.max_size() << endl;
	cout << endl;
	cout << "hash_map config: " << endl;
	cout << "bucket_count : " << myhashmap.bucket_count () << endl;
	cout << "max_bucket_count : " << myhashmap.max_bucket_count () << endl;
	cout << "max_size : " << myhashmap.max_size () << endl;
}
