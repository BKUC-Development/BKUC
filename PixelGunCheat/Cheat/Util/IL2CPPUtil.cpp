#include "IL2CPPUtil.h"

#include "../Core/UnityGame.h"

void IL2CPPUtil::init()
{
    get_domain = reinterpret_cast<get_domain_t>( GetProcAddress( (HMODULE) UnityGame::GameAssembly, "il2cpp_domain_get" ) );
    create_string = reinterpret_cast<create_string_t>( GetProcAddress( (HMODULE) UnityGame::GameAssembly, "il2cpp_string_new" ) );
}
