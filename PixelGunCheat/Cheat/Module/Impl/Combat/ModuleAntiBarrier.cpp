#include "ModuleAntiBarrier.h"

ModuleAntiBarrier* ModuleAntiBarrier::GetInstance(bool clear)
{
    if (clear) __anti_barrier_instance = nullptr;
    return __anti_barrier_instance;
}
