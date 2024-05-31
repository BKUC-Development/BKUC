#include "ModuleRapidFire.h"

ModuleRapidFire* ModuleRapidFire::GetInstance(bool clear)
{
    if (clear) __rapid_fire_instance = nullptr;
    return __rapid_fire_instance;
}
