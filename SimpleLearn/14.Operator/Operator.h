#ifndef _m_operator_h_
#define _m_operator_h_

#include <iostream>
#include "DAF.h"
// using namespace std;

bool operator<(const DAFIdentifiers::ResourceID& nRid,const DAFIdentifiers::ResourceID &mRid);

bool operator==(const DAFIdentifiers::ResourceID& nRid,const DAFIdentifiers::ResourceID &mRid);

bool compare(const DAFIdentifiers::ResourceID& nRid,const DAFIdentifiers::ResourceID &mRid);

typedef bool (*ResourceIDComp)(const DAFIdentifiers::ResourceID&,const DAFIdentifiers::ResourceID&);

class compare
{

};

#endif