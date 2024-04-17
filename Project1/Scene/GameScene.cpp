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

	//���y�̍Đ�
	PlaySoundMem(gameMusic_, DX_PLAYTYPE_BACK, true);

}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	//�摜�̓ǂݍ���
	lpImageMng.GetID("Data/Image/Stage/stage.png", "GameBG");
	lpImageMng.GetID("Data/Image/Stage/stage_buill.png", "GameBG_TOP");

	//���y�̓ǂݍ���
	gameMusic_ = LoadSoundMem("Data/Sound/Music/Retro Noir.wav");

	player_->Init();

	shapeHoop_.reserve(5);

	//������������
	srand((unsigned int)time(NULL));

	return true;
}

void GameScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//�w�i�̕`��
	DrawGraph(0, 0, lpImageMng.GetID("GameBG")[0], true);

	//�E�F�[�u�̕`��
	for (auto& hoop : shapeHoop_)
	{
		hoop->Draw();
	}

	//�v���C���[�̕`��
	player_->Draw();

	DrawGraph(0, 0, lpImageMng.GetID("GameBG_TOP")[0], true);

}

uniquScene GameScene::Update(uniquScene ownScene, float deltaTime)
{
	if (!Start())
	{
		controller_->Update(*ownScene.get());

		//�~�̐���
		if (shapeHoop_.size() + 1 <= shapeHoop_.capacity())
		{
			//�v�f����ύX
			shapeHoop_.resize(shapeHoop_.size() + 1);

			//���W���w�肵�Đ���(Hoop���łł���悤�ɂ���)
			hoopPos_ = { rand() % screenSize_.x + 50, rand() % screenSize_.y + 50 };
			shapeHoop_[shapeHoop_.size() - 1] = std::make_unique<Hoop>(hoopPos_);
		}

		//�v���C���[
		player_->Update();
		player_->Move(*this);

		//�~�̍X�V
		for (auto& hoop : shapeHoop_)
		{
			hoop->Update();

			//�v���C���[�Ƃ̓����蔻��
			if (!player_->IsHit(hoop->GetInHoop()) &&
				player_->IsHit(hoop->GetOutHoop()))
			{
				TRACE("��������\n");
			}
		}
	}

	//�`��
	DrawOwnScreen();

	//�V�[���̐؂�ւ�
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