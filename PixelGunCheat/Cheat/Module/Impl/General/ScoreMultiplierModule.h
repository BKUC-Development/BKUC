#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCSlider __score_amount = { "Amount", 10, 0, 9999, "Use large multiplier values with caution!" };

class ScoreMultiplierModule : public BKUCModule
{
public:
    ScoreMultiplierModule() : BKUCModule("Score Multiplier", "Just so skilled to get such a high score!", GENERAL, 0x0, false, { &__score_amount }) {}
    
    void exec(void* arg) override
    {
        set_bool(arg, Offsets::isBuffPoints, true);
        set_bool(arg,Offsets::buffPointsKillDesigner, true);
        set_bool(arg, Offsets::buffPointsAssistDesigner, true);
        set_bool(arg, Offsets::buffPointsRevengeDesigner, true);
        set_float(arg, Offsets::buffPointsOther, __score_amount.current);
        set_float(arg, Offsets::buffBonusPointsForKill, __score_amount.current);
        set_float(arg, Offsets::buffBonusPointsForAssist, __score_amount.current);
        set_float(arg, Offsets::buffPointsRevenge, __score_amount.current);
    }
};
