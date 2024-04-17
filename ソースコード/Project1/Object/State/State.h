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

//アニメーションの設定
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

//キャラクターの状態チェック
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

//落下処理
struct SetFall {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//アニメーション設定
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Fall");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//落下

		return true;
	}
};

//小ジャンプ処理
struct SetJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//アニメーション設定
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Jump");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//ジャンプ

		return true;
	}
};

//大ジャンプ処理
struct SetBigJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		//アニメーション設定
		lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "BigJump");

		double jump = 0.0;
		GetAttr()(node, "jump", jump);

		dynamic_cast<Player*>(obj)->jump_ = jump;		//ジャンプ

		return true;
	}
};

//落下判定処理
struct UpdateFall {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		//落下量
		double jump = 0.0;
		getAttr(node, "jump", jump);

		//落下できる最大量
		double limit = 0.0;
		getAttr(node, "limit", limit);

		//落下
		if (dynamic_cast<Player*>(obj)->jump_ < limit)
		{
			dynamic_cast<Player*>(obj)->jump_ += jump;
		}
		else
		{
			//アニメーション設定
			lpAnimeMng.SetAnime(dynamic_cast<Player*>(obj)->animStr_, "Idle");
		}
		
		return true;
	}
};

//小ジャンプ判定処理
struct UpdateJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		double jump = 0.0;
		getAttr(node, "jump", jump);

		//ジャンプ
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

//大ジャンプ判定処理
struct UpdateBigJump {
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();

		double jump = 0.0;
		getAttr(node, "jump", jump);

		//ジャンプ
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

//キーの入力チェック
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
		//範囲チェック
		if (cntData.count(inputTbl_[key]))
		{
			//キーが押し込まれていたら
			if (cntData.at(inputTbl_[key])[static_cast<int>(Trg::Now)])
			{
				return true;
			}
		}
		return false;
	}
};

//キャラの向きをチェック
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

//キャラの向きを格納
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
			//異常値の場合はとりあえず右
			TRACE("キャラの向き指定エラー\n");
			player->dirLR_ = DIR_LR::RIGHT;
		}

		return true;
	}
};

//動いているかチェック
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

//移動処理
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

//モジュール関連
struct ModuleNode{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		auto getAttr = GetAttr();
		//モジュールを取得
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
					
					//次のモジュールをチェック
					continue;
				}
				//_TRACE_S(0x00ff00, "",  "->true\n");
				
				//次の階層をチェック
				if (!(*this)(obj, moduleNode))
				{
					return false;				//上の階層へ戻っていく
				}
			}
			else
			{
				//_TRACE_S(0xff0000, "未知のモジュール", moduleNodeName);
			}
		}
		return true;
	}

	//メンバ
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
