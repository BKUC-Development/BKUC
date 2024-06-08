#include "MethodHooks.h"

#include <MinHook.h>

#include "UnityGame.h"
#include "../Internal/Functions.h"
#include "Hooks/Detours/DetourUnityLogger.h"

DetourUnityLogger* unity_logger_detour = new DetourUnityLogger();

void MethodHooks::InitDetours()
{
    UnityGame::init();
    Functions::init(UnityGame::GameBase, UnityGame::GameAssembly, UnityGame::UnityPlayer);

    // Replacement things for all necessary Il2CppResolver functionalities
    IL2CPPUtil::init();
    
    MH_Initialize();
    
    unity_logger_detour->HandleDetours();

    Functions::ConstructString("This is a test");
    Functions::ConstructStringAdv("This is a test 2");
    // add all detours here...
}

void MethodHooks::UnloadDetours()
{
    unity_logger_detour = nullptr;
    
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}
