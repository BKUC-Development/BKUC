#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __frost_range = { "Range", 9999, 0, 9999 };
static BKUCSlider __frost_damage = { "Damage", 2, 0, 20, "High damage values may cause kicks!" };
static BKUCSlider __frost_delay = { "Delay", 0.33f, 0.001f, 2, "Low delay values may cause kicks!" };

class FrostAuraModule : public BKUCModule
{
public:
    FrostAuraModule() : BKUCModule("Frost Aura", "Welcome to Antarctica", COMBAT, 0x0, false, { &__frost_range, &__frost_damage, &__frost_delay }) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::isFrostSword, true);
        set_bool(arg, Offsets::isFrostSwordUseAngle, true);
        set_float(arg, Offsets::frostRadius, __frost_range.current);
        set_float(arg, Offsets::frostDamageMultiplier, __frost_damage.current);
        set_float(arg, Offsets::frostSwordAngle, 360);
        set_float(arg, Offsets::frostSwordnTime, __frost_delay.current);
    }
};
