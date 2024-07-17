#include "MethodHooks.h"

#include <fstream>
#include <iostream>
#include <MinHook.h>

#include "UnityGame.h"
#include "../Internal/Functions.h"
#include "../Module/Impl/Combat/AntiBarrierModule.h"
#include "../Module/Impl/Combat/AOEBulletsModule.h"
#include "../Module/Impl/Combat/BlinderModule.h"
#include "../Module/Impl/Combat/CriticalsModule.h"
#include "../Module/Impl/Combat/DebufferModule.h"
#include "../Module/Impl/Combat/FrostAuraModule.h"
#include "../Module/Impl/Combat/FullAutoModule.h"
#include "../Module/Impl/Combat/HeadshotMultiplierModule.h"
#include "../Module/Impl/Combat/InstantChargeModule.h"
#include "../Module/Impl/Combat/PiercerModule.h"
#include "../Module/Impl/Combat/RecoilModule.h"
#include "../Module/Impl/Combat/SpreadModule.h"
#include "../Module/Impl/General/ScoreMultiplierModule.h"
#include "../Module/Impl/Movement/BetterDashModule.h"
#include "../Module/Impl/Movement/DoubleJumpModule.h"
#include "../Module/Impl/Movement/FlyModule.h"
#include "../Module/Impl/Player/ImmunityModule.h"
#include "Hooks/Detours/DetourCoreHooks.h"
#include "Hooks/Detours/DetourInfiniteAmmo.h"
#include "Hooks/Detours/DetourUnityLogger.h"

DetourCoreHooks* core_detour = new DetourCoreHooks();
DetourUnityLogger* unity_logger_detour = new DetourUnityLogger();
DetourInfiniteAmmo* infinite_ammo_detour = new DetourInfiniteAmmo();

void MethodHooks::InitDetours()
{
    UnityGame::init();
    Functions::init(UnityGame::GameBase, UnityGame::GameAssembly, UnityGame::UnityPlayer);
    IL2CPPUtil::init(); // Replacement things for all necessary Il2CppResolver functionalities
    
    MH_Initialize();
    
    core_detour->HandleDetours();
    unity_logger_detour->HandleDetours();
    infinite_ammo_detour->HandleDetours();
    
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new AntiBarrierModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new AOEBulletsModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new BlinderModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new CriticalsModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new DebufferModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new FrostAuraModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new FullAutoModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new HeadshotMultiplierModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new InstantChargeModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new PiercerModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new RecoilModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new SpreadModule());
    
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new ScoreMultiplierModule());

    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new BetterDashModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new DoubleJumpModule());
    BKUCModuleUtil::add_module_to_map(PLAYER_MOVE_C, new FlyModule());

    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, new ImmunityModule());
    BKUCModuleUtil::add_module_to_map(WEAPON_SOUNDS, DetourInfiniteAmmo::GetModule());
}

void MethodHooks::UnloadDetours()
{
    core_detour = nullptr;
    unity_logger_detour = nullptr;
    
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}
