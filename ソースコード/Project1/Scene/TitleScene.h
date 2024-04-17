#pragma once
#include "BaseScene.h"

class TitleScene :
    public BaseScene
{
public:
    TitleScene(int screenSizeX, int screenSizeY);
    ~TitleScene();
    bool Init(void) override;
    void DrawOwnScreen(void) override;

private:
    uniquScene Update(uniquScene ownScene, float deltaTime) override;

    int count_;   

};

