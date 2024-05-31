#include "ModuleInstantCharge.h"

ModuleInstantCharge* ModuleInstantCharge::GetInstance(bool clear)
{
    if (clear) __instant_charge_instance = nullptr;
    return __instant_charge_instance;
}
