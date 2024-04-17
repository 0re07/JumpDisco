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

    //�~�̐���
    void Create(void);

    //�~�̏��擾
    Circle GetInHoop(void)const;
    Circle GetOutHoop(void)const;

private:
    void UpdateBorn(void);
    void UpdateBefore(void);
    void UpdateStart(void);
    void UpdateEnd(void);

    void Release(void);

    //��ԑJ��
    void ChengeState(STATE state); 

    //���
    STATE state_;

    Circle inHoop_;    //�����̉~
    Circle outHoop_;   //�O���̉~

    //��ʃT�C�Y
    Vector2D screenSize_;

    //�~�̐F
    unsigned int color_;

    //�o���n
    float coreRadius_;

    //�����t���O
    bool isEnd_;

};

