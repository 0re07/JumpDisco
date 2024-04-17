#include "../common/Flame.h"
#include "../Input/Controller.h"
#include "../Input/InputID.h"
#include "Transition/CrossOver.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene(int screenSizeX, int screenSizeY)
	:BaseScene(screenSizeX, screenSizeY)
{
	Init();
	DrawOwnScreen();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::DrawOwnScreen(void)
{
	//���y�̍Đ�
	//PlaySoundMem(gameMusic_, DX_PLAYTYPE_BACK, true);
}

uniquScene TutorialScene::Update(uniquScene ownScene, float deltaTime)
{
	controller_->Update(*ownScene.get());

	DrawString(0, 0, "TutorialScene��Update()�Ăяo��", 0xffffff);

	//�V�[���̐؂�ւ�
	//if (deltaTime >= 21.0f)	
	//{
	//	return  std::make_unique<GameScene>(screenSize_.x, screenSize_.y);
	//}
	
	//�{�^�����������ꂽ��X�L�b�v����
	auto contData = controller_->GetInputData();
	if (contData[NowFlame][static_cast<int>(InputID::Btn1)] &&
		!contData[OldFlame][static_cast<int>(InputID::Btn1)])
	{
		return std::make_unique<CrossOver>(std::move(ownScene),
			std::make_unique<GameScene>(screenSize_.x, screenSize_.y),
			screenSize_.x, screenSize_.y);
	}
	return std::move(ownScene);
}
