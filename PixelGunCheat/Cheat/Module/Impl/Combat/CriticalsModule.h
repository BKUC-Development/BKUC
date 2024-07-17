#pragma once
#include "../../BKUCModule.h"
#include "../../../Internal/Functions.h"
#include "../../../Offsets/Offsets.h"

class CriticalsModule : public BKUCModule
{
public:
    CriticalsModule() : BKUCModule("Criticals", "*tf2 crit sound*", COMBAT, 0x0, true, {}) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::firstKillCritical, true);
        Functions::SetNextHitCritical(arg, true);
    }
};
