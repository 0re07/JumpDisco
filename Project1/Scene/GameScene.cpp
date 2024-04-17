#include <time.h>
#include <DxLib.h>
#include "../common/Flame.h"
#include "../Manager/ImageMng.h"
#include "../Input/Controller.h"
#include "../Input/InputID.h"
#include "../Object/Hoop.h"
#include "../Object/Player.h"
#include "Transition/CrossOver.h"
#include "ResultScene.h"
#include "GameScene.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

const int WAIT_TIME = 120;

GameScene::GameScene(int screenSizeX, int screenSizeY) 
	:BaseScene(screenSizeX, screenSizeY)
{
	player_ = std::make_unique<Player>(screenSizeX, screenSizeY);
	Init();
	DrawOwnScreen();

	//音楽の再生
	PlaySoundMem(gameMusic_, DX_PLAYTYPE_BACK, true);

}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	//画像の読み込み
	lpImageMng.GetID("Data/Image/Stage/stage.png", "GameBG");
	lpImageMng.GetID("Data/Image/Stage/stage_buill.png", "GameBG_TOP");

	//音楽の読み込み
	gameMusic_ = LoadSoundMem("Data/Sound/Music/Retro Noir.wav");

	player_->Init();

	shapeHoop_.reserve(5);

	//乱数を初期化
	srand((unsigned int)time(NULL));

	return true;
}

void GameScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//背景の描画
	DrawGraph(0, 0, lpImageMng.GetID("GameBG")[0], true);

	//ウェーブの描画
	for (auto& hoop : shapeHoop_)
	{
		hoop->Draw();
	}

	//プレイヤーの描画
	player_->Draw();

	DrawGraph(0, 0, lpImageMng.GetID("GameBG_TOP")[0], true);

}

uniquScene GameScene::Update(uniquScene ownScene, float deltaTime)
{
	if (!Start())
	{
		controller_->Update(*ownScene.get());

		//円の生成
		if (shapeHoop_.size() + 1 <= shapeHoop_.capacity())
		{
			//要素数を変更
			shapeHoop_.resize(shapeHoop_.size() + 1);

			//座標を指定して生成(Hoop内でできるようにする)
			hoopPos_ = { rand() % screenSize_.x + 50, rand() % screenSize_.y + 50 };
			shapeHoop_[shapeHoop_.size() - 1] = std::make_unique<Hoop>(hoopPos_);
		}

		//プレイヤー
		player_->Update();
		player_->Move(*this);

		//円の更新
		for (auto& hoop : shapeHoop_)
		{
			hoop->Update();

			//プレイヤーとの当たり判定
			if (!player_->IsHit(hoop->GetInHoop()) &&
				player_->IsHit(hoop->GetOutHoop()))
			{
				TRACE("当たった\n");
			}
		}
	}

	//描画
	DrawOwnScreen();

	//シーンの切り替え
	//if(player_->IsDeath())
	//{
	//	return  std::make_unique<ResultScene>(screenSize_.x, screenSize_.y);
	//}
	return std::move(ownScene);

}

bool GameScene::Start(void)
{
	if (startCount_ >= WAIT_TIME)
	{
		return false;
	}
	startCount_++;

	return true;
}