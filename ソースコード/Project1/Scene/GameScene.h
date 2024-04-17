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

    //�Q�[���J�n�O�J�E���g
    bool Start(void);
    int startCount_;

    //�v���C���[
    std::unique_ptr<Player> player_;

    //�~�֘A
    std::vector<std::unique_ptr<Hoop>> shapeHoop_;
    Vector2D hoopPos_;    //�~�̍��W
};


