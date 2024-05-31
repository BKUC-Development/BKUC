#include "ModuleAOEBullets.h"

ModuleAOEBullets* ModuleAOEBullets::GetInstance(bool clear)
{
    if (clear) __aoe_bullets_instance = nullptr;
    return __aoe_bullets_instance;
}
