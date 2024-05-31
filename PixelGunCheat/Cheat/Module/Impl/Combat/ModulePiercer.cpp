#include "ModulePiercer.h"

ModulePiercer* ModulePiercer::GetInstance(bool clear)
{
    if (clear) __piercer_instance = nullptr;
    return __piercer_instance;
}
