#pragma once
#include <map>
#include <vector>

class BKUCModule;
enum BKUCModuleInvocationType
{
    PLAYER_MOVE_C,
    PLAYER_DAMAGEABLE,
    WEAPON_SOUNDS,
    PRE_RENDER,
    GUI_2D_RENDER
};

class BKUCModuleContainer
{
public:
    static inline std::map<BKUCModuleInvocationType, std::vector<BKUCModule*>> module_invocation_map = {};
    static inline std::vector<BKUCModule*> modules = {};
};
