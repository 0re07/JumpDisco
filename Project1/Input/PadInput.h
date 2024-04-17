#pragma once
#include "Controller.h"

class PadInput :
    public Controller
{
public:
    PadInput();
    ~PadInput();

private:
    void Update(void) override;
    bool Init(void);

    //“ü—Íî•ñ‚ÌŠi”[
    std::map<InputID, int> inputTbl_;
};

