#pragma once

class InfiniteAmmoModule;
class MethodHooks
{
public:
    static void InitDetours();
    static void UnloadDetours();
};
