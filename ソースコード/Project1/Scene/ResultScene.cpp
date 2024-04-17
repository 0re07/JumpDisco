#include "../common/Flame.h"
#include "../Input/Controller.h"
#include "../Input/InputID.h"
#include "../Manager/ImageMng.h"
#include "../Object/Player.h"
#include "Transition/CrossOver.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

ResultScene::ResultScene(int screenSizeX, int screenSizeY) 
	:BaseScene(screenSizeX, screenSizeY)
{
	player_ = std::make_unique<Player>(screenSizeX, screenSizeY);

	Init();
	DrawOwnScreen();
}

ResultScene::~ResultScene()
{
}

bool ResultScene::Init(void)
{
	//‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	lpImageMng.GetID("Data/Image/Result/result_bg.png", "BG");
	lpImageMng.GetID("Data/Image/Result/result_field.png", "Field");
	lpImageMng.GetID("Data/Image/Result/blacklayer.png", "Layer");
	lpImageMng.GetID("Data/Image/Result/score.png", "Score");

	return true;
}

void ResultScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//‰æ‘œ‚Ì•`‰æ
	DrawGraph(0, 0, lpImageMng.GetID("BG")[0], true);
	DrawGraph(0, 0, lpImageMng.GetID("Field")[0], true);
	//DrawGraph(0, 0, lpImageMng.GetID("Layer")[0], true);
	DrawGraph(0, 0, lpImageMng.GetID("Score")[0], true);
	
	auto h = player_->score_;
	DrawFormatString(100, 100, 0x000000, "%d", h);

	DrawFormatString(200, 480 / 2 - 100, 0x000000, "PUSH SPACE KEY");

}

uniquScene ResultScene::Update(uniquScene ownScene, float deltaTime)
{
	controller_->Update(*ownScene.get());


	DrawOwnScreen();

	//ƒV[ƒ“‚ÌØ‚è‘Ö‚¦
	auto contData = controller_->GetInputData();
	if (contData[NowFlame][static_cast<int>(InputID::Btn3)] &&
		!contData[OldFlame][static_cast<int>(InputID::Btn3)])
	{
		return std::make_unique<CrossOver>(std::move(ownScene), 
			std::make_unique<TitleScene>(screenSize_.x, screenSize_.y), 
			screenSize_.x, screenSize_.y);
	}
	return std::move(ownScene);

}
