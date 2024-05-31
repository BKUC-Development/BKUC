#include "ModuleDebuffer.h"

ModuleDebuffer* ModuleDebuffer::GetInstance(bool clear)
{
    if (clear) __debuffer_instance = nullptr;
    return __debuffer_instance;
}
