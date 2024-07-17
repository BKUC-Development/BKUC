#pragma once
#include "../Detour.h"
#include "../../../Module/BKUCModule.h"
#include "../../../Offsets/Offsets.h"
#include "../../../Util/ClientUtil.h"

inline void(__stdcall* weapon_sounds_original)(void* arg);
inline void __stdcall weapon_sounds_call(void* arg)
{
    if (ClientUtil::IsMyPlayerWeaponSounds(arg))
    {
        // if (Hooks::our_player != nullptr && aim_bot_module && aim_bot_module->is_using_silent_aim) ((ModuleBase*)aim_bot_module)->run(arg);
        
        for (BKUCModule* weapon_sounds_module : BKUCModuleUtil::get_modules_of_type(WEAPON_SOUNDS))
        {
            weapon_sounds_module->run(arg);
        }
    }
    else
    {
        /*
        for (ModuleBase* weapon_sounds_other_module : weapon_sound_others_modules)
        {
            weapon_sounds_other_module->run(arg);
        }
        */
    }

    return weapon_sounds_original(arg);
}

inline void(__stdcall* weapon_sounds_late_original)(void* arg);
inline void __stdcall weapon_sounds_late_call(void* arg)
{
    if (ClientUtil::IsMyPlayerWeaponSounds(arg))
    {
        // if (Hooks::our_player != nullptr && aim_bot_module && !aim_bot_module->is_using_silent_aim) ((ModuleBase*)aim_bot_module)->run(arg);
    }

    return weapon_sounds_late_original(arg);
}

inline void(__stdcall* player_move_c_original)(void* arg);
inline void __stdcall player_move_c(void* arg)
{
    if (ClientUtil::IsMyPlayer(arg))
    {
        // Just do this every fucking call innit
        // Hooks::main_camera = find_main_camera();
        // if (Hooks::main_camera == nullptr) return player_move_c_original(arg);
        ClientUtil::our_player = arg; // WARN: ALWAYS ALLOW THIS TO BE SET, OTHERWISE BREAKS A LOT OF MODULES
        
        // Hooks::fov_changer_module->run(nullptr);

        // Functions::SendChat(arg, Hooks::create_system_string(".gg/security-research [ " + random_string(8) + " ] "));
        
        for (BKUCModule* player_move_c_module : BKUCModuleUtil::get_modules_of_type(PLAYER_MOVE_C))
        {
            player_move_c_module->run(arg);
        }
    }
    else
    {
        /*
        // Other Players
        if (Hooks::main_camera == nullptr) return player_move_c_original(arg);
        Hooks::fov_changer_module->run(nullptr);
        esp_module->add_esp(arg);
        working_player_list.push_back(arg);
        
        for (auto player_move_c_others_module : player_move_c_others_modules)
        {
            player_move_c_others_module->run(arg);
        }
        */
    }
    
    return player_move_c_original(arg);
}

inline void(__stdcall* player_move_c_fixed_original)(void* arg);
inline void __stdcall player_move_c_fixed(void* arg)
{
    const auto player_damageable = (void*)*(uint64_t*)((uint64_t)arg + Offsets::playerMoveCPlayerDamageable);
    if (ClientUtil::IsMyPlayer(arg))
    {
        ClientUtil::fixed_tick++;
        
        for (BKUCModule* player_damageable_module : BKUCModuleUtil::get_modules_of_type(PLAYER_DAMAGEABLE))
        {
            player_damageable_module->run(player_damageable);
        }
    }
    else
    {
        // Other Players
    }
    
    return player_move_c_fixed_original(arg);
}

inline float(__stdcall* on_pre_render_original)(void* arg);
inline float __stdcall on_pre_render(void* arg)
{
    if (ClientUtil::tick % 60 == 0)
    {
        ClientUtil::UpdateWinSize();
    }
    
    ClientUtil::tick++;

    /*
    Hooks::player_list = working_player_list;
    const std::list<void*> tl;
    working_player_list = tl;
    */
    
    for (BKUCModule* on_pre_render_module : BKUCModuleUtil::get_modules_of_type(PRE_RENDER))
    {
        on_pre_render_module->run(arg);
    }

    return on_pre_render_original(arg);
}

inline void (__stdcall* on_scene_unload_original)(void* arg);
inline void __stdcall on_scene_unload(void* arg)
{
    /*
    Hooks::main_camera = nullptr;
    nuke_player_list();
    */
    return on_scene_unload_original(arg);
    // Get Old Scene Name
    /*
    void* name_ptr = (void*)*(uint64_t*)((uint64_t)arg + 0x10);
    if (name_ptr == nullptr) return;
    std::string name = ((Unity::System_String*)name_ptr)->ToString();
    std::string clean = clean_string(name);
    std::cout << clean << std::endl;
    */
}

class DetourCoreHooks : public Detour
{
public:
    void HandleDetours() override
    {
        HookMethod(Offsets::PlayerMoveCUpdate, &player_move_c, &player_move_c_original);
        HookMethod(Offsets::PlayerMoveCFixedUpdate, &player_move_c_fixed, &player_move_c_fixed_original);
        HookMethod(Offsets::WeaponSoundsUpdate, &weapon_sounds_call, &weapon_sounds_original);
        HookMethod(Offsets::WeaponSoundsLateUpdate, &weapon_sounds_late_call, &weapon_sounds_late_original);
        HookMethod(Offsets::OnPreRender, &on_pre_render, &on_pre_render_original);
        HookMethod(Offsets::OnSceneUnload, &on_scene_unload, &on_scene_unload_original);
    }
};
