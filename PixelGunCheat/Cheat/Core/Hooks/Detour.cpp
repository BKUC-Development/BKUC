#include "Detour.h"

#include <ios>
#include <MinHook.h>
#include <sstream>
#include <stacktrace>

#include "../UnityGame.h"
#include "../../Logger/Logger.h"

void Detour::HookMethod(uint64_t offset, LPVOID detour, void* original)
{
    const auto ga_offset = (LPVOID*)(UnityGame::GameAssembly + offset);
    const MH_STATUS create_hook = MH_CreateHook(ga_offset, detour, (LPVOID*)original);
    std::stringstream hexified;
    hexified << std::hex << offset;
    if (create_hook == MH_OK)
    {
        const MH_STATUS enable_hook = MH_EnableHook(ga_offset);
        if (enable_hook == MH_OK) Logger::log_debug("MH_CreateHook && MH_EnableHook success on offset 0x" + hexified.str());
        else Logger::log_err("MH_EnableHook failure on offset 0x" + hexified.str() + "! (Status: " + MH_StatusToString(enable_hook) + ")");
    }
    else Logger::log_err("MH_CreateHook failure on offset 0x" + hexified.str() + "! (Status: " + MH_StatusToString(create_hook) + ")");
}
