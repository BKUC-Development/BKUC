#include "ModuleLegacyAnimations.h"

ModuleLegacyAnimations* ModuleLegacyAnimations::GetInstance(bool clear)
{
    if (clear) __legacy_anim_instance = nullptr;
    return __legacy_anim_instance;
}