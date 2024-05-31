#include "ModuleSpread.h"

ModuleSpread* ModuleSpread::GetInstance(bool clear)
{
    if (clear) __spread_instance = nullptr;
    return __spread_instance;
}
