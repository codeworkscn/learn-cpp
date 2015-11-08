
//csv操作代码

#include "docsv.h"

///////////////////////////////////////////////////////

//程序代码、函数功能说明、参数说明、及返回值

///////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////
/*

关键点，实现逗号分隔的分离，分离后可用数组存储，也可以不以逗号

分隔的形式重新写入另一文件，进行其它操作。

参数说明：str[]为传入的字符串，aim[]为分离后要存储的位置，Xth

表示要分离出第几项。若传入的Xth大于字符串中逗号个数，则返回逗号

个数；否则，返回分离出的字符串的长度

*/
////////////////////////////////////////////////////////////////

int _RemoveDH(char str[],char aim[],int Xth)
{
	int i,j,left,right;
	for(i=0,j=0;str[i]!='\0';i++)
		if(str[i]==',') j++;
	j += 1;
	if(Xth>j) return j;
	for(left=0,i=0;str[left]!='\0';left++)
	{
		if(str[left]==',') i++;
		if(i==Xth-1) break;
	}
	for(i=0,right=0;str[right]!='\0';right++)
	{
		if(str[right]==',') i++;
		if(i==Xth) break;
	}
	if(Xth!=1) left++;
	for(i=left,j=0;i<right;i++,j++)
		aim[j]=str[i];
	aim[j]='\0';
	return j;
}





/*
函数功能：与函数RemoveDH()相反，将若干个字符串合成逗号分隔的形式。

参数说明：1.存储分离的字符串的二维数组；

		  2.合成后要存储的目标字符串；

          3.要合成的字符串的个数。

函数返回值：返回值为合成逗号分隔后字符串的总长度。
*/

int _AddDH(char ManyStr[][CSVSTRLENTH],char TogStr[],int amount)
{
	int count,lenth;
	for(count=0,lenth=0;count<amount;count++)
		lenth+=strlen(ManyStr[count]);
	strcpy(TogStr,ManyStr[0]);
	strcat(TogStr,",");
	for(count=1;count<amount;count++)
	{
		strcat(TogStr,ManyStr[count]);
		strcat(TogStr,",");
	}
	strcat(TogStr,"\0");
	return (lenth+amount);
}



////////////////////////////////////////////////
//判断输入的字符串中有几个逗号
////////////////////////////////////////////////

int _DHamount(char str[])
{
	int i,j;
	for(i=0,j=0;str[i]!='\0';i++)
		if(str[i]==',') j++;
	return j+1;
}



//////////////////////////////////////////////////////
/*

设置文件属性，参数SX[],"+R +S +H"代表分别将文件属性设置为只读、系统文件、隐藏，

"-R -S -H"代表将文件去除只读、系统文件、隐藏属性。

若文件不存在返回0，成功返回1.

*/
//////////////////////////////////////////////////////

int _FileSX(char filename[],char SX[])
{
	char filename_2[100]="attrib ";
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	fclose(fp);
	strcat(filename_2,filename);
	strcat(filename_2," ");
	strcat(filename_2,"SX");
	system(filename_2);
	return 1;
}


/*

函数功能：文件的行数。

参数说明：文件指针。

返回值：返回文件的行数.

*/

int csvGetSignX(FILE *fp)
{
	int iRaw;
	char str[64];
	if(fp==NULL) return 0;
	for(iRaw=0;!feof(fp);iRaw++)
		fscanf(fp,"%s",str);
	rewind(fp);
	return (iRaw-1);
}

/*

函数功能：文件的列数。

参数说明：文件指针。

返回值：返回文件的列数.

*/

int csvGetSignY(FILE *fp)
{
	int iCol;
	char str[64];
	if(fp==NULL) return 0;
	fscanf(fp,"%s",str);
	iCol=_DHamount(str);
	rewind(fp);
	return iCol;
}

//读取整个csv文件
/*
参数说明：1.文件指针；2.要存储的位置。

返回值：返回文件中的行数。
*/

int csvGetFile(FILE *fp,char cStrRaw[][CSVSTRLENTH])
{
	int sign,iRaw;
	if(fp==NULL) return 0;
	sign=csvGetSignX(fp);
	for(iRaw=0;iRaw<sign;iRaw++)
		fscanf(fp,"%s",cStrRaw[iRaw]);
	rewind(fp);
	return sign;
}



//取一行
/*

参数说明：传入的参数分别为文件指针、行标、取出后存放的字符串。

若文件指针为空，返回0；若要取得的行标大于文件中实际的行数，返回实际行数；

成功则返回(-1*实际行数).

*/

int csvGetRaw(FILE *fp,int line,char str[])
{
	int i,j;
	if(line<=0) return 0;
	if(fp==NULL) return 0;
	j=csvGetSignX(fp);
	if(line>j) return j;
	for(i=1;i<=line;i++)
		fscanf(fp,"%s",str);
	rewind(fp);
	return (-1*j);
}



//取一列
/*

参数说明：传入的参数分别为文件指针、列标、取出后存放的字符串(二维数组，二维长度必须设为 CSVSTRLENTH 的值)。

若文件指针为空，返回0；若要取得的列标大于文件中实际的列数，返回实际列数；

成功则返回(-1*实际列数).

*/

int csvGetCol(FILE *fp,int col,char str[][CSVSTRLENTH])
{
	int iDH,iRaw,sign;
	char cStr[CSVSTRLENTH];
	if(col<=0) return 0;
	if(fp==NULL) return 0;
	fscanf(fp,"%s",cStr);
	iDH=_DHamount(cStr);
	if(col>iDH)	return iDH;
	rewind(fp);
	sign=csvGetSignX(fp);
	for(iRaw=0;iRaw<sign;iRaw++)
	{
		fscanf(fp,"%s",cStr);
		_RemoveDH(cStr,str[iRaw],col);
	}
	rewind(fp);
	return (-1*iDH);

}

//按坐标取值
/*

参数说明：传入的参数分别为文件指针、行标、列标、取出后存放的字符串。

若文件指针为空，返回0；若要取得的行标大于文件中实际的行数，返回实际行数；

若要取得的列标大于文件中实际的列数，返回实际列数；成功则返回-1.

*/

int	csvGetxy(FILE *fp,int x,int y,char str[])
{
	char cStr[CSVSTRLENTH];
	int iRe,iDH;
	if(x<=0||y<=0||x>csvGetSignX(fp)||y>csvGetSignY(fp)) return 0;
	if(fp==NULL) return 0;
	iRe=csvGetRaw(fp,x,cStr);
	if(iRe>=0) return iRe;
	iDH=_DHamount(cStr);
	if(y>iDH) return iDH;
	_RemoveDH(cStr,str,y);
	return -1;

}





/*
函数功能：实现对csv文件按任意列的排序。

参数说明：1)文件路径；2)列标；3)从大到小(大于0)或从小到大(小于0)；

对文件的要求：1.文件后缀名须是.csv或者txt文件用逗号分隔存储；
			  
	      2.文件中最后一行须是换行符，否则最后一行的数据将会丢失；

	      3.对应2中的要求，向文件中输入时注意最后一行为换行符，方式可为fprintf(fp,"……\n",……);

*/

int csvSort(char filename[],int col,int a_z)
{
	FILE *fp;
	char cStrCol[CSVSTRLENTH][CSVSTRLENTH],cStrRaw[CSVSTRLENTH][CSVSTRLENTH],str[CSVSTRLENTH];
	int i,iCol,iRaw,BSi,BSj;
	double iStrCol[CSVSTRLENTH],temp;
	if(col<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	iCol=csvGetCol(fp,col,cStrCol);
	if(iCol>=0) return 0;
	rewind(fp);
	for(iRaw=0;!feof(fp);iRaw++)
		fgets(cStrRaw[iRaw],CSVSTRLENTH,fp);
	fclose(fp);
	iRaw--;
	for(i=0;i<iRaw;i++)
		iStrCol[i]=atof(cStrCol[i]);

	for(BSi=1;BSi<=iRaw;BSi++)
	for(BSj=0;BSj<iRaw-BSi;BSj++)
	{
		if(a_z<0&&iStrCol[BSj]>iStrCol[BSj+1])
		{
			temp=iStrCol[BSj];
			iStrCol[BSj]=iStrCol[BSj+1];
			iStrCol[BSj+1]=temp;
			strcpy(str,cStrRaw[BSj]);
			strcpy(cStrRaw[BSj],cStrRaw[BSj+1]);
			strcpy(cStrRaw[BSj+1],str);
			

		}
		else if(a_z>=0&&iStrCol[BSj]<=iStrCol[BSj+1])
		{
			temp=iStrCol[BSj];
			iStrCol[BSj]=iStrCol[BSj+1];
			iStrCol[BSj+1]=temp;
			strcpy(str,cStrRaw[BSj]);
			strcpy(cStrRaw[BSj],cStrRaw[BSj+1]);
			strcpy(cStrRaw[BSj+1],str);
		}
	}
	fp=fopen(filename,"w");
	for(i=0;i<iRaw;i++)
		fprintf(fp,"%s",cStrRaw[i]);
	fclose(fp);
	return 1;
}




/*
函数功能：将csv文件中的某行某列的内容修改为字符串str。

参数说明：1.文件路径；

          2.第二、第三个参数分别为要修改的行标、列标；

          3.要重新写入的字符串。

返回值：成功返回1，出错返回0.

函数使用要求：要求调用函数之前务必将文件关闭，否则可能会发生错误。

注：凡是在参数中使用文件路径的时候，均要符合该要求。

*/


int csvModify(char filename[],int x,int y,char str[])
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH][CSVSTRLENTH],AimRaw[CSVSTRLENTH][CSVSTRLENTH],xRaw[CSVSTRLENTH];
	int iRaw,iDH,count;
	if(x<=0||y<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	for(iRaw=0;!feof(fp);iRaw++)
		fscanf(fp,"%s",cStrRaw[iRaw]);
	fclose(fp);
	iRaw--;
	iDH=_DHamount(cStrRaw[x-1]);
	if(iRaw<x||iDH<y) return 0;
	for(count=0;count<iDH;count++)
		_RemoveDH(cStrRaw[x-1],AimRaw[count],count+1);
	strcpy(AimRaw[y-1],str);
	_AddDH(AimRaw,xRaw,iDH);
	fp=fopen(filename,"w");
	for(count=0;count<iRaw;count++)
	{
		if(count!=x-1)
			fprintf(fp,"%s\n",cStrRaw[count]);
		else fprintf(fp,"%s\n",xRaw);
	}
	fclose(fp);
	return 1;
}



/*

函数功能：删除csv文件中的一行。

参数说明：1.文件路径；

          2.要删除的行标。

返回值：成功返回1，出错或未执行返回0.

*/


int csvDeleteRaw(char filename[],int iRaw)
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH][CSVSTRLENTH];
	int Raw,count;
	if(iRaw<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	for(Raw=0;!feof(fp);Raw++)
		fscanf(fp,"%s",cStrRaw[Raw]);
	fclose(fp);
	Raw--;
	if(iRaw>Raw) return (-1*Raw);
	fp=fopen(filename,"w");
	for(count=0;count<Raw;count++)
		if((count+1)!=iRaw)
			fprintf(fp,"%s\n",cStrRaw[count]);
	fclose(fp);
	return 1;
}







/*

函数功能：按行标、列标删除csv文件中的内容(单元格)，只是将单元格中内容清除。

参数说明：1.文件路径；

          2.要删除的行标、列标。

返回值：成功返回1，出错或未执行返回0.

*/


int csvDeletexy(char filename[],int x,int y)
{
	FILE *fp;
	if(x<=0||y<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	return csvModify(filename,x,y,"");
}







/*

函数功能：按行标、列标删除csv文件中的内容(单元格)，完全将单元格删除。应禁用，应使用csvDeletexy()函数。

参数说明：1.文件路径；

          2.要删除的行标、列标。

返回值：成功返回1，出错或未执行返回0.

*/




int csvDelete_xy(char filename[],int x,int y)
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH][CSVSTRLENTH],cStrCol[CSVSTRLENTH][CSVSTRLENTH];
	char _cStrRaw[CSVSTRLENTH],_cStrCol[CSVSTRLENTH][CSVSTRLENTH];
	int Raw,iDH,count,count_2;
	if(x<=0||y<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	for(Raw=0;!feof(fp);Raw++)
		fscanf(fp,"%s",cStrRaw[Raw]);
	fclose(fp);
	Raw--;
	if(x>Raw) return (-1*Raw);
	iDH=_DHamount(cStrRaw[x-1]);
	if(iDH==1)
	{
		fp=fopen(filename,"w");
		fclose(fp);
		return 1;
	}
	if(y>iDH) return (-1*iDH);
	for(count=0;count<iDH;count++)
		_RemoveDH(cStrRaw[x-1],cStrCol[count],count+1);
	for(count=0,count_2=0;count<iDH;count++)
		if((count+1)!=y)
		{
			strcpy(_cStrCol[count_2],cStrCol[count]);
			count_2++;
		}
	_AddDH(_cStrCol,_cStrRaw,iDH-1);
	puts(_cStrRaw);
	fp=fopen(filename,"w");
	for(count=0;count<Raw;count++)
		if((count+1)!=x)
			fprintf(fp,"%s\n",cStrRaw[count]);
		else fprintf(fp,"%s\n",_cStrRaw);
	fclose(fp);
	return 1;
}






/*

函数功能：按列标删除csv文件中的内容(单元格)，完全将单元格删除。

参数说明：1.文件路径；

          2.要删除的列标。

返回值：成功返回1，出错或未执行返回0.

*/



int csvDeleteCol(char filename[],int iCol)
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH];
	int iDH,iRaw,count;
	if(iCol<=0) return 0;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	iRaw=csvGetRaw(fp,1,cStrRaw);
	fclose(fp);
	iDH=_DHamount(cStrRaw);
	if(iCol>iDH) return 0;	
	for(count=1;count<=(-1*iRaw);count++)
		csvDelete_xy(filename,count,iCol);
	return 1;
}




/*

函数功能：判断两字符串是否相互包含。

参数说明：1.字符串1；

          2.字符串2.

返回值：相互包含返回1，否则返回0.

*/


int _pipei(char str[],char str2[])
{
	unsigned int i=1,j=2,pipei1=3,pipei2=4,n=5;
	for(i=0,pipei1=0;i<strlen(str);i++)
		for(j=i;j<strlen(str2);j++)
			if(str[i]==str2[j])
			{
				pipei1++;
				break;
			}
	for(j=0,pipei2=0;j<strlen(str2);j++)
		for(n=j;n<strlen(str);n++)
			if(str2[j]==str[n])
			{
				pipei2++;
				break;
			}
	if(i==pipei1||j==pipei2)
		return 1;
	else
		return 0;
}


/*

函数功能：寻找csv文件中的特定的字符串，并获得其对应的行标和列标。

参数说明：1.文件指针；

          2.要寻找的字符串；

          3.整形数据，为0则仅全词匹配，非0则非全词匹配下查询；

          4.要存储行标、列标的整形数组，遍历文件时，将查询到的字符串的坐标全部存储。

返回值：返回文件中该字符串的个数.

*/


int csvFindStr(FILE *fp,char str[],int PiPei,int PosX[],int PosY[])
{
	char cStrRaw[CSVSTRLENTH],cStrCol[CSVSTRLENTH];
	int iRaw,iCol,iDH,x,y,flag,count,sign;
	if(fp==NULL) return 0;
	sign=csvGetSignX(fp);
	for(iRaw=1,x=0,y=0,count=0;iRaw<=sign;iRaw++)
	{
		fscanf(fp,"%s",cStrRaw);
		iDH=_DHamount(cStrRaw);
		if(iDH==0) break;
		for(iCol=1;iCol<=iDH;iCol++)
		{
			flag=0;
			_RemoveDH(cStrRaw,cStrCol,iCol);
			if((PiPei!=0)&&(_pipei(str,cStrCol)==1))
				flag=1;
			if((PiPei==0)&&(strcmp(str,cStrCol)==0))
				flag=1;
			if(flag)
			{
				PosX[x]=iRaw;
				PosY[y]=iCol;
				x++;y++;count++;
			}
		}
	}
	rewind(fp);
	return count;
}


/*

函数功能：在csv文件中插入一空行。

参数说明：1.文件路径；

          2.要操作的行标；

          3.若sorx大于等于0，则在该行之上插入，若小于0，则在该行之下插入。

返回值：成功返回1.

*/

int csvInsertRaw(char filename[],int iRaw,int sorx)
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH][CSVSTRLENTH];
	int Raw,sign,iDH,count;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	sign=csvGetSignX(fp);
	if(iRaw>sign||iRaw<=0){fclose(fp); return (-1*sign);}
	for(Raw=0;Raw<sign;Raw++)
		fscanf(fp,"%s",cStrRaw[Raw]);
	fclose(fp);
	iDH=_DHamount(cStrRaw[0]);
	fp=fopen(filename,"w");
	if(iRaw==1){	
		for(count=1;count<=iDH;count++)
			fprintf(fp,"%s",",");
		fputc('\n',fp);	}
	for(Raw=0;Raw<sign;Raw++)
	{
		fprintf(fp,"%s\n",cStrRaw[Raw]);
		if((sorx<0&&(Raw+1==iRaw))||(sorx>=0&&(Raw+2==iRaw))) {
			for(count=1;count<=iDH;count++)
				fprintf(fp,"%s",",");
			fputc('\n',fp);}
	}
	fclose(fp);
	return 1;
}


/*

函数功能：在csv文件中插入一空列。

参数说明：1.文件路径；

          2.要操作的列标；

          3.若sorx大于等于0，则在该列之右插入，若小于0，则在该列之左插入。

返回值：成功返回1.

*/


int csvInsertCol(char filename[],int iCol,int zory)
{
	FILE *fp;
	char cStrRaw[CSVSTRLENTH][CSVSTRLENTH],_cStrRaw[CSVSTRLENTH][CSVSTRLENTH];
	char cStrCol[CSVSTRLENTH][CSVSTRLENTH],_cStrCol[CSVSTRLENTH][CSVSTRLENTH];
	int signX,signY,Col,Raw;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	signY=csvGetSignY(fp);
	signX=csvGetSignX(fp);
	if(iCol>signY||iCol<=0){fclose(fp);return (-1*signY);}
	for(Raw=0;Raw<signX;Raw++)
	{
		fscanf(fp,"%s",cStrRaw[Raw]);
		for(Col=0;Col<signY;Col++)
			_RemoveDH(cStrRaw[Raw],cStrCol[Col],Col+1);
		if(zory>=0){
			for(Col=0;Col<iCol;Col++)
				strcpy(_cStrCol[Col],cStrCol[Col]);
			strcpy(_cStrCol[Col],"");
			for(Col=iCol;Col<signY;Col++)
				strcpy(_cStrCol[Col+1],cStrCol[Col]);}
		else{
			for(Col=0;Col<iCol-1;Col++)
				strcpy(_cStrCol[Col],cStrCol[Col]);
			strcpy(_cStrCol[Col],"");
			for(Col=iCol-1;Col<signY;Col++)
				strcpy(_cStrCol[Col+1],cStrCol[Col]);}
		_AddDH(_cStrCol,_cStrRaw[Raw],signY+1);
	}
	fclose(fp);
	fp=fopen(filename,"w");
	for(Raw=0;Raw<signX;Raw++)
		fprintf(fp,"%s\n",_cStrRaw[Raw]);
	fclose(fp);
	return 1;
}


/*

函数功能：创建csv文件，需输入.csv。

参数说明：1.文件路径。

返回值：文件存在返回1，文件不存在创建成功返回0.

*/


int NewFile(char filename[])
{
	FILE *fp;
	//strcat(filename,".csv");
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		fp=fopen(filename,"w+");
		fclose(fp);
		return 0;
	}
	else {fclose(fp);return 1;}
}



/*

函数功能：将二维数组(已进行逗号分隔)写入csv文件。

参数说明：1.文件路径；

          2.文件打开方式，为"a+"或"w+"或"w"；

          3.二维数组。

          4.行数，即二维数组的一维长度。

返回值：成功返回1，出错返回0.

*/



int csvAddtoFile(char filename[],char method[],char cStrRaw[][CSVSTRLENTH],int iRaw)
{
	FILE *fp;
	int Raw,iDH;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	fclose(fp);
	iDH=_DHamount(cStrRaw[0]);
	for(Raw=1;Raw<iRaw;Raw++)
		if(_DHamount(cStrRaw[Raw])!=iDH)
			return 0;
	fp=fopen(filename,method);
	for(Raw=0;Raw<iRaw;Raw++)
		fprintf(fp,"%s\n",cStrRaw[Raw]);
	fclose(fp);
	return 1;
}



/*

函数功能：在csv文件中添加(修改)一行数据，可在csvInsertRaw()后，即先插入行，再添加数据。

          也可直接调用，视为修改某行信息。

参数说明：1.文件路径；

          2.要操作的行标；

          3、4.插入数据的列标，如在第2行第3-8列添加数据。

          5.二维数组，用于存储要添加的信息。

返回值：成功返回1.

*/




int csvAddtoRaw(char filename[],int iRaw,int iCol_1,int iCol_2,char cStrCol[][CSVSTRLENTH])
{
	FILE *fp;
	int Col,count;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	if(iRaw>csvGetSignX(fp)){fclose(fp); return 0;}
	if(iCol_1>iCol_2||iCol_1>csvGetSignY(fp)||iCol_2>csvGetSignY(fp)||iCol_1<=0||iCol_2<=0){
		fclose(fp); return 0;}
	fclose(fp);
	for(Col=iCol_1,count=0;Col<=iCol_2;Col++,count++)
		csvModify(filename,iRaw,Col,cStrCol[count]);
	return 1;
}



/*

函数功能：在csv文件中添加(修改)一列数据，可在csvInsertCol()后，即先插入列，再添加数据。

          也可直接调用，视为修改某列信息。

参数说明：1.文件路径；

          2.要操作的列标；

          3、4.插入数据的列标，如在第3-8行第2列添加数据。

          5.二维数组，用于存储要添加的信息。

返回值：成功返回1.

*/



int csvAddtoCol(char filename[],int iCol,int iRaw_1,int iRaw_2,char cStrRaw[][CSVSTRLENTH])
{
	FILE *fp;
	int Raw,count;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	if(iCol>csvGetSignY(fp)){fclose(fp); return 0;}
	if(iRaw_1>iRaw_2||iRaw_1>csvGetSignX(fp)||iRaw_2>csvGetSignX(fp)||iRaw_1<=0||iRaw_2<=0){
		fclose(fp); return 0;}
	fclose(fp);
	for(Raw=iRaw_1,count=0;Raw<=iRaw_2;Raw++,count++)
		csvModify(filename,Raw,iCol,cStrRaw[count]);
	return 1;
}


/*

函数功能：在csv文件某行某列添加数据，可在csvInsertxy()后，即先插入单元格，再添加数据。

          若直接调用，可用来修改单元格数据。

参数说明：1.文件路径；

          2.要操作的行标；

          3、要操作的列标。

          5.用于存储要添加的信息的数组。

返回值：成功返回1.

*/

int csvAddtoxy(char filename[],int x,int y,char iStr[])
{
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	if(x>csvGetSignX(fp)||y>csvGetSignY(fp)||x<=0||y<=0){fclose(fp);return 0;}
	fclose(fp);
	return csvModify(filename,x,y,iStr);
}