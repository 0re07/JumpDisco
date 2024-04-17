#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Manager/ImageMng.h"
#include "../common/Vector2D.h"

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"


using MapData = std::map<std::string, std::vector<int>>;
						//stringは大きいので動作が遅くなる
						//ほんとはenumとかがいい

class TmxObj
{
public:
	TmxObj();
	~TmxObj();

	bool LoadTMX(std::string fileName);
	bool LoadTSX(std::string fileName);
	bool SetMap(rapidxml::xml_node<>* node);

	//const ColList& GetColList(void);
	const MapData& GetMapData(void);	
	const Vector2D& GetWorldArea(void);	
	const Vector2D& GetTileSize(void);
	const std::string& GetMapKey(void);

	//Raycast raycast_;

private:
	//TSX
	rapidxml::xml_document<> tsxDoc_;

	//TMX
	rapidxml::xml_document<> tmxDoc_;
	unsigned int layerSize_;	//次のレイヤーのID
	Vector2D worldArea_;		//マップ画面のサイズ
	Vector2D tileSize_;			//タイルのサイズ
	//ColList colList_;			//当たり判定

	MapData mapData_;
	std::string mapKey_;
};

