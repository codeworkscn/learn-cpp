#include <iostream>
#include "inifile.h"

using namespace std;

int main(void)
{
	CXW::IniFile iniFile("cxw.ini");

	//Section  为空
	cout << "Color: [" << iniFile.Value ("","Color").c_str () << "]" << endl;
	cout << "Height: [" << iniFile.Value ("","Height").c_str () << "]" << endl;

	if (iniFile.HasSection ("PERSON"))
	{
		cout << "Male: [" << iniFile.Value ("PERSON","Male").c_str () << "]" << endl;
		cout << "Female: [" << iniFile.Value ("PERSON","Female").c_str () << "]" << endl;
	}
	else
	{
		cout << "do not has section of PERSON" << endl;
	}

	if (iniFile.HasSection ("LOCATION"))
	{
		cout << "Male: [" << iniFile.Value ("LOCATION","Loc1").c_str () << "]" << endl;
		cout << "Female: [" << iniFile.Value ("LOCATION","Loc2").c_str () << "]" << endl;
	}
	else
	{
		cout << "do not has section of LOCATION" << endl;
	}

	iniFile.Add("" ,"HH" ,"HaHa");
	iniFile.Add("Add" ,"Name" ,"CXW");
	iniFile.Add("Beauty" , "Most" , "XW");
	if (iniFile.Save ("cxwsave.ini"))
	{
		cout << "save ini info to file [cxwsave.ini] success."  << endl;
	}
	else
	{
		cout << "save ini info to file [cxwsave.ini] error."  << endl;
	}

	return 0;
};