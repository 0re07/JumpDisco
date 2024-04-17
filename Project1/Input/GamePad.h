#pragma once
#include "Controller.h"

class GamePad :
    public Controller
{
public:
    GamePad();
    ~GamePad();

private:
    void Update(void) override;
    void Update(BaseScene& scene) override;

};

