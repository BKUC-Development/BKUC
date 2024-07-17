#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __recoil_coeff = { "Recoil Coefficient", 0, -100, 100, "Recoil values too small/large may cause interesting effects!" };

class RecoilModule : public BKUCModule
{
public:
    RecoilModule() : BKUCModule("No Recoil", "I don't remember this module being in the game either...", COMBAT, 0x0, true, { &__recoil_coeff }) {}
    
    void exec(void* arg) override
    {
        // set_float(arg, Offsets::recoilCoeff, __recoil_coeff.current); TODO: Move to new system
        set_float(arg, Offsets::recoilCoeffZoom, __recoil_coeff.current);
    }
};
