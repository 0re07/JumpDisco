#pragma once
#include <memory>
#include "../common/Vector2D.h"

class BaseScene;
class Controller;

class Player
{
public:
    //状態
    enum class STATE
    {
        NON,
        IDLE,
        RUN,
        JUMP,
        FALL,
        HURT,
        DEATH
    };

    Player();
    Player(int screenSizeX, int screenSizeY);
    ~Player();

    bool Init(void);
    void Update(void);
    void Move(BaseScene& scene);
    void Draw(void);

    //当たり判定
    bool IsHit(Circle hoop);

    //色を変更
    void SetColor(unsigned int color);

    //死んでいるか
    bool IsDeath(void)const;

    //
    bool GetHit(void);
    bool hit_;          //当たり判定
    int score_;

private:
    void UpdateJump(void);
    void UpdateFall(void);
    void UpdateHurt(void);
    void UpdateDeath(void);

    //状態遷移
    void ChengeState(STATE state);

    //状態確認
    bool CheckState(STATE state);

    //
    bool CheckNonMove(void);

    bool IsEndCount(void);

    Vector2D screenSize_;                       //画面サイズ
    std::unique_ptr<Controller> controller_;    //コントローラーの管理

    //プレイヤー関連
    Circle player_;  
    Vector2D posOld_;
    unsigned int color_;//プレイヤーの色
    int life_;          //ライフ4
    int jump;
    STATE state_;       //状態
    bool isDeath_;
    int playerCount_;

    int idleImg_[4];
    int runImg_[6];
    int jumpImg_[4];
    int fallImg_[4];
    int deathImg_[6];
    
    float mutekicount_;   //後で一括管理

};

