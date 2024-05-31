#include "ModuleTeamKill.h"

ModuleTeamKill* ModuleTeamKill::GetInstance(bool clear)
{
    if (clear) __team_kill_instance = nullptr;
    return __team_kill_instance;
}
