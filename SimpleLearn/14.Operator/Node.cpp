#include "Node.h"
// using namespace std;

//  bool compare(const DAFIdentifiers::ResourceID& nRid,const DAFIdentifiers::ResourceID &mRid);


// ::DAIS::CDaNode::CDaNode(void)
// {
// 	m_Nodes = new CDaNodeMaps(compare);
// 	m_Items = new CDaItemMaps(compare);;
// }

// ::DAIS::CDaNode::~CDaNode(void)
// {
// 
// 
// }


void ::DAIS::CDaNode::add_child (const DAIS::CDaNode &childNode)
{


	::DAIS::ResourceID rId = childNode.id;
// 	this->m_Nodes.insert(::DAIS::CDaNodeMaps::value_type(rId,childNode));
}