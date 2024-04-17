#pragma once
#include <string>

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

//関数オブジェクト
class GetAttr 
{
public:
		//どのオペレターをオーバーライドするか、引数
	bool operator()(rapidxml::xml_node<>* node, std::string atrStr, int& num)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atr = node->first_attribute(atrStr.c_str());
		if (atr == nullptr)
		{
			TRACE("アトリビュートの取得エラー：%s\n", atrStr.c_str());
			return false;
		}
		num = atoi(atr->value());
		return true;
	}

	//unsigned int 
	bool operator()(rapidxml::xml_node<>* node, std::string atrStr, unsigned int& num)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atr = node->first_attribute(atrStr.c_str());
		if (atr == nullptr)
		{
			TRACE("アトリビュートの取得エラー：%s\n", atrStr.c_str());
			return false;
		}
		num = atoi(atr->value());
		return true;
	}

	//string
	bool operator()(rapidxml::xml_node<>* node, std::string atrStr, std::string& str)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atr = node->first_attribute(atrStr.c_str());
		if (atr == nullptr)
		{
			TRACE("アトリビュートの取得エラー：%s\n", atrStr.c_str());
			return false;
		}
		str = atr->value();
		return true;
	}

	//double
	bool operator()(rapidxml::xml_node<>* node, std::string atrStr, double& num)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atr = node->first_attribute(atrStr.c_str());
		if (atr == nullptr)
		{
			TRACE("アトリビュートの取得エラー：%s\n", atrStr.c_str());
			return false;
		}
		num = atof(atr->value());
		return true;
	}

};
