#pragma once
#include "../BaseScene.h"

class Transition:
	public BaseScene
{
public:
	Transition(uniquScene beforScene, uniquScene afterScene, int screenSizeX, int screenSizeY);
	~Transition();

private:
	uniquScene Update(uniquScene ownScene, float deltaTime) override;
	virtual bool UpdateTransition(void) = 0;

protected:
	uniquScene beforScene_;
	uniquScene afterScene_;

	

};

