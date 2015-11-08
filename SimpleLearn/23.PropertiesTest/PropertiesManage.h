// ******************************************************************
//
// 2012-7-3, chenxw, modify for *.ini file  read, 
//			from orbacus Properties class
// 2012-7-3 13:56:33, chenxw, add save function.
// 2012-7-4 ,chenxw, how about read-only file?..
//
// orbacus copyright:Progress Software Corporation (PSC)
//
// ******************************************************************

#ifndef _SGRDC_PropertiesManage_H
#define _SGRDC_PropertiesManage_H

#include <iostream>
#include <string>
#include <vector>


//
// for bool load(HKEY, const char*, const char*);
// only useable in windows
//
#ifdef _WIN32
#include <Windows.h>
#endif


using namespace std;


class PropertiesManage
{
    //
    // Hide copy-constructor and assignment operator
    //
    PropertiesManage(const PropertiesManage&);
    void operator=(const PropertiesManage&);
private:
	string filename_;

public:

    typedef vector<string> KeySeq;

protected:

    //
    // PropertiesManage data
    //
    KeySeq props_;

    
public:

    //
    // Create an empty property set
    //
    PropertiesManage();

    ~PropertiesManage();

    //
    // Set and get a property
    //
    void setProperty(const char*, const char*);
    const char* getProperty(const char*) const;

    //
    // Get all property keys starting with prefix
    // Get all property keys
    //
    KeySeq getKeys(const char* prefix) const;
    KeySeq getKeys() const;

    //
    // Load the Properties from a file. Returns false if the file
    // could not be opened. The value of errno should be checked to
    // determine the cause of the error.
    //
    bool load(const char*);


	//
	// Save the Properties to a file. Returns false if the file
	// could not be saved. The value of errno should be checked to
	// determine the cause of the error.
	//
	bool save(const char*);

	//
	// Save the Properties to the default file. Returns false if the file
	// could not be saved. The value of errno should be checked to
	// determine the cause of the error.
	//
	bool save();


#ifdef _WIN32
    //
    // Load the Properties from the registry. Returns false if the
    // registry key could not be opened.
    //
    bool load(HKEY, const char*, const char*);


#endif
};


#endif
