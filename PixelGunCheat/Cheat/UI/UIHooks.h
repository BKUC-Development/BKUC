#pragma once

class UIHooks
{
public:
    static void UnloadImGui(bool is_dx_11);
    static void SetUpImGuiWindow(void* handle, void* device, void* device_context, bool is_dx_11);
    static void StartImGui(void* g_mainRenderTargetView, void* g_pd3dDevice, void* g_pd3dDeviceContext, bool is_dx_11);
};
