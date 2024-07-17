#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

class FullAutoModule : public BKUCModule
{
public:
    FullAutoModule() : BKUCModule("Full Auto", "I don't remember this module being in the game...", COMBAT, 0x0, true, {}) {}
    
    void exec(void* arg) override
    {
        set_float(arg, Offsets::shootDelay, 0.000001f);
        // set_float(arg, Offsets::delayInBurstShooting, 0.000001f); TODO: Move to new system
    }
};
