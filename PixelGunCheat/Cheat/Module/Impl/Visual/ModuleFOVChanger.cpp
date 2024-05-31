#include "ModuleFOVChanger.h"

ModuleFOVChanger* ModuleFOVChanger::GetInstance(bool clear)
{
    if (clear) __fov_instance = nullptr;
    return __fov_instance;
}