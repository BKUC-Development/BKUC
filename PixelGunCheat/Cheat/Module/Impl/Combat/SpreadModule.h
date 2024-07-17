#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __spread_coeff = { "Spread Coefficient", 0, -100, 100, "Spread values too small/large may cause interesting effects!" };

class SpreadModule : public BKUCModule
{
public:
    SpreadModule() : BKUCModule("No Spread", "Boys will not spread their legs anymore :(", COMBAT, 0x0, true, { &__spread_coeff }) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::firstShotScatter, false);
        set_bool(arg, Offsets::instantHorizontalMoveScatterCoeff, false);
        set_bool(arg, Offsets::instantVerticalMoveScatterCoeff, false);
        set_bool(arg, Offsets::scatterInversion, false);
        set_bool(arg, Offsets::enableRocketScatter, false);

        set_bool(arg, Offsets::firstShotScatterZoom, false);
        set_bool(arg, Offsets::instantHorizontalMoveScatterCoeffZoom, false);
        set_bool(arg, Offsets::instantVerticalMoveScatterCoeffZoom, false);
        set_bool(arg, Offsets::scatterInversionZoom, false);
        
        set_float(arg, Offsets::moveScatterCoeff, __spread_coeff.current);
        set_float(arg, Offsets::moveScatterCoeffZoom, __spread_coeff.current);
        // set_float(arg, Offsets::maxKoof, __spread_coeff.current); TODO: Move to new system
        set_float(arg, Offsets::upKoofFireZoom, __spread_coeff.current);
        set_float(arg, Offsets::downKoofFirstZoom, __spread_coeff.current);
        set_float(arg, Offsets::downKoofZoom, __spread_coeff.current);
        set_float(arg, Offsets::maxKoofZoom, __spread_coeff.current);
        set_float(arg, Offsets::tekKoof, __spread_coeff.current);
        set_float(arg, Offsets::upKoofFireZoom, __spread_coeff.current);
        set_float(arg, Offsets::downKoofFirst, __spread_coeff.current);
        set_float(arg, Offsets::downKoof, __spread_coeff.current);
    }
};
