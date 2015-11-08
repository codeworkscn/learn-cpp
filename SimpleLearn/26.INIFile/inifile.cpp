/*! 
*  \file	  inifile.cpp
*  \brief     IniFile 源文件
*  \details   IniFile 源文件，包含IniFile类的实现，用于管理ini文件
*  \author    陈小伟 
*  \version   1.1
*  \date      2012-7-18
*  \bug       报告BUG，请联系 cxwtc123@gmail.com
*  \copyright free
*/
#include <fstream>
#include "inifile.h"
#include "a_str.h"

using std::string;
using std::vector;

namespace CXW {

//----------------------------------------------------------------------------
// create inifile object (not disk file), populating if filename provided
//----------------------------------------------------------------------------

IniFile :: IniFile( const string & filename ) {
	if ( filename != "" ) {
		Read( filename );
	}
}

//----------------------------------------------------------------------------
// do clear
//----------------------------------------------------------------------------

IniFile :: ~IniFile() {
	Clear();
}

//----------------------------------------------------------------------------
// remove entries & reset filename
//----------------------------------------------------------------------------

void IniFile :: Clear() {
	mMap.clear();
	mFileName = "";
}

//----------------------------------------------------------------------------
// helper to check if line is comment or empty
// note line will alreadhy have been trimmed
//----------------------------------------------------------------------------

static bool IsComment( const string & line ) {
	if ( line == "" || line[0] == ';' || line[0] == '#' ) {
		return true;
	}
	else {
		return false;
	}
}

//----------------------------------------------------------------------------
// helper to get section name - an empty name is ok
//----------------------------------------------------------------------------

static bool GetSection( const string & line, string & sect ) {
	if ( line[0] == '[' ) {
		if ( StrLast( line ) == ']' ) {
			sect = Trim( line.substr( 1, line.length() - 2 ) );
			return true;
		}
		else {
			//ATHROW( "Invalid section: " << sect );
			return false;
		}
	}
	else {
		return false;
	}
}

//----------------------------------------------------------------------------
// read named inifile, replacing any existing content
//----------------------------------------------------------------------------

void IniFile :: Read( const string & filename ) {
	Clear();
	mFileName = filename;
	std::ifstream ifs( filename.c_str() );
	if ( ! ifs.is_open() ) {
		//ATHROW( "Cannot open config file: " << filename );
		return;
	}
	string line, sect;
	while( std::getline( ifs, line ) ) {
		line = Trim( line );
		if ( IsComment( line ) ) {
			continue;
		}
		else if ( GetSection( line, sect ) ) {
			if ( HasSection( sect ) ) {
				//ATHROW( "Duplicate section name: " << sect );
				continue;//以当前最近 Section 为准
			}
		}
		else {
			vector <string> vs;
			if ( Split( line, '=', vs ) != 2 ) {
				//ATHROW( "Invalid setting: " << line );
				continue;
			}
			if ( HasSetting( sect, vs[0] ) ) {
				//ATHROW( "Duplicate setting " << vs[0] << " in section ["
// 							<< sect << "]" );
				continue;
			}
			Add( sect, vs[0], vs[1] );
		}
	}
}

bool IniFile :: Save( const std::string & filename ) const {
	std::ofstream ofs( filename.c_str() );
	if ( ! ofs.is_open() ) {
		//ATHROW( "Cannot open config save file: " << filename );
		return false;
	}
	std::string lastsection = "";

	for (IniFile ::MapType::const_iterator it = mMap.begin () ; it != mMap.end () ; it ++)
	{
		if (lastsection != it->first.mSection)
		{
			ofs << std::endl << "[" << it->first.mSection << "]" << std::endl;
			lastsection = it->first.mSection;
		}
		ofs << it->first.mName << " = " << it->second << std::endl;
	}

	ofs.close();
	return true;
}

//----------------------------------------------------------------------------
// save to file name last loaded - return false when mFileName is empty
//----------------------------------------------------------------------------

bool IniFile :: Save() const {
	if (mFileName.empty ())
	{
		return false;
	}
	return Save(mFileName);
}


//----------------------------------------------------------------------------
// get file name last loaded - may be empty
//----------------------------------------------------------------------------

const string & IniFile :: FileName() const {
	return mFileName;
}

//----------------------------------------------------------------------------
// add entry, replacing any existing entry
//----------------------------------------------------------------------------

void IniFile :: Add( const string & section,
						const string & name,
						const string & value )  {

	Key k( section, name );
	MapType::iterator it = mMap.find( k );
	if ( it != mMap.end() ) {
		mMap.erase( it );
	}
	mMap.insert( std::make_pair( k, value ) );
}

//----------------------------------------------------------------------------
// modify entry, only replacing existing entry
//----------------------------------------------------------------------------

void IniFile :: Modify( const std::string & section,
					   const std::string & name,
					   const std::string & value ) {
	Key k( section, name );
	MapType::iterator it = mMap.find( k );
	if ( it != mMap.end() ) {
		mMap.erase( it );
		mMap.insert( std::make_pair( k, value ) );
	}
}

//----------------------------------------------------------------------------
// delete entry, delete existing entry
//----------------------------------------------------------------------------

void IniFile :: Del( const std::string & section,
					const std::string & name) {
	Key k( section, name );
	MapType::iterator it = mMap.find( k );
	if ( it != mMap.end() ) {
		mMap.erase( it );
	}
}

//----------------------------------------------------------------------------
// see if named section exist
//----------------------------------------------------------------------------

bool IniFile :: HasSection( const string & section ) const {
	MapType::const_iterator it = mMap.begin();
	while( it != mMap.end() ) {
		if ( Equal( it->first.mSection, section ) ) {
			return true;
		}
		++it;
	}
	return false;
}


//----------------------------------------------------------------------------
// see if named section & value name exists
//----------------------------------------------------------------------------

bool IniFile :: HasSetting( const string & section, const string & name ) const {
	Key k( section, name );
	return mMap.find( k ) != mMap.end();
}

//----------------------------------------------------------------------------
// get value or empty string if not there
//----------------------------------------------------------------------------

string IniFile :: Value( const string & section, const string & name ) const {
	Key k( section, name );
	MapType::const_iterator it = mMap.find( k );
	if ( it == mMap.end() ) {
		return "";
	}
	else {
		return it->second;
	}
}

//----------------------------------------------------------------------------
// construct key for entry
//----------------------------------------------------------------------------

IniFile::Key :: Key( const std::string & sect, const std::string & name )
	: mSection( sect ), mName( name ) {
}

//----------------------------------------------------------------------------
// do case insensitive comparison of two keys
//----------------------------------------------------------------------------

bool IniFile::Key :: operator < ( const IniFile::Key & e ) const {
	if ( Cmp( this->mSection, e.mSection, IgnoreCase ) < 0 ) {
		return true;
	}
	else if ( Cmp( this->mSection, e.mSection, IgnoreCase ) == 0
	          && Cmp( this->mName, e.mName, IgnoreCase ) < 0 ) {
		return true;
	}
	else {
		return false;
	}
}

//----------------------------------------------------------------------------

} // namespace

// end

