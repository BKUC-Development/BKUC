#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

class PiercerModule : public BKUCModule
{
public:
    PiercerModule() : BKUCModule("Piercer", "Bro got AP bullets wtf??", COMBAT, 0x0, false, {}) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::bulletBreakout, true);
        set_bool(arg, Offsets::bulletSuperBreakout, true);
        set_bool(arg, Offsets::railgunStopAtWall, false);
    }
};
