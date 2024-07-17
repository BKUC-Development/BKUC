#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __oshs_multi = { "Damage Multiplier", 1, 1, 100, "Multiplier values too high will cause kicks! (Depending on weapon)" };

class HeadshotMultiplierModule : public BKUCModule
{
public:
    HeadshotMultiplierModule() : BKUCModule("Headshot Modifier", "John F. Kennedy would be proud", COMBAT, 0x0, false, { &__oshs_multi }) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::isHeadshotDamageIncreased, true);
        set_float(arg, Offsets::increasedHeadshotDamageMultiplier, __oshs_multi.current);
    }
};
