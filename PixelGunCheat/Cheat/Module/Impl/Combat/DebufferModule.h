#pragma once
#include "../../BKUCModule.h"
#include "../../../Offsets/Offsets.h"

static BKUCCheckbox __charm = { "Charm", false };

static BKUCCheckbox __curse = { "Curse", false };
static BKUCSlider __curse_duration = { "Curse Duration", 9999, 0, 9999, "", { { &__curse, EQUAL, true } } };
static BKUCSlider __curse_damage = { "Curse Damage", 10, 0, 100, "", { { &__curse, EQUAL, true } } };

static BKUCCheckbox __lightning = { "Lightning", false };

static BKUCCheckbox __poison = { "Poison", true };
static BKUCSliderInt __poison_amount = { "Poison Amount", 9999, 0, 9999, "", { { &__poison, EQUAL, true } } };
static BKUCSlider __poison_time = { "Poison Time", 9999, 0, 9999, "", { { &__poison, EQUAL, true } } };
static BKUCSlider __poison_multi = { "Poison Multiplier", 9999, 0, 9999, "This may or may not work!", { { &__poison, EQUAL, true } } };

static BKUCCheckbox __slow = { "Slow", true };
static BKUCSlider __slow_duration = { "Slow Duration", 9999, 0, 9999, "", { { &__slow, EQUAL, true } } };
static BKUCSlider __slow_factor = { "Slow Factor", 0.001f, 0.001f, 10, "", { { &__slow, EQUAL, true } } };

static BKUCCheckbox __stun = { "Stun", false };
static BKUCSlider __stun_duration = { "Stun Duration", 9999, 0, 9999, "", { { &__stun, EQUAL, true } } };
static BKUCSlider __stun_factor = { "Stun Factor", 10, 0.001f, 10, "", { { &__stun, EQUAL, true } } };
static BKUCSlider __stun_radius = { "Stun Radius", 9999, 0, 9999, "", { { &__stun, EQUAL, true } } };

class DebufferModule : public BKUCModule
{
public:
    DebufferModule() : BKUCModule("Debuffer", "Twists everyone's kneecaps", COMBAT, 0x0, true, { &__charm, &__curse, &__curse_duration, &__curse_damage, &__lightning, &__poison, &__poison_amount, &__slow, &__slow_duration, &__slow_factor, &__stun, &__stun_duration, &__stun_factor, &__stun_radius}) {}
    
    void exec(void* arg) override
    {
        if (__charm.checked)
        {
            set_bool(arg, Offsets::isCharm, true);
        }

        if (__curse.checked)
        {
            set_bool(arg, Offsets::isCursing, true);
            set_float(arg, Offsets::curseTime, __curse_duration.current);
            set_float(arg, Offsets::curseDamageMultiplier, __curse_damage.current);
        }

        if (__lightning.checked)
        {
            set_bool(arg, Offsets::isLightning, true);
        }

        if (__poison.checked)
        {
            set_bool(arg, Offsets::isPoisoning, true);
            set_int(arg, Offsets::poisonCount, __poison_amount.current);
            set_float(arg, Offsets::poisonDamageMultiplier, __poison_multi.current);
            set_float(arg, Offsets::poisonTime, __poison_time.current);
        }

        if (__slow.checked)
        {
            set_bool(arg, Offsets::isSlowdown, true);
            set_float(arg, Offsets::slowdownCoeff, __slow_factor.current);
            set_float(arg, Offsets::slowdownTime, __slow_duration.current);
            set_bool(arg, Offsets::isSlowdownStack, true);
        }

        if (__stun.checked)
        {
            set_bool(arg, Offsets::isStun, true);
            set_float(arg, Offsets::stunCoeff, __stun_factor.current);
            set_float(arg, Offsets::stunTime, __stun_duration.current);
            set_float(arg, Offsets::stunRadius, __stun_radius.current);
        }
    }
};
