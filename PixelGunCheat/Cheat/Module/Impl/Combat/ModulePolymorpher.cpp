#include "ModulePolymorpher.h"

ModulePolymorpher* ModulePolymorpher::GetInstance(bool clear)
{
    if (clear) __polymorpher_instance = nullptr;
    return __polymorpher_instance;
}
