#include "StateXML.h"
#include "StateMng.h"

StateMng* StateMng::s_Instance = nullptr;

bool StateMng::Load(std::string fileName, std::string key)
{
	auto value = data_.try_emplace(key);
	//読み込んでいなかったら
	if (!value.second)
	{
		return false;
	}

	//ファイルを開きパーサーに引き渡す
	rapidxml::file<> moduleFileName = fileName.c_str();
	data_[key].stateVec_ = moduleFileName.vecData();

	data_[key].stateDoc_.parse<0>(data_[key].stateVec_.data());
	data_[key].stateNode_ = data_[key].stateDoc_.first_node("moduleList");
	if (data_[key].stateNode_ == nullptr)
	{
		return false;
	}
	return true;
}

rapidxml::xml_node<char>* StateMng::GetNode(std::string key)
{
	return data_[key].stateNode_;
}

StateMng& StateMng::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new StateMng();
	}
	return *s_Instance;
}

bool StateMng::Destroy(void)
{
	delete s_Instance;
	s_Instance = nullptr;
	return true;
}

StateMng::StateMng()
{
}

StateMng::~StateMng()
{
}
