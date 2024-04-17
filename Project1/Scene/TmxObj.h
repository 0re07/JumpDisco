#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Manager/ImageMng.h"
#include "../common/Vector2D.h"

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"


using MapData = std::map<std::string, std::vector<int>>;
						//string�͑傫���̂œ��삪�x���Ȃ�
						//�ق�Ƃ�enum�Ƃ�������

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
	unsigned int layerSize_;	//���̃��C���[��ID
	Vector2D worldArea_;		//�}�b�v��ʂ̃T�C�Y
	Vector2D tileSize_;			//�^�C���̃T�C�Y
	//ColList colList_;			//�����蔻��

	MapData mapData_;
	std::string mapKey_;
};

