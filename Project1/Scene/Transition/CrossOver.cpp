#include <DxLib.h>
#include "CrossOver.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

CrossOver::CrossOver(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY)
	:Transition(std::move(beforScene), std::move(afterScene), screenSizeX, screenSizeY)
{
	count_ = 0;
	//TRACE("CrossOver‚Ì¶¬\n");
}

CrossOver::~CrossOver()
{
	//TRACE("CrossOver‚Ì”jŠü\n");
}

bool CrossOver::UpdateTransition(void)
{
	DrawOwnScreen();

	if (++count_ >= 255)			//	‹K’è’l‚Ö“ž’B‚µ‚½‚çI—¹
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen(void)
{
	//	•`‰æ
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//	ƒCƒ“ƒXƒ^ƒ“ƒX‚µ‚½Û‚É“]ŽÊ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
	afterScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
