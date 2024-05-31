#include "ModuleAimBot.h"

ModuleAimBot* ModuleAimBot::GetInstance(bool clear)
{
    if (clear) __aim_bot_instance = nullptr;
    return __aim_bot_instance;
}
