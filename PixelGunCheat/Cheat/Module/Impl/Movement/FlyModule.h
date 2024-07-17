#pragma once
#include "../../BKUCModule.h"
#include "../../../Internal/Functions.h"
#include "../../../Util/ClientUtil.h"

static void* fly_player_instance;

class FlyModule : public BKUCModule
{
public:
    FlyModule() : BKUCModule("Fly", "Become an airliner", MOVEMENT, 0x0, false, {}) {}
    
    void exec(void* arg) override
    {
        if (ClientUtil::fixed_tick % 120 == 0) Functions::ActivateGadget(arg, 3, 65);
        fly_player_instance = arg;
    }
};
