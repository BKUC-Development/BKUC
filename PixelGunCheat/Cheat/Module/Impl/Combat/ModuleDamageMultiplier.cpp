#include "ModuleDamageMultiplier.h"

ModuleDamageMultiplier* ModuleDamageMultiplier::GetInstance(bool clear)
{
    if (clear) __damage_multiplier_instance = nullptr;
    return __damage_multiplier_instance;
}
