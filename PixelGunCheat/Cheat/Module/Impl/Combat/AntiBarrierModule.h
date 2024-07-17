#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

class AntiBarrierModule : public BKUCModule
{
public:
    AntiBarrierModule() : BKUCModule("Anti Barrier", "Pretty much just anti rusted revolver", COMBAT, 0x0, true, {}) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::ignoreBarrier, true);
        set_bool(arg, Offsets::ignoreSlyWolf, true);
        set_bool(arg, Offsets::ignoreReflector, true);
    }
};
