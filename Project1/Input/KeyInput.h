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

    //“ü—Íî•ñ‚ÌŠi”[
    std::map<InputID, int> inputTbl_;

    std::array<char, 256> keyData_;
};

