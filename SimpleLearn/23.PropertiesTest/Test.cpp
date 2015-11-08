// ******************************************************************
//
// 2012-7-3, chenxw, add test case, 
// 2012-7-3 13:56:33, chenxw, add save test case.
//
// ******************************************************************

#include "PropertiesManage.h"


int main(void)
{
	PropertiesManage props;
	if (!props.load("cxw.ini"))
	{
		cout << "load ini file error! " << endl;
		return -1;
	}


	//get keys test
	cout << endl << "get keys test" << endl;

	PropertiesManage::KeySeq getKeys = props.getKeys ();

	cout << "size = " << getKeys.size () << endl;

	for (unsigned int i = 0 ; i < getKeys.size ();i ++ )
	{
		cout << "key : " << getKeys[i] 
		<< "  value: " << props.getProperty (getKeys[i].c_str()) 
			<< endl;
	}

	//get prefix keys test
	cout << endl << "get prefix keys test" << endl;

	PropertiesManage::KeySeq getKeysPrefix = props.getKeys ("cxw");

	cout << "size = " << getKeysPrefix.size () << endl;

	for (unsigned int i = 0 ; i < getKeysPrefix.size ();i ++ )
	{
		cout << "key : " << getKeysPrefix[i] 
		<< "  value: " << props.getProperty (getKeysPrefix[i].c_str())
			<< endl;
	}


	if(!props.save("cxwsave.ini"))
	{
		cout << "save ini file error! " << endl;
		return -2;
	}


	return 0;
};