#include<DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "SceneMng.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

constexpr int ScreenSizeX = 640;
constexpr int ScreenSizeY = 480;

Vector2D SceneMng::GetScreenSize(void) const
{
	return { ScreenSizeX,ScreenSizeY };
}

SceneMng::SceneMng()
{
	initFlag_ = SysInit();

	deltaTime_ = 10.0f / 60.0f;

}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	if (!initFlag_)
	{
		return;
	}

	scene_ = std::make_unique<TitleScene>(ScreenSizeX, ScreenSizeY);
	//scene_ = std::make_unique<ResultScene>(ScreenSizeX, ScreenSizeY);		//�f�o�b�N�p

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Update())
	{
		// �f���^�^�C��
		auto nowTime = std::chrono::system_clock::now();
		deltaTime_ = static_cast<float>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
		preTime_ = nowTime;

		Draw();
	}

}

bool SceneMng::Update(void)
{
	_dbgStartDraw();

	if (!scene_)
	{
		TRACE("�yERROR�zscene_�̒��g����\n");
		return false;
	}
	scene_ = scene_->Update(std::move(scene_),deltaTime_);

	return true;
}

void SceneMng::Draw(void)
{
	//	�`��
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	scene_->Draw();

	ScreenFlip();
}

bool SceneMng::SysInit(void)
{
	//�V�X�e������
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == 1)
	{
		//���������s
		return false;
	}

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	_dbgSetup(ScreenSizeX, ScreenSizeY, 256);
	return true;
}
#include "SceneMng.h"
