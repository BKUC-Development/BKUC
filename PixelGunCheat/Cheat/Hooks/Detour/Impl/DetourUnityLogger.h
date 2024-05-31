#pragma once
#include <Unity/Structures/System_String.hpp>

#include "../Detour.h"
#include "../../../Logger/Logger.h"

inline bool blacklist_log(std::string log)
{
    return log.find("eventstore") != std::string::npos || log.find("FreeChestController.AreAdcAvailable") != std::string::npos;
}

inline void (__stdcall* debug_log_orig)(void* arg);
inline void __stdcall debug_log(void* arg)
{
    Unity::System_String* str = (Unity::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if(!blacklist_log(cpp_str)) Logger::log_info("[UNITY] " + cpp_str);
        debug_log_orig(arg);
    }
}

inline void (__stdcall* debug_log_warn_orig)(void* arg);
inline void __stdcall debug_log_warn(void* arg)
{
    Unity::System_String* str = (Unity::System_String*)arg;
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
    Unity::System_String* str = (Unity::System_String*)arg;
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
    Unity::System_String* str = (Unity::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if(!blacklist_log(cpp_str)) Logger::log_info("[UNITY] " + cpp_str);
        debug_log_fmt_orig(arg);
    }
}

inline void (__stdcall* debug_log_warn_fmt_orig)(void* arg);
inline void __stdcall debug_log_warn_fmt(void* arg)
{
    Unity::System_String* str = (Unity::System_String*)arg;
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
    Unity::System_String* str = (Unity::System_String*)arg;
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
    Unity::System_String* str = (Unity::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        if(!blacklist_log(cpp_str)) Logger::log_info("[UNITY] " + cpp_str);
        debug_log_fmt_orig2(arg);
    }
}

inline void (__stdcall* debug_log_warn_fmt_orig2)(void* arg);
inline void __stdcall debug_log_warn_fmt2(void* arg)
{
    Unity::System_String* str = (Unity::System_String*)arg;
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
    Unity::System_String* str = (Unity::System_String*)arg;
    if (str->m_iLength < 524288)
    {
        std::string cpp_str = ClientUtil::CleanString(str->ToString());
        Logger::log_err("[UNITY] " + cpp_str);
        debug_log_error_fmt_orig2(arg);
    }
}

class DetourUnityLogger : Detour
{
public:
    void init_detours() override
    {
        create_method_detour(0x438f9e0, &debug_log, &debug_log_orig); // Log 1arg
        create_method_detour(0x438f850, &debug_log_warn, &debug_log_warn_orig); // LogWarning 1arg
        create_method_detour(0x438f2c0, &debug_log_error, &debug_log_error_orig); // LogError 1arg

        create_method_detour(0x438f910, &debug_log_fmt, &debug_log_fmt_orig); // Log 2arg
        create_method_detour(0x438f780, &debug_log_warn_fmt, &debug_log_warn_fmt_orig); // LogWarning 2arg
        create_method_detour(0x438f1f0, &debug_log_error_fmt, &debug_log_error_fmt_orig); // LogError 2arg

        create_method_detour(0x438f500, &debug_log_fmt2, &debug_log_fmt_orig2); // LogFormat 2arg
        create_method_detour(0x438f5d0, &debug_log_warn_fmt2, &debug_log_warn_fmt_orig2); // LogWarningFormat 2arg
        create_method_detour(0x438f120, &debug_log_error_fmt2, &debug_log_error_fmt_orig2); // LogErrorFormat 2arg
    }
};
