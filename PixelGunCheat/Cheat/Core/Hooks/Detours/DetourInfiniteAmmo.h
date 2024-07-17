#pragma once
#include "../Detour.h"
#include "../../../Module/Impl/Player/InfiniteAmmoModule.h"
#include "../../../Offsets/Offsets.h"

inline InfiniteAmmoModule* infinite_ammo_module = new InfiniteAmmoModule();

inline int (__stdcall* ammo_in_clip_original)(void* arg);
inline int __stdcall ammo_in_clip(void* arg)
{
    if (infinite_ammo_module->enabled) return 9999;
    return ammo_in_clip_original(arg);
}

inline int (__stdcall* ammo_original)(void* arg);
inline int __stdcall ammo(void* arg)
{
    if (infinite_ammo_module->enabled) return 9999;
    return ammo_original(arg);
}

class DetourInfiniteAmmo : public Detour
{
public:
    void HandleDetours() override
    {
        HookMethod(Offsets::GetAmmoInClip, &ammo_in_clip, &ammo_in_clip_original);
        HookMethod(Offsets::GetAmmo, &ammo, &ammo_in_clip_original);
    }

    static InfiniteAmmoModule* GetModule()
    {
        return infinite_ammo_module;
    }
};
