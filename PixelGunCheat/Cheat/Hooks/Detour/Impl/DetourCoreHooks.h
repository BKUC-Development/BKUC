#pragma once

#include "../Detour.h"
#include "../GMD.h"
#include "../DetourVars.h"
#include "../../../Offsets/Offsets.h"

inline void nuke_player_list()
{
    DetourVars::working_player_list.clear();
    DetourVars::player_list.clear();
}

inline void(__stdcall* player_move_c_original)(void* arg);
inline void __stdcall player_move_c(void* arg)
{
    if (ClientUtil::IsPlayerSelf(arg))
    {
        // Just do this every fucking call innit
        Hooks::our_player = arg; // WARN: ALWAYS ALLOW THIS TO BE SET, OTHERWISE BREAKS A LOT OF MODULES IF NOT
        Hooks::main_camera = Functions::CameraGetMain();
        if (Hooks::main_camera == nullptr) return player_move_c_original(arg);
        
        // Functions::SendChat(arg, Hooks::create_system_string(".gg/security-research [ " + random_string(8) + " ] "));
        
        for (ModuleBase* player_move_c_module : GMD::player_move_c_modules)
        {
            player_move_c_module->run(arg);
        }
    }
    else
    {
        // Other Players
        if (Hooks::main_camera == nullptr) return player_move_c_original(arg);
        ModuleESP::add_esp(arg);
        DetourVars::working_player_list.push_back(arg);
        
        for (auto player_move_c_others_module : GMD::player_move_c_others_modules)
        {
            player_move_c_others_module->run(arg);
        }
    }

    ClientUtil::RunSafe(ModuleFOVChanger::GetInstance(), nullptr);
    return player_move_c_original(arg);
}

inline void(__stdcall* player_move_c_fixed_original)(void* arg);
inline void __stdcall player_move_c_fixed(void* arg)
{
    const auto player_damageable = Functions::GetPlayerDamageable(arg);
    if (ClientUtil::IsPlayerSelf(arg))
    {
        ClientUtil::fixed_tick_ingame++;
        for (ModuleBase* player_damageable_module : GMD::player_damageable_modules) player_damageable_module->run(player_damageable);
    }
    else
    {
        // Other Players
    }
    
    return player_move_c_fixed_original(arg);
}

inline void(__stdcall* weapon_sounds_original)(void* arg);
inline void __stdcall weapon_sounds_call(void* arg)
{
    if (ClientUtil::IsPlayerSelfWeaponSounds(arg))
    {
        if (Hooks::our_player != nullptr && ModuleAimBot::GetInstance()->is_using_silent_aim) ClientUtil::RunSafe(ModuleAimBot::GetInstance(), arg);
        ClientUtil::RunSafe(ModuleUnlockWeapons::GetInstance(), arg);
        ClientUtil::RunSafe(ModuleUnlockGadgets::GetInstance(), arg);
        ClientUtil::RunSafe(ModuleAddArmor::GetInstance(), arg);
        ClientUtil::RunSafe(ModuleAddPets::GetInstance(), arg);
        ClientUtil::RunSafe(ModuleAddCurrency::GetInstance(), arg);
        
        for (ModuleBase* weapon_sounds_module : GMD::weapon_sounds_modules)
        {
            ClientUtil::RunSafe(weapon_sounds_module, arg);
        }
    }
    else
    {
        for (ModuleBase* weapon_sounds_other_module : GMD::weapon_sound_others_modules)
        {
            ClientUtil::RunSafe(weapon_sounds_other_module, arg);
        }
    }

    return weapon_sounds_original(arg);
}

inline void(__stdcall* weapon_sounds_late_original)(void* arg);
inline void __stdcall weapon_sounds_late_call(void* arg)
{
    if (ClientUtil::IsPlayerSelfWeaponSounds(arg))
    {
        if (Hooks::our_player != nullptr && !ModuleAimBot::GetInstance()->is_using_silent_aim) ClientUtil::RunSafe(ModuleAimBot::GetInstance(), arg);
    }

    return weapon_sounds_late_original(arg);
}

inline float(__stdcall* on_pre_render_original)(void* arg);
inline float __stdcall on_pre_render(void* arg)
{
    if (ClientUtil::tick % 60 == 0)
    {
        ClientUtil::UpdateWinSize();
    }
    
    ClientUtil::tick++;
    
    DetourVars::player_list = DetourVars::working_player_list;
    DetourVars::working_player_list.clear();
    
    for (ModuleBase* on_pre_render_module : GMD::on_pre_render_modules)
    {
        ClientUtil::RunSafe(on_pre_render_module, arg);
    }

    return on_pre_render_original(arg);
}

inline void (__stdcall* on_scene_unload_original)(void* arg);
inline void __stdcall on_scene_unload(void* arg)
{
    Hooks::main_camera = nullptr;
    nuke_player_list();
    return on_scene_unload_original(arg);
}

class DetourCoreHooks : Detour
{
public:
    void init_detours() override
    {
        create_method_detour(Offsets::PlayerMoveCUpdate, &player_move_c, &player_move_c_original);
        create_method_detour(Offsets::PlayerMoveCFixedUpdate, &player_move_c_fixed, &player_move_c_fixed_original);
        create_method_detour(Offsets::WeaponSoundsUpdate, &weapon_sounds_call, &weapon_sounds_original);
        create_method_detour(Offsets::WeaponSoundsLateUpdate, &weapon_sounds_late_call, &weapon_sounds_late_original);
        create_method_detour(Offsets::OnSceneUnload, &on_scene_unload, &on_scene_unload_original);
        create_method_detour(Offsets::OnPreRender, &on_pre_render, &on_pre_render_original);
    }
};
