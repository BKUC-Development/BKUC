#include "ModuleSpoofModules.h"

ModuleSpoofModules* ModuleSpoofModules::GetInstance(bool clear)
{
    if (clear) __spoof_modules_instance = nullptr;
    return __spoof_modules_instance;
}