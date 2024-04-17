#include "GetAttr.h"
#include "State.h"
#include "StateMng.h"
#include "StateXML.h"

#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"

StateXML::StateXML(Obj& obj, std::string key) : obj_(obj)
{
	moduleNode_ = std::make_unique<ModuleNode>();
	stateNode_ = lpStateMng.GetNode(key);
}

StateXML::~StateXML()
{
}

void StateXML::Update(void)
{
	//ステート制御
	for (auto actNode = stateNode_->first_node();
		actNode != nullptr;
		actNode = actNode->next_sibling())
	{
		std::string actNodeName;
		GetAttr()(actNode, "name", actNodeName);
		//_TRACE_S(0xffffff, "actNodeName", actNodeName);

		(*moduleNode_)(&obj_, actNode);

		if (moduleNode_ == nullptr)
		{
			return;
		}
	}
}
