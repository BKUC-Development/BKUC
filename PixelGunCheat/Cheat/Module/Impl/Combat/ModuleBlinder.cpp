#include "ModuleBlinder.h"

ModuleBlinder* ModuleBlinder::GetInstance(bool clear)
{
    if (clear) __blinder_instance = nullptr;
    return __blinder_instance;
}
