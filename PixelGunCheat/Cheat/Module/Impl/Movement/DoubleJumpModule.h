#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

class DoubleJumpModule : public BKUCModule
{
public:
    DoubleJumpModule() : BKUCModule("Double Jump", "But where triple jump???", MOVEMENT, 0x0, false, {}) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::isDoubleJump, true);
    }
};
