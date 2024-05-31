#include "ModuleScoreMultiplier.h"

ModuleScoreMultiplier* ModuleScoreMultiplier::GetInstance(bool clear)
{
    if (clear) __score_multiplier_instance = nullptr;
    return __score_multiplier_instance;
}