#pragma once
#include "../common/Vector2D.h"

class Hoop
{
public:
    enum class STATE
    {
        BORN,
        BEFORE,
        START,
        END
    };

    Hoop();
    Hoop(Vector2D pos);
    ~Hoop();

    bool Init(void);
    void Update(void);
    void Draw(void);

    //円の生成
    void Create(void);

    //円の情報取得
    Circle GetInHoop(void)const;
    Circle GetOutHoop(void)const;

private:
    void UpdateBorn(void);
    void UpdateBefore(void);
    void UpdateStart(void);
    void UpdateEnd(void);

    void Release(void);

    //状態遷移
    void ChengeState(STATE state); 

    //状態
    STATE state_;

    Circle inHoop_;    //内側の円
    Circle outHoop_;   //外側の円

    //画面サイズ
    Vector2D screenSize_;

    //円の色
    unsigned int color_;

    //出現地
    float coreRadius_;

    //生存フラグ
    bool isEnd_;

};

