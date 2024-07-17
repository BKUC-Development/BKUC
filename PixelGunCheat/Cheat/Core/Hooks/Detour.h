#pragma once
#include <cstdint>
#include <Windows.h>

class Detour
{
public:
    virtual void HandleDetours() = 0;
    static void HookMethod(uint64_t offset, LPVOID detour, void* original);
};
