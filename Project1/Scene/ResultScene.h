#pragma once
#include "BaseScene.h"

class Player;

class ResultScene :
    public BaseScene
{
public:
    ResultScene(int screenSizeX, int screenSizeY);
    ~ResultScene();
    bool Init(void)override;
    void DrawOwnScreen(void) override;

private:
    uniquScene Update(uniquScene ownScene, float deltaTime) override;

    std::unique_ptr<Player> player_;

};

