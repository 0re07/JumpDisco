#pragma once
#include <vector>
#include "../Obj.h"

#include "../../rapidxml/rapidxml.hpp"
#include "../../rapidxml/rapidxml_utils.hpp"

struct ModuleNode;

class StateXML
{
public:
	StateXML(Obj& obj_, std::string key);
	~StateXML();

	void Update(void);

private:
	Obj& obj_;

	std::unique_ptr<ModuleNode> moduleNode_;
	rapidxml::xml_node<>* stateNode_;
};

