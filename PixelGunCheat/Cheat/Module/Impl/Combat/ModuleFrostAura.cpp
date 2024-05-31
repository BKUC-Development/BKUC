#include "ModuleFrostAura.h"

ModuleFrostAura* ModuleFrostAura::GetInstance(bool clear)
{
    if (clear) __frost_aura_instance = nullptr;
    return __frost_aura_instance;
}
