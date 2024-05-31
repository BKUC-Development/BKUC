#pragma once
#include <IL2CPP_Resolver.hpp>

enum UIHooksCategory
{
    NONE = 0,
    GENERAL = 1,
    COMBAT = 2,
    VISUAL = 3,
    MOVEMENT = 4,
    PLAYER = 5,
    EXPLOIT = 6
};

class UIHooks
{
public:
    static void SetUpImGuiWindow(HWND handle, void* device, void* device_context, bool is_dx_11);
    static void StartImGui(void* g_mainRenderTargetView, void* g_pd3dDevice, void* g_pd3dDeviceContext, bool is_dx_11);
};
