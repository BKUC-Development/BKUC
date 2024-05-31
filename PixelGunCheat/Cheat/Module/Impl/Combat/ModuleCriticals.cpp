#include "ModuleCriticals.h"

ModuleCriticals* ModuleCriticals::GetInstance(bool clear)
{
    if (clear) __criticals_instance = nullptr;
    return __criticals_instance;
}
