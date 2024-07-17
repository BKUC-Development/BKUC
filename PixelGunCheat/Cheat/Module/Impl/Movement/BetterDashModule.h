#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCCheckbox __force_dash = { "Force Dash", false, "Forces a weapon to allow dashing, may break a lot of weapons!" };
static BKUCSlider __dash_impulse = { "Dash Impulse", 100, 0, 1000 };
static BKUCSlider __dash_decay = { "Dash Decay", 3.5f, 0, 100 };
static BKUCSlider __dash_impact = { "Dash Impact", 1, 0, 2 };

class BetterDashModule : public BKUCModule
{
public:
    BetterDashModule() : BKUCModule("Better Dash", "Yeet yourself even further", MOVEMENT, 0x0, false, { &__force_dash, &__dash_impulse, &__dash_decay, &__dash_impact }) {}
    
    void exec(void* arg) override
    {
        if (__force_dash.checked)
        {
            set_bool(arg, Offsets::isDash, true);
        }

        set_float(arg, Offsets::dashMaxImpulse, __dash_impulse.current);
        set_float(arg, Offsets::dashDecaySpeed, __dash_decay.current);
        set_float(arg, Offsets::dashDeltaImpact, __dash_impact.current);
    }
};
