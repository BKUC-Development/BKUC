#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCCheckbox __immunity_poison = { "Poison", true };
static BKUCCheckbox __immunity_bleeding = { "Slow", true };
static BKUCCheckbox __immunity_toxic = { "Stun", true };

class ImmunityModule : public BKUCModule
{
public:
    ImmunityModule() : BKUCModule("Immunity", "Bro got his vaccines", PLAYER, 0x0, true, { &__immunity_poison, &__immunity_bleeding, &__immunity_toxic }) {}
    
    void exec(void* arg) override
    {
        if (__immunity_poison.checked) set_bool(arg, Offsets::fireImmunity, true);
        if (__immunity_bleeding.checked) set_bool(arg, Offsets::bleedingImmunity, true);
        if (__immunity_toxic.checked) set_bool(arg, Offsets::toxicImmunity, true);
    }
};
