#include<iostream>
#include<string>

using namespace std;

int Test3(void)
{
	const char* refFile = "G:\\MyExample\\Learn\\Learn1\\Debug\\haha.txt";
	char s[2048] ;

	FILE* in = fopen(refFile,"rb");

	if(in == NULL)
	{
		printf("error open %s file to read\n",refFile);
		system("pause");
		exit(1);
	}

	fgets(s,sizeof(s),in);
	//fread(s,1,300,in);

	fclose(in);
	return 0 ;
}