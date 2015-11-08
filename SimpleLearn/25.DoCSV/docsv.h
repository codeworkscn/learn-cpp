

#ifndef _SGRDC_DOCSV_H
#define _SGRDC_DOCSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSVSTRLENTH 64
#define CSVROWLENTH 1000

/*

1.针对csv文件的操作主要有添加(Add)、修改(Modify)、删除(Delete)、插入(Insert)、排序(Sort)，其中除排序外其它

 函数都分按行(Raw)、按列(Col)、按单元格(行标列标)(x\y)对csv文件进行操作；

2.函数命名规律为1中英文组合，如插入一行函数为csvInsertRaw()等;

3.函数使用前预先定义CSVSTRLENTH,作为使用到的数组的长度；

4.函数参数用filename(文件路径)的，务必保证使用前该文件为关闭状态；

5.函数参数用文件指针的，须在使用前打开(多为用"r"方式打开)、使用后关闭；

*/




//函数声明

int _RemoveDH(char [],char [],int);

//1.关键点，实现逗号分隔的分离

int _AddDH(char [][CSVSTRLENTH],char [],int);

//2.与函数RemoveDH()相反，将若干个字符串合成逗号分隔的形式

int _DHamount(char []);

//3.判断输入的字符串中有几个逗号

int _pipei(char [],char []);

//4.判断两字符串是否相互包含

int _FileSX(char [],char []);

//5.设置、去除文件只读、系统文件或隐藏属性

int csvGetSignX(FILE *);

//6.文件的行数

int csvGetSignY(FILE *);

//7.文件的列数

int csvGetFile(FILE *,char [][CSVSTRLENTH]);

//8.读取整个csv文件

int csvGetRaw(FILE *,int,char []);

//9.取一行

int csvGetCol(FILE *,int,char [][CSVSTRLENTH]);

//10.取一列

int csvGetxy(FILE *,int,int,char []);

//11.按坐标取值，取某个单元格

int csvSort(char [],int,int);

//12.实现对csv文件按任意列的排序，将该列数据转换为浮点数

int csvModify(char [],int,int,char[]);

//13.将csv文件中的某行某列的内容修改为字符串str

int csvDeletexy(char [],int,int);

//14.按行标、列标删除csv文件中的内容(单元格)，只是将单元格中内容清除，保留单元格

int csvDeleteRaw(char [],int);

//15.删除csv文件中的一行

int csvDelete_xy(char [],int,int);

//16.按行标、列标删除csv文件中的内容(单元格)，完全将单元格删除

int csvDeleteCol(char [],int);

//17.按列标删除csv文件中的内容(单元格)，完全将单元格删除

int csvFindStr(FILE *,char [],int,int [],int []);

//18.寻找csv文件中的特定的字符串，并获得其对应的行标和列标，用整形数组存储行标、列标

int csvInsertRaw(char [],int,int);

//19.在csv文件中插入一空行

int csvInsertCol(char [],int,int);

//20.在csv文件中插入一空列

int NewFile(char []);

//21.创建csv文件，不需输入.csv

int csvAddtoFile(char [],char [],char [][CSVSTRLENTH],int);

//22.将二维数组(已进行逗号分隔)写入csv文件

int csvAddtoRaw(char [],int,int,int,char [][CSVSTRLENTH]);

//23.在csv文件中添加(修改)一行数据，可在csvInsertRaw()后，即先插入行，再添加数据。

//   也可直接调用，视为修改某行信息。

int csvAddtoCol(char [],int,int,int,char [][CSVSTRLENTH]);

//24.在csv文件中添加(修改)一列数据，可在csvInsertCol()后，即先插入列，再添加数据。

//   也可直接调用，视为修改某列信息。


int csvAddtoxy(char [],int,int,char []);

//25.在csv文件某行某列添加数据，可在csvInsertxy()后，即先插入单元格，再添加数据。

//   若直接调用，可用来修改单元格数据。


#endif