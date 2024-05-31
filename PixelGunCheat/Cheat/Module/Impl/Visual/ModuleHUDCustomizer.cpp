#include "ModuleHUDCustomizer.h"

ModuleHUDCustomizer* ModuleHUDCustomizer::GetInstance(bool clear)
{
    if (clear) __hud_instance = nullptr;
    return __hud_instance;
}