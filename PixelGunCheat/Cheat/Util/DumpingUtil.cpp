#include "DumpingUtil.h"

#include <fstream>
#include <iostream>
#include <map>

#include "ClientUtil.h"
#include "IL2CPPUtil.h"
#include "../Internal/Functions.h"
#include "../Logger/Logger.h"

std::map<std::string, int> enum_OfferItemType = {
    { "None",                 0    },
    { "Weapons",              10   },
    { "Armor",                20   },
    { "Mask",                 30   },
    { "Hat",                  40   },
    { "Boots",                50   },
    { "Cape",                 60   },
    { "Skin",                 65   },
    { "Gadget",               70   },
    { "Pet",                  80   },
    { "Egg",                  83   },
    { "LobbyItem",            85   },
    { "FortItem",             90   },
    { "Gems",                 1000 },
    { "Coins",                1010 },
    { "Leprechaun",           1020 },
    { "WeaponUpgrade",        1030 },
    { "GachaFreeSpin",        1040 },
    { "EventCurrency",        1050 },
    { "VIP",                  1060 },
    { "Parts",                1070 },
    { "Royale",               1080 },
    { "BattlePassLevel",      1090 },
    { "BattlePassExp",        1100 },
    { "BattlePassCurrency",   1110 },
    { "GoldenSkin",           1120 },
    { "EventChest",           1130 },
    { "CraftCurrency",        1140 },
    { "Module",               1150 },
    { "ModulePoint",          1155 },
    { "ModuleChest",          1160 },
    { "WeaponSkin",           1170 },
    { "ClanCurrency",         1180 },
    { "Coupons",              1190 },
    { "Currency",             1200 },
    { "Character",            1210 },
    { "ClanShields",          1220 },
    { "ClanLootBox",          1230 },
    { "ClanPlaceable",        1240 },
    { "ClanPlaceablePoint",   1250 },
    { "Detail",               1300 },
    { "WeaponLevelUpgrade",   1310 },
    { "PlayerBuff",           1320 },
    { "ClanBuff",             1330 },
    { "WeaponQualityUpgrade", 1340 },
    { "ArmorSkin",            1350 },
    { "ClanBuilding",         1360 },
    { "ClanBuildingPoint",    1370 },
    { "FreeUpgrade",          1380 },
    { "Chest",                1390 },
    { "Exp",                  1400 },
    { "Stats",                1410 },
    { "ModeSlots",            1420 },
    { "Executable",           1430 },
    { "Tank",                 1440 },
    { "VIP20",                1450 },
    { "LootBox",              1460 },
    { "Graffiti",             1470 },
    { "PixelPassExp",         1490 },
    { "ClanRankExperience",   1500 },
    { "WearSkin",             1510 },
    { "Applicable",           1520 },
    { "CraftSet",             1530 },
    { "FeatureExp",           1540 },
    { "PackagedItem",         1550 },
    { "Achievement",          1560 },
    { "ExpirySimple",         1570 },
    { "Static",               1580 },
    { "GemsHarvester",        1590 },
};

void DumpingUtil::DumpItemRecords()
{
    Logger::log_debug("Dumping Records");
    auto dict = (IL2CPPUtil::il2cppDictionary<IL2CPPUtil::System_String*, void*>*)Functions::GetItemRecordDict();
    std::cout << &dict << std::endl;
    std::cout << dict->m_iCount << std::endl;
    for (int i = 0; i < dict->m_iCount; ++i)
    {
        IL2CPPUtil::System_String* key = dict->GetKeyByIndex(i);
        // wprintf(key->m_wString);
        // wprintf(L"\n");
        std::cout << key->ToString() << std::endl;
    }
    Logger::log_debug("Dumping Finished");
}

void DumpingUtil::DumpFullRecordList()
{
    FILE* file;
    fopen_s(&file, "latest_OfferItemType_dump.txt", "w+");
    std::ofstream out(file);
    
    for (auto entry : enum_OfferItemType)
    {
        auto name = entry.first;
        auto dict = (IL2CPPUtil::il2cppList<IL2CPPUtil::System_String*>*)Functions::GetDataList(Functions::GetDataListStaticInstance(), entry.second);
        Logger::log_info("[Universal Dumper] Dumping Records of Type '" + name + "' (Estimated Size: " + std::to_string(dict->m_pListArray->m_uMaxLength) + ")");
        out << "[Universal Dumper] Dumping Records of Type '" + name + "' (Estimated Size: " + std::to_string(dict->m_pListArray->m_uMaxLength) + ")" << std::endl;
        int real_size = 0;

        for (int i = 0; i < dict->m_pListArray->m_uMaxLength; ++i)
        {
            IL2CPPUtil::System_String* key = dict->m_pListArray->At(i);
            if (key == nullptr) break;
            out << ClientUtil::CleanString(key->ToString()) << std::endl;
            real_size++;
        }

        Logger::log_warn("[Universal Dumper] Record of Type '" + name + "' End-of-List (Real Size: " + std::to_string(real_size) + ")");
        out << "[Universal Dumper] Record of Type '" + name + "' End-of-List (Real Size = " + std::to_string(real_size) + ")" << std::endl;
    }
    
    Logger::log_info("[Universal Dumper] Dumping Finished");
    out << "[Universal Dumper] Dumping Finished" << std::endl;
    fclose(file);
}