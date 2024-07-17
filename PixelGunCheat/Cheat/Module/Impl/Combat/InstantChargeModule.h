#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

class InstantChargeModule : public BKUCModule
{
public:
    InstantChargeModule() : BKUCModule("Instant Charge", "Got that 300watt fast charger from Temu", COMBAT, 0x0, false, {}) {}
    
    void exec(void* arg) override
    {
        set_float(arg, Offsets::chargeTime, 0);
        set_float(arg, Offsets::chargeMax, 0);
        set_bool(arg, Offsets::chargeLoop, true);
        set_bool(arg, Offsets::isCharging, false);
    }
};
