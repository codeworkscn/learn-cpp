#ifndef _m_dais_h_
#define _m_dais_h_

#include <map>
#include "DAF.h"
#include "Operator.h"

using namespace std;

namespace DAIS
{
	typedef ::DAFIdentifiers::ResourceID ResourceID;

	typedef map<ResourceID,long,ResourceIDComp> CDaItemMaps;


}



#endif
