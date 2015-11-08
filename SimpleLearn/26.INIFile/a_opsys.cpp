//---------------------------------------------------------------------------
// a_opsys.cpp
//
// operating system specific functions
//
// Copyright (C) 2006 Neil Butterworth
//---------------------------------------------------------------------------

#include <windows.h>
#include "a_opsys.h"
using std::string;

namespace CXW {

//----------------------------------------------------------------------------

string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

//---------------------------------------------------------------------------

} // namespace

// end

