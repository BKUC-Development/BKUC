#include "ModuleFullAuto.h"

ModuleFullAuto* ModuleFullAuto::GetInstance(bool clear)
{
    if (clear) __full_auto_instance = nullptr;
    return __full_auto_instance;
}
