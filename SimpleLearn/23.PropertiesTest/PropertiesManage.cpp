// ******************************************************************
//
// 2012-7-3, chenxw, modify for *.ini file  read, 
//			from orbacus Properties class
// 2012-7-3 13:56:33, chenxw, add save function.
//
// orbacus copyright:Progress Software Corporation (PSC)
//
// ******************************************************************

#include <stdlib.h>
#include <fstream>
#include "PropertiesManage.h"

// ----------------------------------------------------------------------
// PropertiesManage constructor and destructor
// ----------------------------------------------------------------------

PropertiesManage::PropertiesManage()
{
}


PropertiesManage::~PropertiesManage()
{
}

// ----------------------------------------------------------------------
// PropertiesManage public member implementation
// ----------------------------------------------------------------------


//
// Set a property value
//
void
PropertiesManage::setProperty(const char* key, const char* value)
{
	//key 为空 则返回
	if (NULL == key)
	{
		return;
	}

	for(unsigned long i = 0; i < props_.size(); i += 2)
	{
		//如果已经存在
		if(props_[i]== key)
		{
			//修改value
			props_[i+1] = value;
			return;
		}
	}

	//不存在，则增加
	props_.push_back (key) ;
	props_.push_back (value) ;
}

//
// Get a property value, 0 if no such property exists
//
const char*
PropertiesManage::getProperty(const char* key) const
{
	for(unsigned long i = 0; i < props_.size(); i += 2)
	{
		if(props_[i]== key)
		{
			return props_[i+1].c_str();
		}
	}

	return 0;
}

PropertiesManage::KeySeq
PropertiesManage::getKeys(const char* prefix) const
{
	KeySeq keys;
	int prefLen = strlen(prefix);
	for(unsigned long i = 0; i < props_.size(); i += 2)
	{
		if(strncmp(props_[i].c_str(), prefix, prefLen) == 0) 
		{
			keys.push_back (props_[i]) ;
		}
	}
	return keys;
}

PropertiesManage::KeySeq
PropertiesManage::getKeys() const
{
	KeySeq keys;
	for(unsigned long i = 0; i < props_.size(); i += 2)
	{
		keys.push_back (props_[i]) ;
	}
	return keys;
}

bool
PropertiesManage::load(const char* name)
{
	if(NULL == name)
	{
		return false;
	}

	ifstream in; // Must use open(name), not ifstream in(name) (VC++ bug)
	in.open(name);
	if(in.fail())
		return false;

	char ch;
	in.get(ch);


	string key = "";
	string value = "";

	while(in)
	{
		key = "";
		value = "";

		//
		// Find start of key
		//
		switch(ch)
		{
		case '#':
		case '!':
			do
			{
				in.get(ch);
			}
			while(in && ch != '\n' && ch != '\r');
			continue;

		case '\n':
		case '\r':
		case ' ':
		case '\t':
			in.get(ch);
			continue;
		}

		//
		// Read the key
		//
		while(in &&
			(ch != '=') && (ch != ':') && 
			(ch != ' ') && (ch != '\t') &&
			(ch != '\n') && (ch != '\r'))
		{
			key += ch;
			in.get(ch);
		}
		while(in && ((ch == ' ') || (ch == '\t')))
			in.get(ch);
		if(in && ((ch == '=') || (ch == ':')))
			in.get(ch);
		while(in && ((ch == ' ') || (ch == '\t')))
			in.get(ch);

		//
		// Read the value
		//
		while(in && ((ch != '\n') && (ch != '\r')))
		{
			char next = 0;

			//处理转义字符
			if (ch == '\\')
			{
				if(!in.get(ch))
					continue;
				switch (ch)
				{
					// '\' 之后就.....
				case '\r':
					in.get(ch);
					if (in && ((ch == '\n') || (ch == ' ') || (ch == '\t')))
					{
						// fall thru to '\n' case
					}
					else
						continue;

					// '\' 之后就换行，说明是续行标记
				case '\n':
					in.get(ch);
					while(in && ((ch == ' ') || (ch == '\t')))
						in.get(ch);
					continue;

					//制表符
				case 't':
					ch = '\t';
					in.get(next);
					break;

					//换行符
				case 'n':
					ch = '\n';
					in.get(next);
					break;

				case 'r':
					ch = '\r';
					in.get(next);
					break;

					//十六进制编码表示的字符
				case 'u':
					{
						while(in && ch == 'u')
							in.get(ch);
						int d = 0;
						bool stop = false;
						for(int i = 0 ; i < 4 && !stop; ++i)
						{
							if(!in.get(ch))
								break;
							switch (ch)
							{
							case '0': case '1': case '2': case '3': case '4':
							case '5': case '6': case '7': case '8': case '9':
								d = (d << 4) + ch - '0';
								break;
							case 'a': case 'b': case 'c': case 'd': case 'e':
							case 'f':
								d = (d << 4) + 10 + ch - 'a';
								break;
							case 'A': case 'B': case 'C': case 'D': case 'E':
							case 'F':
								d = (d << 4) + 10 + ch - 'A';
								break;
							default:
								stop = true;
							}
							if(!stop)
								ch = next;
						}
						ch = d;
						break;
					}

				default:
					in.get(next);
					break;
				}
			}
			else
			{
				in.get(next);
			}
			value += ch;
			ch = next;
		}
		setProperty(key.c_str(), value.c_str());
	}
	in.close();
	filename_ = name;
	return true;
}


bool PropertiesManage::save(const char* name)
{
	ofstream out; // Must use open(name), not ifstream in(name) (VC++ bug)
	out.open(name);
	if(out.fail())
		return false;

	string key = "";
	string value = "";

	//配置文件全部重写
	for(unsigned long i = 0; i < props_.size(); i += 2)
	{
		//key 不处理
		key = props_[i] ;

		//value需判断是否有转义字符，变成转义表达之后保存
		string tempvalue = props_[i+1] ;
		value = "";

		for (unsigned int j = 0 ;j < props_[i+1].length() ; j++)
		{
			char ch = props_[i+1][j];
			switch (ch)
			{
			case '\r':
				value += "\\r";break;

			case '\n':
				value += "\\n";break;

			case '\t':
				value += "\\t";break;

			case '\\':
				value += "\\\\";break;

			default:
				value += ch;break;
			}
		}

		out << key << " = " << value << endl;
	}
	out.close();
	return true;
}

bool PropertiesManage::save()
{
	return save(filename_.c_str());
}


#ifdef _WIN32
//
// Add all values in this registry key, and all subkeys.
//
bool
PropertiesManage::load(HKEY base, const char* path, const char* prefix)
{

	HKEY key;

	//
	// Open the registry.
	//
	DWORD rc = RegOpenKeyEx(base, path, 0, KEY_READ, &key);

	//
	// If the key doesn't exist, then return.
	//
	if(rc != ERROR_SUCCESS)
		return false;

	// Buffer for class name.
	char className[MAX_PATH] = "";
	// Length of class string.
	DWORD szClassLen = MAX_PATH;
	// Number of sub keys.
	DWORD numSubKeys;
	// Longest sub key size.
	DWORD numMaxSubKey;
	// Longest class string.
	DWORD numMaxClass;
	// Number of values for this key.
	DWORD numValues;
	// Longest Value name.
	DWORD  maxValueName;
	// Longest Value data.
	DWORD  maxValueData;
	// Security descriptor.
	DWORD  secDesc;
	// Last write time.
	FILETIME lastWriteTime;

	//
	// Query registry information.
	//
	RegQueryInfoKey(key,               // Key handle.
		className,         // Buffer for class name.
		&szClassLen,       // Length of class string.
		NULL,              // Reserved.
		&numSubKeys,       // Number of sub keys.
		&numMaxSubKey,     // Longest sub key size.
		&numMaxClass,      // Longest class string.
		&numValues,        // Number of values for this key.
		&maxValueName,     // Longest Value name.
		&maxValueData,     // Longest Value data.
		&secDesc,          // Security descriptor.
		&lastWriteTime);   // Last write time.

	//
	// We need to allocate one more byte for storage.
	//
	++maxValueName;
	++maxValueData;

	int i;
	DWORD szValueName;
	char* valueName = new char[maxValueName];
	DWORD szData;
	unsigned char* data = new unsigned char[maxValueData];
	DWORD type;

	//
	// Enumerate each value in this registry key.
	//
	for(i = 0, rc = ERROR_SUCCESS; rc == ERROR_SUCCESS; ++i)
	{
		szValueName = maxValueName;
		valueName[0] = '\0';
		szData = maxValueData;
		rc = RegEnumValue(key, i, valueName,
			&szValueName, 0,
			&type, data, &szData);

		//
		// Did we get a valid key?
		//
		if(rc == ERROR_SUCCESS)
		{
			//
			// The key should be a string, otherwise it's ignored
			//
			if(type == REG_SZ)
			{
				//
				// Construct the property name.
				//
				char name[MAX_PATH];
				strcpy(name, prefix);
				strcat(name, ".");
				strcat(name, valueName);

				//
				// Set the property.
				//
				setProperty(name, (const char*)data);
			}
		}
	}
	delete[] valueName;
	delete[] data;

	//
	// Recurse down each set of subkeys.
	//
	char name[MAX_PATH];
	for(i = 0, rc = ERROR_SUCCESS; rc == ERROR_SUCCESS; ++i)
	{
		rc = RegEnumKey(key, i, name, MAX_PATH);
		if(rc == ERROR_SUCCESS)
		{
			//
			// Construct the subkey path name.
			//
			char buf[MAX_PATH];
			strcpy(buf, path);
			strcat(buf, "\\");
			strcat(buf, name);

			//
			// Construct the subkey property prefix.
			//
			char pref[MAX_PATH];
			if(*prefix != '\0')
			{
				strcpy(pref, prefix);
				strcat(pref, ".");
			}
			else
			{
				*pref = '\0';
			}
			strcat(pref, name);

			//
			// Add all values contained in this subkey.
			//
			if(!load(base, buf, pref))
				return false;
		}
	}

	//
	// Close the registry key.
	//
	RegCloseKey(key);

	return true;
}
#endif