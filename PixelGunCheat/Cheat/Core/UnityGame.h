#pragma once
#include <cstdint>
#include <Windows.h>

class UnityGame
{
public:
    static void init()
    {
        GameBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
        GameAssembly = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
        UnityPlayer = reinterpret_cast<uintptr_t>(GetModuleHandleA("UnityPlayer.dll"));
    }
    
    static inline uintptr_t GameBase;
    static inline uintptr_t GameAssembly;
    static inline uintptr_t UnityPlayer;
};
