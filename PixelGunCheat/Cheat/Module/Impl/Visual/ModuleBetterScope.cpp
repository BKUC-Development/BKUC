#include "ModuleBetterScope.h"

ModuleBetterScope* ModuleBetterScope::GetInstance(bool clear)
{
    if (clear) __better_scope_instance = nullptr;
    return __better_scope_instance;
}