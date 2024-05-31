#pragma once
#include <imgui.h>
#include <string>
#include <vector>

#include "../Internal/Functions.h"
#include "../UI/UIHooks.h"

class ClientUtil
{
public:
    static inline std::vector<>
    static inline std::string client_name = "boykisser.cc";
    static inline std::string client_ver = "v3.0-pre";
    static inline int window_display = -1;
    static inline bool has_font_changed = false;
    static inline bool ui_hooks_render = false;
    
    static uint64_t tick;
    static uint64_t fixed_tick;
    static RECT win_size_info;
    static float color_prog_offset;
    
    static void UpdateWinSize();
    static std::string CleanString(std::string string);
    static std::string TokenizeString(std::string string, std::string token);
    static ImVec4 ColorToImVec4(std::vector<float> rgba);
    static std::vector<float> GetColor(uint32_t color);
    static uint32_t GetColorHex(const std::vector<float>& rgba);
    static float BlendProgressWrap(float progress);
    static uint32_t Blend2Color(uint32_t start, uint32_t end, float offset);
    static uint32_t BlendDynamic(float progress, const std::vector<uint32_t>& colors);
    static ImU32 QuickDynamicBlendImU32(float progress, const std::vector<uint32_t>& colors);
    static float GetFrameTime();
};
