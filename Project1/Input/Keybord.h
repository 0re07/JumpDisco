#pragma once
#include "Controller.h"

class Keybord :
    public Controller
{
public:
    Keybord();
    ~Keybord();

private:
    void Update(void) override;
    void Update(BaseScene& scene) override;

    char keyData_[256];					//�L�[�{�[�h���

};

