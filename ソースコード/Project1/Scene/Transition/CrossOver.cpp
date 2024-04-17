#include <DxLib.h>
#include "CrossOver.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

CrossOver::CrossOver(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY)
	:Transition(std::move(beforScene), std::move(afterScene), screenSizeX, screenSizeY)
{
	count_ = 0;
	//TRACE("CrossOverの生成\n");
}

CrossOver::~CrossOver()
{
	//TRACE("CrossOverの破棄\n");
}

bool CrossOver::UpdateTransition(void)
{
	DrawOwnScreen();

	if (++count_ >= 255)			//	規定値へ到達したら終了
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen(void)
{
	//	描画
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//	インスタンスした際に転写
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
	afterScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
