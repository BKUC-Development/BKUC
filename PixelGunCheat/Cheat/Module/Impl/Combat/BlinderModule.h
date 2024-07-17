#pragma once
#include <random>

#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCCheckbox __random_blind = { "Blind Random", false, "Randomizes what blindness effect is applied to the enemy." };
static BKUCSlider __blind_duration = { "Blind Duration", 9999, 0, 9999 };

static std::vector blind_effects = {
    23, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37,
    39, 40, 41, 42, 43, 44, 45, 46, 48, 50, 53,
    54, 55, 56, 57, 58, 59, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73, 75, 76, 77
}; 

class BlinderModule : public BKUCModule
{
public:
    BlinderModule() : BKUCModule("Blinder", "Bleach their eyes!!!", COMBAT, 0x0, true, { &__random_blind, &__blind_duration }) {}
    
    void exec(void* arg) override
    {
        std::vector<int> out;
        std::ranges::sample(
            blind_effects,
            std::back_inserter(out),
            1,
            std::mt19937{std::random_device{}()}
        );
        set_bool(arg, Offsets::isBlindEffect, true);
        set_float(arg, Offsets::isBlindEffectTime, __blind_duration.current);
        set_int(arg, Offsets::blindEffect, out[0]);
    }
};
