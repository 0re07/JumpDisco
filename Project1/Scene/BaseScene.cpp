#include "../Input/Keybord.h"
#include "../Input/GamePad.h"
#include "TitleScene.h"
#include "GameScene.h"

BaseScene::BaseScene(int screenSizeX, int screenSizeY) :screenSize_(screenSizeX, screenSizeY)
{
	//	��ʂ����
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);

	Init();
}

BaseScene::~BaseScene()
{
}

bool BaseScene::Init(void)
{
	if (GetJoypadNum())		//�p�b�h���ڑ�����Ă�����
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
