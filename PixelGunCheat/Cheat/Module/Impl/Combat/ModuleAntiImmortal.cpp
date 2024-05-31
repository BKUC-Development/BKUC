#include "ModuleAntiImmortal.h"

ModuleAntiImmortal* ModuleAntiImmortal::GetInstance(bool clear)
{
    if (clear) __anti_immortal_instance = nullptr;
    return __anti_immortal_instance;
}
