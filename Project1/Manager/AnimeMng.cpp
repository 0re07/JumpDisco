#include <sstream>
#include "../common/Vector2D.h"
#include "ImageMng.h"
#include "GetAttr.h"
#include "AnimeMng.h"

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

std::string AnimeMng::LoadAnime(std::string fileName)
{
	//�t�@�C�����J��
	rapidxml::xml_document <> actDoc;

	rapidxml::file<> xmlFile = fileName.c_str();
	auto getAtr = GetAttr();
	//xml�t�@�C���̒��g��xml�̃p�[�T�[�ɓn��
	actDoc.parse<0>(xmlFile.data());
	std::string CharName;

	auto actionList = actDoc.first_node("actionList");
	if (actionList == nullptr)
	{
		return std::string();
	}

	std::string charName;
	getAtr(actionList, "name", charName);

	//action���s����܂�
	for (auto animAct = actionList->first_node("action");
		animAct != nullptr;
		animAct = animAct->next_sibling())
	{
		if (animAct == nullptr)
		{
			continue;
		}

		std::string keyName;
		std::string source;
		Vector2D divSize;
		Vector2D divCnt;

		getAtr(animAct, "name", keyName);
		getAtr(animAct, "source", source);
		getAtr(animAct, "divSizeX", divSize.x);
		getAtr(animAct, "divSizeY", divSize.y);
		getAtr(animAct, "divCntX", divCnt.x);
		getAtr(animAct, "divCntY", divCnt.y);

		lpImageMng.GetID(source, charName + keyName, divSize, divCnt);		//�f�[�^�̊i�[

		//�e�[�u���f�[�^�̏d�����Ȃ���
		auto result = animeTbl_.try_emplace(charName + keyName);
		if (!result.second)
		{
			return charName;
		}

		auto anime = animAct->first_node("anime");
		if (anime == nullptr)
		{
			return std::string();
		}

		int loop;
		getAtr(anime, "loop", loop);
		animeTbl_[charName + keyName].first = loop;

		//csv
		auto animeData = anime->first_node();
		std::stringstream dataStream;
		dataStream << animeData->value();
		std::string numStr;
		while (getline(dataStream, numStr, ','))
		{
			auto id = atoi(numStr.c_str());
			getline(dataStream, numStr, ',');
			auto frame = atoi(numStr.c_str());
			int csv[4];
			for (int j = 0; j < 4; j++)
			{
				getline(dataStream, numStr, ',');
				csv[j] = atoi(numStr.c_str());
			}
			//�f�[�^���Ō������i�[
			animeTbl_[charName + keyName].second.
				emplace_back(AnimData{ id,frame,csv[0],csv[1] ,csv[2],csv[3] });
		}
	}
	return charName;
}

bool AnimeMng::UpdateAnime(AnimeStr& animeCache)
{
	//�A�j���[�V����
	if (animeCache.animCount_++ >= (*animeCache.animID_)[InvLimit])		//�w�肵���t���[�������傫�����								
	{
		animeCache.animCount_ = 0;
		++animeCache.animID_;
		//�A�j���[�V�����̍Đ����I����Ă�����
		if (animeCache.animID_ == animeTbl_[animeCache.objID_ + animeCache.state_].second.end())
		{
			//�A�j���[�V�����̌��Đ��񐔂��K��̍Đ��񐔂�菭�Ȃ�������
			if (++animeCache.animPlayCount_ < animeTbl_[animeCache.objID_ + animeCache.state_].first || 
				animeTbl_[animeCache.objID_ + animeCache.state_].first == -1)
			{
				TRACE("%d\n", animeCache.animPlayCount_);
				animeCache.animID_ = animeTbl_[animeCache.objID_ + animeCache.state_].second.begin();
			}
			else
			{
				animeCache.animID_ = --animeTbl_[animeCache.objID_ + animeCache.state_].second.end();	//�I����-�P���ă��[�v��������
				animeCache.endFlag_ = true;
			}
		}
	}

	return false;
}

void AnimeMng::SetAnime(AnimeStr& animeData, std::string state)
{
	//���݂̃A�j���[�V�����̏�
	if (state == animeData.state_)
	{
		return;
	}
	
	//�����o������
	animeData = AnimeStr{
		animeData.objID_ + state,
		animeData.objID_,
		state,
		animeTbl_[animeData.objID_ + state].second.begin(),
		0,
		0,
		false
	};

 }

AnimeMng::AnimeMng()
{
}

AnimeMng::~AnimeMng()
{
}
