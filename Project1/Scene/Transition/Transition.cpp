#include "Transition.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

Transition::Transition(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY)
	:BaseScene(screenSizeX, screenSizeY) 
{
	//	“n‚³‚ê‚½ˆø”‚ğ•Û‘¶
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
		return std::move(afterScene_);		//	Ÿ‚ÌƒV[ƒ“‚ğ•Ô‚·
	}
	return ownScene;		//	beforScene
}
