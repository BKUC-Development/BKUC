#include "ModuleHeadshotMultiplier.h"

ModuleHeadshotMultiplier* ModuleHeadshotMultiplier::GetInstance(bool clear)
{
    if (clear) __headshot_multiplier_instance = nullptr;
    return __headshot_multiplier_instance;
}
