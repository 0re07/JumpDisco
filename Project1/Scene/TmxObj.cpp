#include <sstream>
#include "../Object/State/GetAttr.h"
#include "TmxObj.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

TmxObj::TmxObj()
{
}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTMX(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();		//	ファイルを開く
	tmxDoc_.parse<0>(xmlFile.data());					//	中身にアクセスできるようになる

	//解析
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");
	if (mapNode == nullptr)
	{
		return false;
	}
	rapidxml::xml_node<>* tileset = mapNode->first_node("tileset");
	if (tileset == nullptr)
	{
		return false;
	}
	rapidxml::xml_attribute<>* tsxSource = tileset->first_attribute("source");
	if (tsxSource == nullptr)
	{
		return false;
	}

	auto getAtr = GetAttr();				//関数オブジェクトを使う
	if (!getAtr(mapNode,"nextlayerid", layerSize_))
	{
		return false;
	}
	layerSize_--;		//nextlayeridの値はレイヤー総数からすると＋1されているため減算

	if (!getAtr(mapNode, "width", worldArea_.x))
	{
		return false;
	}
	if (!getAtr(mapNode, "height", worldArea_.y))
	{
		return false;
	}
	if (!getAtr(mapNode, "tilewidth", tileSize_.x))
	{
		return false;
	}
	if (!getAtr(mapNode, "tileheight", tileSize_.y))
	{
		return false;
	}

	auto filePass = fileName.substr(0, fileName.find_last_of("/") + 1);
	LoadTSX(filePass + tsxSource->value());

	if (SetMap(mapNode))
	{
		return false;
	}

	return SetMap(mapNode);
}

bool TmxObj::LoadTSX(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();		//	ファイルを開く
	tsxDoc_.parse<0>(xmlFile.data());					//	中身にアクセスできるようになる

	//解析
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");
	if (tileset == nullptr)
	{
		return false;
	}
	rapidxml::xml_attribute<>* version = tileset->first_attribute("version");
	rapidxml::xml_attribute<>* tiledversion = tileset->first_attribute("tiledversion");
	//TRACE("TSX vesion : %s\n", version->value());
	//TRACE("Tiled vesion : %s\n", tiledversion->value());

	int tilewidth;				//タイルの幅
	int tileheight;				//タイルの高さ
	int tilecount;				//タイルの数
	int columns;

	auto getAtr = GetAttr();	//関数オブジェクトを使う
	if (!getAtr(tileset,"tilewidth", tilewidth))
	{
		return false;
	}
	if (!getAtr(tileset, "tileheight", tileheight))
	{
		return false;
	}
	if (!getAtr(tileset, "tilecount", tilecount))
	{
		return false;
	}
	if (!getAtr(tileset, "columns", columns))
	{
		return false;
	}

	rapidxml::xml_node<>* imageNode = tileset->first_node("image");
	if (imageNode == nullptr)
	{
		return false;
	}
	rapidxml::xml_attribute<>* source = imageNode->first_attribute("source");
	if (source == nullptr)
	{
		return false;
	}

	std::string sourcePass = source->value();
	mapKey_ = "mapChip";
	lpImageMng.GetID("../Data/tmx" + sourcePass.substr(1), mapKey_, { tilewidth,tileheight }, { columns, tilecount / columns });

	return true;
}

bool TmxObj::SetMap(rapidxml::xml_node<>* node)
{
	if (node == nullptr)
	{
		return false;
	}

	auto tileset = node->first_node("tileset");
	if (tileset == nullptr)
	{
		return false;
	}

	auto getAtr = GetAttr();
	int firstgid;
	getAtr(tileset, "firstgid", firstgid);

	//レイヤーがなくなるまで
	for (auto layer = node->first_node("layer");
		layer != nullptr;
		layer = layer->next_sibling())
	{
		if (layer == nullptr)
		{
			return false;
		}

		std::string layerName;
		getAtr(layer, "name", layerName);

		//レイヤーがコリジョン(当たり判定)の場合はもう一度
		if (layerName == "Col")
		{
			continue;
		}

		//レイヤーの幅と高さを取る
		Vector2D layerSize;
		getAtr(layer, "width", layerSize.x);
		getAtr(layer, "height", layerSize.y);
		//	Vector2Dなので初期値0
		//	0が入ると後々falseになるためnullチェックしてない

		if (worldArea_ != layerSize)
		{
			return false;
		}

		//csvつくる
		auto layerDeta = mapData_.try_emplace(layerName);			//格納先
		if (layerDeta.second)
		{
			layerDeta.first->second.resize(worldArea_.x * worldArea_.y);
		}

		auto data = layer->first_node("data");
		if (data == nullptr)
		{
			return false;
		}
		auto csvData = data->first_node();

		//文字列をばらしてデータからマップの詳しい情報を格納する
		std::stringstream dataStream;
		dataStream << csvData->value();					//データを流し込む
		for (auto& vecData : layerDeta.first->second)
		{
			std::string numStr;
			getline(dataStream, numStr, ',');
			vecData = atoi(numStr.c_str()) - firstgid;	//画像のずれを修正
		}
	}

	//当たり判定の取得
	//for (auto colNode = node->first_node("objectgroup");
	//	colNode != nullptr;
	//	colNode = colNode->next_sibling())
	//{
	//	std::string grpName;
	//	getAtr(colNode, "name", grpName);
	//	if (grpName != "Col")
	//	{
	//		continue;
	//	}

	//	for (auto objNode = colNode->first_node("object");
	//		objNode != nullptr;
	//		objNode = objNode->next_sibling())
	//	{
	//		double x, y, w, h;
	//		getAtr(objNode, "x", x);
	//		getAtr(objNode, "y", y);
	//		getAtr(objNode, "width", w);
	//		getAtr(objNode, "height", h);
	//		colList_.push_back(
	//			Collision
	//			{
	//				Vector2DDouble{x,y},
	//				Vector2DDouble{w,h}
	//			}
	//		);
	//	}
	//}

	return true;
}

//const ColList& TmxObj::GetColList(void)
//{
//	return colList_;
//}

const MapData& TmxObj::GetMapData(void)
{
	return mapData_;
}

const Vector2D& TmxObj::GetWorldArea(void)
{
	return worldArea_;
}

const Vector2D& TmxObj::GetTileSize(void)
{
	return tileSize_;
}

const std::string& TmxObj::GetMapKey(void)
{
	return mapKey_;
}

