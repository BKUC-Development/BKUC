#pragma once

#include <any>
#include <map>
#include <string>
#include "../Util/ClientUtil.h"

class BKUCSetting;
enum ParentState
{
    EQUAL,
    EQUAL_IGNORE_CASE,
    LESS_THAN,
    MORE_THAN,
    RANGE
};

struct ParentalConstraint
{
    BKUCSetting* parent;
    ParentState state;
    std::any constraint;
};

class BKUCSetting
{
public:
    std::string name;
    std::string description;
    std::string category;
    std::vector<ParentalConstraint> parents;
    int type = -1;
};

class BKUCCheckbox : public BKUCSetting
{
public:
    BKUCCheckbox(const std::string& _name, const bool checked, const std::string& _description = "")
    {
        this->name = _name;
        this->checked = checked;
        this->description = _description;
        this->category = "General";
        this->type = 1;
    }

    bool checked;
};

class BKUCSlider : public BKUCSetting
{
public:
    BKUCSlider(const std::string& _name, const float _default, const float _min, const float _max, const std::string& _description = "")
    {
        this->name = _name;
        this->current = _default;
        this->min = _min;
        this->max = _max;
        this->description = _description;
        this->category = "General";
        this->type = 2;
    }

    float current;
    float min;
    float max;
};

class BKUCSliderInt : public BKUCSetting
{
public:
    BKUCSliderInt(const std::string& _name, const int _default, const int _min, const int _max, const std::string& _description = "")
    {
        this->name = _name;
        this->current = _default;
        this->min = _min;
        this->max = _max;
        this->description = _description;
        this->category = "General";
        this->type = 3;
    }

    int current;
    int min;
    int max;
};

class BKUCDropdown : public BKUCSetting
{
public:
    BKUCDropdown(const std::string& _name, const std::wstring& _default, const std::vector<std::wstring>& _values, const bool _allow_search, const std::string& _description = "")
    {
        this->name = _name;
        this->current = _default;
        this->current_index = indexof(_default);
        this->values = _values;
        this->allow_search = _allow_search;
        this->description = _description;
        this->category = "General";
        this->type = 4;
    }

    int indexof(const std::wstring& val)
    {
        const auto indexer = std::ranges::find(values, val);
        return indexer != values.end() ? (int)(indexer - values.begin()) : -1;
    }

    std::wstring current;
    int current_index;
    std::vector<std::wstring> values;

    char* search_string;
    bool allow_search;
};

class BKUCModule
{
public:
    static inline std::vector<BKUCModule*> modules = {};
    
    BKUCModule(const std::string& name, const std::string& description, bool enabled, const UIHooksCategory category, const int key, const std::vector<BKUCSetting*>& settings)
    {
        this->name = name;
        this->description = description;
        this->enabled = enabled;
        this->category = category;
        this->key = key;
        this->settings = settings;
        modules.push_back(this);
    }

    std::string name;
    std::string description;
    bool enabled;
    UIHooksCategory category;
    int key;
    std::vector<BKUCSetting*> settings;

    void run(void* arg)
    {
        if (enabled) exec(arg);
    }
    
    virtual void exec(void* arg) = 0;
protected:
    static void set_bool(void* arg, uint64_t offset, bool value)
    {
        *(bool*)((uint64_t)arg + offset) = value;
    }

    static void set_float(void* arg, uint64_t offset, float value)
    {
        *(float*)((uint64_t)arg + offset) = value;
    }

    static void set_int(void* arg, uint64_t offset, int value)
    {
        *(int*)((uint64_t)arg + offset) = value;
    }

    static void* get_void(void* arg, uint64_t offset)
    {
        return (void*)((uint64_t)arg + offset);
    }

    static bool get_bool(void* arg, uint64_t offset)
    {
        return *(bool*)((uint64_t)arg + offset);
    }

    static float get_float(void* arg, uint64_t offset)
    {
        return *(float*)((uint64_t)arg + offset);
    }

    static int get_int(void* arg, uint64_t offset)
    {
        return *(int*)((uint64_t)arg + offset);
    }
    
};

enum BKUCModuleInvocationType
{
    PLAYER_MOVE_C,
    PLAYER_DAMAGEABLE,
    WEAPON_SOUNDS,
    PRE_RENDER,
    GUI_2D_RENDER
};

class BKUCModuleUtil
{
public:
    static inline std::map<BKUCModuleInvocationType, std::vector<BKUCModule*>> module_invocation_map = {};

    static void add_module_to_map(const BKUCModuleInvocationType type, BKUCModule* module)
    {
        std::vector<BKUCModule*> map_modules;
        
        if (!module_invocation_map.contains(type))
        {
            map_modules = std::vector<BKUCModule*>();
            map_modules.push_back(module);
            module_invocation_map.insert_or_assign(type, map_modules);
        }

        map_modules = module_invocation_map[type];
        map_modules.push_back(module);
        module_invocation_map.insert_or_assign(type, map_modules);
    }

    static std::vector<BKUCModule*> get_modules_of_type(const BKUCModuleInvocationType type)
    {
        if (!module_invocation_map.contains(type)) return {};
        return module_invocation_map[type];
    }
    
    static bool are_parents_enabled(const BKUCSetting* current)
    {
        if (current->parents.empty()) return true;
        
        for (const auto& constraint : current->parents)
        {
            const auto setting = constraint.parent;

            // recursive check (check for crashes lol)
            if (!are_parents_enabled(setting)) return false;

            const auto state = constraint.state;
            auto data = constraint.constraint;
            
            switch (setting->type)
            {
            case 1:
            {
                const auto* checkbox = (BKUCCheckbox*)setting;
                auto applicable_status = std::any_cast<bool>(data);
                if (state != EQUAL || (checkbox->checked && !applicable_status) || (!checkbox->checked && applicable_status)) return false;
                break;
            }
            case 2:
            {
                const auto* slider = (BKUCSlider*)setting;
                std::pair<float, float> applicable_status;
                
                if (state != RANGE) applicable_status = std::pair(std::any_cast<float>(data), std::any_cast<float>(data));
                else applicable_status = std::any_cast<std::pair<float, float>>(data);
                
                switch (state)
                {
                case EQUAL_IGNORE_CASE:
                case EQUAL: { if (slider->current != applicable_status.first) return false; break; }
                case LESS_THAN: { if (slider->current > applicable_status.first) return false; break; }
                case MORE_THAN: { if (slider->current < applicable_status.first) return false; break; }
                case RANGE: { if (slider->current < applicable_status.first || slider->current > applicable_status.second) return false; }
                }

                break;
            }
            case 3:
            {
                const auto* slider = (BKUCSliderInt*)setting;
                std::pair<int, int> applicable_status;
                
                if (state != RANGE) applicable_status = std::pair(std::any_cast<int>(data), std::any_cast<int>(data));
                else applicable_status = std::any_cast<std::pair<int, int>>(data);
                
                switch (state)
                {
                case EQUAL_IGNORE_CASE:
                case EQUAL: { if (slider->current != applicable_status.first) return false; break; }
                case LESS_THAN: { if (slider->current > applicable_status.first) return false; break; }
                case MORE_THAN: { if (slider->current < applicable_status.first) return false; break; }
                case RANGE: { if (slider->current < applicable_status.first || slider->current > applicable_status.second) return false; }
                }

                break;
            }
            case 4:
            {
                const auto* dropdown = (BKUCDropdown*)setting;
                auto applicable_status = std::any_cast<std::wstring>(data);
                
                switch (state)
                {
                case EQUAL_IGNORE_CASE: { if (ClientUtil::WStrLow(dropdown->current) == ClientUtil::WStrLow(applicable_status)) return false; break; }
                case EQUAL: { if (dropdown->current == applicable_status) return false; break; }
                case LESS_THAN:
                case MORE_THAN:
                case RANGE:
                    return false;
                }

                break;
            }
            default:
            {
                Logger::log_warn("Invalid setting type");
            }
            }
        }

        return true;
    }
};
