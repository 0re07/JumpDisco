#pragma once
#include <vector>
#include <array>
#include "BaseScene.h"

class Player;
class Hoop;

class GameScene :
    public BaseScene
{
public:
    GameScene(int screenSizeX, int screenSizeY);
    ~GameScene();
    bool Init(void) override;
    void DrawOwnScreen(void) override;

private:
    uniquScene Update(uniquScene ownScene, float deltaTime) override;

    //ゲーム開始前カウント
    bool Start(void);
    int startCount_;

    //プレイヤー
    std::unique_ptr<Player> player_;

    //円関連
    std::vector<std::unique_ptr<Hoop>> shapeHoop_;
    Vector2D hoopPos_;    //円の座標
};


