#include <DxLib.h>
#include "../common/Flame.h"
#include "../Manager/ImageMng.h"
#include "../Manager/SoundMng.h"
#include "../Manager/SoundApp.h"
#include "../Input/Controller.h"
#include "../Input/InputID.h"
#include "Transition/CrossOver.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include "TitleScene.h"

TitleScene::TitleScene(int screenSizeX, int screenSizeY)
	:BaseScene(screenSizeX, screenSizeY)
{
	Init();
	lpSoundApp.PlayLoopSound("Title", true);
	DrawOwnScreen();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	//�摜�̓ǂݍ���
	if (GetJoypadNum())		//�p�b�h���ڑ�����Ă�����
	{
		lpImageMng.GetID("Data/Image/Title/InputPad.png", "InputPad");
		lpImageMng.GetID("Data/Image/Title/Abuttun.png", "Abuttun");
		lpImageMng.GetID("Data/Image/Title/Abuttun_push.png", "AbuttunPush");
	}
	else
	{
		lpImageMng.GetID("Data/Image/Title/InputKey_Buttun.png", "InputKey");
		lpImageMng.GetID("Data/Image/Title/SpKey.png", "SpaceKey");
		lpImageMng.GetID("Data/Image/Title/SpKey_push.png", "SpaceKeyPush");
	}

	lpImageMng.GetID("Data/Image/Title/Title.jpg", "TitleBG");

	//���y�̓ǂݍ���
	lpSoundMng.GetSoundID("Data/Sound/Music/Sweet 70s.wav", "Title");

	return true;
}

void TitleScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//�w�i�̕\��
	DrawGraph(0, 0, lpImageMng.GetID("TitleBG")[0], true);
	if (GetJoypadNum())		//�p�b�h���ڑ�����Ă�����
	{
		if ((count_ / 30) % 4 != 0)
		{
			//�����`��
			DrawGraph(0, 0, lpImageMng.GetID("InputPad")[0], true);

			//�{�^���`��
			if ((count_ / 30) % 2 != 0)
			{
				DrawGraph(0, 0, lpImageMng.GetID("Abuttun")[0], true);
			}
			else
			{
				DrawGraph(0, 0, lpImageMng.GetID("AbuttunPush")[0], true);
			}
		}
	}
	else
	{
		if ((count_ / 30) % 4 != 0)
		{
			//�����`��
			DrawGraph(0, 0, lpImageMng.GetID("InputKey")[0], true);

			//�L�[�`��
			if ((count_ / 30) % 2 != 0)
			{
				DrawGraph(0, 0, lpImageMng.GetID("SpaceKey")[0], true);
			}
			else
			{
				DrawGraph(0, 0, lpImageMng.GetID("SpaceKeyPush")[0], true);
			}
		}

	}

}

uniquScene TitleScene::Update(uniquScene ownScene, float deltaTime)
{
	controller_->Update(*ownScene.get());

	count_++;

	DrawOwnScreen();

	//�V�[���̐؂�ւ�
	auto contData = controller_->GetInputData();

	if (contData[NowFlame][static_cast<int>(InputID::Btn2)] &&
		!contData[OldFlame][static_cast<int>(InputID::Btn2)])
	{
		//���y�̍Đ����~�߂�
		lpSoundApp.StopSound("Title");

		return std::make_unique<CrossOver>(std::move(ownScene), 
			std::make_unique<GameScene>(screenSize_.x, screenSize_.y),
			screenSize_.x, screenSize_.y);
	}
	return std::move(ownScene);

}
