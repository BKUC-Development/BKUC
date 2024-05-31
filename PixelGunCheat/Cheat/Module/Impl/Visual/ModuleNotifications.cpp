#include "ModuleNotifications.h"

ModuleNotifications* ModuleNotifications::GetInstance(bool clear)
{
    if (clear) __notifications_instance = nullptr;
    return __notifications_instance;
}