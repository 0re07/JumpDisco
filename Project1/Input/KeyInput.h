#pragma once
#include "Controller.h"

class KeyInput :
    public Controller
{
public:
    KeyInput();
    ~KeyInput();

private:
    void Update(void) override;

    //���͏��̊i�[
    std::map<InputID, int> inputTbl_;

    std::array<char, 256> keyData_;
};

