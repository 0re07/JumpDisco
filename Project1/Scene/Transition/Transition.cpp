#include "Transition.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

Transition::Transition(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY)
	:BaseScene(screenSizeX, screenSizeY) 
{
	//	渡された引数を保存
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
}

Transition::~Transition()
{

}

uniquScene Transition::Update(uniquScene ownScene, float deltaTime)
{
	DrawOwnScreen();
	if (UpdateTransition())				
	{
		return std::move(afterScene_);		//	次のシーンを返す
	}
	return ownScene;		//	beforScene
}
