#include "ModuleXRay.h"

ModuleXRay* ModuleXRay::GetInstance(bool clear)
{
    if (clear) __xray_instance = nullptr;
    return __xray_instance;
}