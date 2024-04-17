#pragma once
#include <memory>
#include "../common/Vector2D.h"

class BaseScene;
class Controller;

class Player
{
public:
    //���
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

    //�����蔻��
    bool IsHit(Circle hoop);

    //�F��ύX
    void SetColor(unsigned int color);

    //����ł��邩
    bool IsDeath(void)const;

    //
    bool GetHit(void);
    bool hit_;          //�����蔻��
    int score_;

private:
    void UpdateJump(void);
    void UpdateFall(void);
    void UpdateHurt(void);
    void UpdateDeath(void);

    //��ԑJ��
    void ChengeState(STATE state);

    //��Ԋm�F
    bool CheckState(STATE state);

    //
    bool CheckNonMove(void);

    bool IsEndCount(void);

    Vector2D screenSize_;                       //��ʃT�C�Y
    std::unique_ptr<Controller> controller_;    //�R���g���[���[�̊Ǘ�

    //�v���C���[�֘A
    Circle player_;  
    Vector2D posOld_;
    unsigned int color_;//�v���C���[�̐F
    int life_;          //���C�t4
    int jump;
    STATE state_;       //���
    bool isDeath_;
    int playerCount_;

    int idleImg_[4];
    int runImg_[6];
    int jumpImg_[4];
    int fallImg_[4];
    int deathImg_[6];
    
    float mutekicount_;   //��ňꊇ�Ǘ�

};

