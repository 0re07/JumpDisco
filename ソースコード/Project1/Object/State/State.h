#pragma once
#include <map>
#include <functional>
#include "../../common/Vector2D.h"
#include "../../Manager/AnimeMng.h"
#include "../../Input/Controller.h"
#include "../Player.h"
#include "GetAttr.h"

#include "../../rapidxml/rapidxml.hpp"
#include "../../rapidxml/rapidxml_utils.hpp"

//�A�j���[�V�����̐ݒ�
struct SetAnime {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		std::string state;
		GetAttr()(node, "state", state);

		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, state);
		return true;
	}
};

struct CheckNonState {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute("state");
			atr != nullptr;
			atr = atr->next_attribute())
		{
			if (dynamic_cast<Player*>(obj)->animStr_.state_ == atr->value())
			{
				return false;
			}
		}
		return true;
	}
};

//�L�����N�^�[�̏�ԃ`�F�b�N
struct CheckState{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute("state"); 
			atr != nullptr; 
			atr = atr->next_attribute())
		{
			if (dynamic_cast<Player*>(obj)->animStr_.state_ == atr->value())
			{
				return true;
			}
		}
		return false;
	}
};

//��������
struct SetFall {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//�A�j���[�V�����ݒ�
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Fall");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//����

		return true;
	}
};

//���W�����v����
struct SetJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//�A�j���[�V�����ݒ�
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Jump");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//�W�����v

		return true;
	}
};

//��W�����v����
struct SetBigJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//�A�j���[�V�����ݒ�
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "BigJump");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//�W�����v

		return true;
	}
};

//�������菈��
struct UpdateFall {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		//������
		double jump = 0.0;
		getAttr(node, "jump", jump);

		//�����ł���ő��
		double limit = 0.0;
		getAttr(node, "limit", limit);

		//����
		if (dynamic_cast<Player*>(obj)->jump_ < limit)
		{
			dynamic_cast<Player*>(obj)->jump_ += jump;
		}
		else
		{
			//�A�j���[�V�����ݒ�
			lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Idle");
		}
		
		return true;
	}
};

//���W�����v���菈��
struct UpdateJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		double jump = 0.0;
		getAttr(node, "jump", jump);

		//�W�����v
		dynamic_cast<Player*>(obj)->jump_ += jump;
		if (dynamic_cast<Player*>(obj)->jump_ <= 0.0)
		{
			dynamic_cast<Player*>(obj)->jump_ = 0.0;
			SetFall()(obj, node);
			return false;
		}

		return true;
	}
};

//��W�����v���菈��
struct UpdateBigJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		double jump = 0.0;
		getAttr(node, "jump", jump);

		//�W�����v
		dynamic_cast<Player*>(obj)->jump_ += jump;
		if (dynamic_cast<Player*>(obj)->jump_ <= 0.0)
		{
			dynamic_cast<Player*>(obj)->jump_ = 0.0;
			SetFall()(obj, node);
			return false;
		}

		return true;
	}
};

//�L�[�̓��̓`�F�b�N
struct CheckKey{
	bool operator()(Obj* player, rapidxml::xml_node<>* node)
	{

		std::map<std::string, InputID> inputTbl_ = {
			{"UP",InputID::UP},
			{"DOWN",InputID::DOWN},
			{"LEFT",InputID::LEFT},
			{"RIGHT",InputID::RIGHT},
			{"BTN1",InputID::BTN1},
			{"BTN2",InputID::BTN2},
			{"BTN3",InputID::BTN3}
		};

		std::string key;
		std::string state;
		GetAttr()(node, "key", key);
		GetAttr()(node, "state", state);

		const auto& cntData = player->controller_->GetCntData();
		//�͈̓`�F�b�N
		if (cntData.count(inputTbl_[key]))
		{
			//�L�[���������܂�Ă�����
			if (cntData.at(inputTbl_[key])[static_cast<int>(Trg::Now)])
			{
				return true;
			}
		}
		return false;
	}
};

//�L�����̌������`�F�b�N
struct CheckDir{
	bool operator()(Obj* player, rapidxml::xml_node<>* node)
	{
		std::string dirStr;
		GetAttr()(node, "dir", dirStr);
		if (dirStr == "LEFT")
		{
			if (player->dirLR_ == DIR_LR::LEFT)
			{
				return true;
			}
		}
		else if (dirStr == "RIGHT")
		{
			if (player->dirLR_ == DIR_LR::RIGHT)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
		return false;
	}
};

//�L�����̌������i�[
struct SetDir{
	bool operator()(Obj* player, rapidxml::xml_node<>* node)
	{
		std::string dirStr;
		GetAttr()(node,"dir", dirStr);
		if (dirStr == "LEFT")
		{
			player->dirLR_ = DIR_LR::LEFT;
		}
		else if (dirStr == "RIGHT")
		{
			player->dirLR_ = DIR_LR::RIGHT;
		}
		else
		{
			//�ُ�l�̏ꍇ�͂Ƃ肠�����E
			TRACE("�L�����̌����w��G���[\n");
			player->dirLR_ = DIR_LR::RIGHT;
		}

		return true;
	}
};

//�����Ă��邩�`�F�b�N
struct CheckNonMove {
	bool operator()(Obj* player, rapidxml::xml_node<>* node)
	{
		if (player->pos_ == player->posOld_)
		{
			return true;
		}
		return false;
	}
};

//�ړ�����
struct Move{
	bool operator()(Obj* player, rapidxml::xml_node<>* node)
	{
		Vector2D num;
		GetAttr()(node, "x", num.x);
		GetAttr()(node, "y", num.y);
		player->pos_ += num;

		return true;
	}
};

//���W���[���֘A
struct ModuleNode{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();
		//���W���[�����擾
		for (auto moduleNode = node->first_node();
			moduleNode != nullptr;
			moduleNode = moduleNode->next_sibling())
		{
			std::string moduleNodeName;
			getAttr(moduleNode, "name", moduleNodeName);
			//_TRACE_S(0xffffff, "moduleName:", moduleNodeName);

			if (module_.count(moduleNodeName))
			{
				if (!module_[moduleNodeName](obj, moduleNode))
				{
					//_TRACE_S(0x0000ff,"", "->false\n");
					
					//���̃��W���[�����`�F�b�N
					continue;
				}
				//_TRACE_S(0x00ff00, "",  "->true\n");
				
				//���̊K�w���`�F�b�N
				if (!(*this)(obj, moduleNode))
				{
					return false;				//��̊K�w�֖߂��Ă���
				}
			}
			else
			{
				//_TRACE_S(0xff0000, "���m�̃��W���[��", moduleNodeName);
			}
		}
		return true;
	}

	//�����o
	std::map<std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node)>> module_ = {
		{"CheckKey",CheckKey()},
		{"CheckDir",CheckDir()},
		{"SetDir",SetDir()},
		{"CheckNonMove",CheckNonMove()},
		{"Move",Move()},
		{"SetAnime",SetAnime()},
		{"CheckNonState",CheckNonState()},
		{"CheckState",CheckState()},
		{"SetFall",SetFall()},
		{"UpdateFall",UpdateFall()},
		{"SetJump", SetJump()},
		{"UpdateJump",UpdateJump()},
		{"SetBigJump", SetJump()},
		{"UpdateBigJump",UpdateJump()}
	};
};
