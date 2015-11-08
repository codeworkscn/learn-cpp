#ifndef _m_node_h_
#define _m_node_h_

#include "DAIS.h"
using namespace std;

bool compare(const DAFIdentifiers::ResourceID& nRid,const DAFIdentifiers::ResourceID &mRid);


namespace DAIS
{
	class CDaNode;
	typedef map<::DAIS::ResourceID,::DAIS::CDaNode,ResourceIDComp> CDaNodeMaps;

	class CDaNode
	{
	public:
		CDaNode(void)
		{
			m_Nodes = new CDaNodeMaps(compare);
			m_Items = new CDaItemMaps(compare);
		}
		~CDaNode(void)
		{


		}

	public:


		ResourceID id;

		//��ȫ������ԣ���class�ڲ��򱨴�compareʧЧ��
  		CDaNodeMaps* m_Nodes;
  		CDaItemMaps* m_Items;

		void add_child (const DAIS::CDaNode &childNode);
	};
}


#endif
