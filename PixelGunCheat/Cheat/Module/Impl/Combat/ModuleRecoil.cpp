#include "ModuleRecoil.h"

ModuleRecoil* ModuleRecoil::GetInstance(bool clear)
{
    if (clear) __recoil_instance = nullptr;
    return __recoil_instance;
}
