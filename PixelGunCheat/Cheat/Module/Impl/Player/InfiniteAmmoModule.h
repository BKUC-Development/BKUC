#pragma once
#include "../../BKUCModule.h"

static BKUCCheckbox __infinite_ammo_extra_patches = { "Extra Patches", false, "Adds extra functionality to how you get infinite ammo" };

class InfiniteAmmoModule : public BKUCModule
{
public:
    InfiniteAmmoModule() : BKUCModule("Infinite Ammo", "Ammo capacity module with a slight upgrade", PLAYER, 0x0, true, { &__infinite_ammo_extra_patches }) {}
    
    void exec(void* arg) override
    {
        if (__infinite_ammo_extra_patches.checked)
        {
            set_bool(arg, 0x459, true); // isUnlimitedAmmo
        
            void* item_record = get_void(arg, 0x6a0); // itemRecord
            set_bool(item_record, 0x6c, true); // isUnlimitedAmmo
            set_int(item_record, 0x20, 9999); // ammoInClip
            set_int(item_record, 0xb0, 9999); // modulesClipAmmoModifier
            set_int(item_record, 0x58, 9999); // initialAmmo
        }
    }
};
