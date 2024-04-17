#include <DxLib.h>
#include "CrossOver.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

CrossOver::CrossOver(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY)
	:Transition(std::move(beforScene), std::move(afterScene), screenSizeX, screenSizeY)
{
	count_ = 0;
	//TRACE("CrossOver�̐���\n");
}

CrossOver::~CrossOver()
{
	//TRACE("CrossOver�̔j��\n");
}

bool CrossOver::UpdateTransition(void)
{
	DrawOwnScreen();

	if (++count_ >= 255)			//	�K��l�֓��B������I��
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen(void)
{
	//	�`��
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//	�C���X�^���X�����ۂɓ]��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
	afterScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
