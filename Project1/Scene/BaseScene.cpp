#include "../Input/Keybord.h"
#include "../Input/GamePad.h"
#include "TitleScene.h"
#include "GameScene.h"

BaseScene::BaseScene(int screenSizeX, int screenSizeY) :screenSize_(screenSizeX, screenSizeY)
{
	//	画面を作る
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);

	Init();
}

BaseScene::~BaseScene()
{
}

bool BaseScene::Init(void)
{
	if (GetJoypadNum())		//パッドが接続されていた時
	{
		controller_ = std::make_unique<GamePad>();
	}
	else
	{
		controller_ = std::make_unique<Keybord>();
	}

	return true;
}

void BaseScene::Draw(void)
{
	DrawGraph(drawOffset_.x, drawOffset_.y, screenID_, true);
}
