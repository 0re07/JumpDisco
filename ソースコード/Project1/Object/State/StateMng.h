#pragma once
#include <map>
#include <string>
#include "State.h"

#include "../../rapidxml/rapidxml.hpp"
#include "../../rapidxml/rapidxml_utils.hpp"

#define lpStateMng StateMng::GetInstance()

class StateMng
{
public:

	struct StateStr {
		std::vector<char> stateVec_;
		rapidxml::xml_document<> stateDoc_;
		rapidxml::xml_node<>* stateNode_;
	};

	bool Load(std::string fileName, std::string key);
	rapidxml::xml_node<char>* GetNode(std::string key);

	static StateMng& GetInstance(void)
	{
		return *s_Instance;
	}

	static StateMng& Create(void);
	static bool Destroy(void);

private:
	static StateMng* s_Instance;
	StateMng();
	~StateMng();

	std::map<std::string, StateStr> data_;
};

