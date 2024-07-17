#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __aoe_range = { "Range",  9999, 0, 9999 };
static BKUCSlider __aoe_damage = { "Damage",  5, 0, 20, "High damage values may cause kicks!" };
static BKUCCheckbox __aoe_weapon_fix = { "Weapon Fix", false, "Changes some weapon types to false, some weapons will break with this while turned on!" };

class AOEBulletsModule : public BKUCModule
{
public:
    AOEBulletsModule() : BKUCModule("AOE Bullets", "Massive bullets, kind of, sometimes", COMBAT, 0x0, false, { &__aoe_range, &__aoe_damage }) {}
    
    void exec(void* arg) override
    {
        if (__aoe_weapon_fix.checked)
        {
            set_bool(arg, Offsets::flamethrower, false);
            set_bool(arg, Offsets::railgun, false);
            set_bool(arg, Offsets::bazooka, false);
            set_bool(arg, Offsets::harpoon, false);
        }
        
        set_bool(arg, Offsets::isSectorsAOE, true);
        set_float(arg, Offsets::sectorsAOEAngleBack, 360);
        set_float(arg, Offsets::sectorsAOEAngleFront, 360);
        set_float(arg, Offsets::sectorsAOEDamageMultiplierBack, __aoe_damage.current);
        set_float(arg, Offsets::sectorsAOEDamageMultiplierFront, __aoe_damage.current);
        set_float(arg, Offsets::sectorsAOEDamageMultiplierSide, __aoe_damage.current);
        set_float(arg, Offsets::sectorsAOERadiusSectorsAoE, __aoe_range.current);
    }
};
