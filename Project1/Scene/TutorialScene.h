#pragma once
#include "BaseScene.h"

class TutorialScene :
    public BaseScene
{
public:
	TutorialScene(int screenSizeX, int screenSizeY);
	~TutorialScene();
	void DrawOwnScreen(void) override;

private:
	uniquScene Update(uniquScene ownScene, float deltaTime) override;
};

