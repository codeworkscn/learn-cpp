#include<stdio.h>
#include <iostream>

using namespace std;

void mstrcat(char *,char*);

int Test6(void){
	char *s="hello";
	char *t="world";
	mstrcat(s,t);
	return 0;
}   
void mstrcat(char *s,char *t)
{   
	while(*s)
	{
		cout << *s  << *t << endl;
		memcpy(&s,&t,1) ;
		s++;
		t++;
	}
	s -= 5;
// 	while(*s++=*t++)
// 	{
// 		NULL;
// 	} 
	printf("%s\n",s);
}   