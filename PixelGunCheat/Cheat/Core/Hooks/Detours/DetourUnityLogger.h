#pragma once

#include "../Detour.h"
#include "../../../Logger/Logger.h"
#include "../../../Util/ClientUtil.h"
#include "../../../Util/IL2CPPUtil.h"

inline void (__stdcall* debug_log_orig)(void* arg);
inline void __stdcall debug_log(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if (cpp_str.find("eventstore") != std::string::npos || cpp_str.find("FreeChestController.AreAdcAvailable") != std::string::npos) return debug_log_orig(arg);
        Logger::log_info("[UNITY] " + cpp_str);
        debug_log_orig(arg);
    }
}

inline void (__stdcall* debug_log_warn_orig)(void* arg);
inline void __stdcall debug_log_warn(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_warn("[UNITY] " + cpp_str);
        debug_log_warn_orig(arg);
    }
}

inline void (__stdcall* debug_log_error_orig)(void* arg);
inline void __stdcall debug_log_error(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_err("[UNITY] " + cpp_str);
        debug_log_error_orig(arg);
    }
}

inline void (__stdcall* debug_log_fmt_orig)(void* arg);
inline void __stdcall debug_log_fmt(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if (cpp_str.find("eventstore") != std::string::npos || cpp_str.find("FreeChestController.AreAdcAvailable") != std::string::npos) return debug_log_fmt_orig(arg);
        Logger::log_info("[UNITY] " + cpp_str);
        debug_log_fmt_orig(arg);
    }
}

inline void (__stdcall* debug_log_warn_fmt_orig)(void* arg);
inline void __stdcall debug_log_warn_fmt(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_warn("[UNITY] " + cpp_str);
        debug_log_warn_fmt_orig(arg);
    }
}

inline void (__stdcall* debug_log_error_fmt_orig)(void* arg);
inline void __stdcall debug_log_error_fmt(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_err("[UNITY] " + cpp_str);
        debug_log_error_fmt_orig(arg);
    }
}

inline void (__stdcall* debug_log_fmt_orig2)(void* arg);
inline void __stdcall debug_log_fmt2(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if (cpp_str.find("eventstore") != std::string::npos || cpp_str.find("FreeChestController.AreAdcAvailable") != std::string::npos) return debug_log_fmt_orig2(arg);
        Logger::log_info("[UNITY] " + cpp_str);
        debug_log_fmt_orig2(arg);
    }
}

inline void (__stdcall* debug_log_warn_fmt_orig2)(void* arg);
inline void __stdcall debug_log_warn_fmt2(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_warn("[UNITY] " + cpp_str);
        debug_log_warn_fmt_orig2(arg);
    }
}

inline void (__stdcall* debug_log_error_fmt_orig2)(void* arg);
inline void __stdcall debug_log_error_fmt2(void* arg)
{
    IL2CPPUtil::System_String* str = (IL2CPPUtil::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_err("[UNITY] " + cpp_str);
        debug_log_error_fmt_orig2(arg);
    }
}


class DetourUnityLogger : public Detour
{
public:
    void HandleDetours() override
    {
        HookMethod(0x43667e0, &debug_log, &debug_log_orig); // Log 1arg
        HookMethod(0x4366710, &debug_log_fmt, &debug_log_fmt_orig); // Log 2arg
        HookMethod(0x4366300, &debug_log_fmt2, &debug_log_fmt_orig2); // LogFormat 2arg
        
        HookMethod(0x4366650, &debug_log_warn, &debug_log_warn_orig); // LogWarning 1arg
        HookMethod(0x4366580, &debug_log_warn_fmt, &debug_log_warn_fmt_orig); // LogWarning 2arg
        HookMethod(0x43663d0, &debug_log_warn_fmt2, &debug_log_warn_fmt_orig2); // LogWarningFormat 2arg
        
        HookMethod(0x43660c0, &debug_log_error, &debug_log_error_orig); // LogError 1arg
        HookMethod(0x4365ff0, &debug_log_error_fmt, &debug_log_error_fmt_orig); // LogError 2arg
        HookMethod(0x4365f20, &debug_log_error_fmt2, &debug_log_error_fmt_orig2); // LogErrorFormat 2arg
    }
};
