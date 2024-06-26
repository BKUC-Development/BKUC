﻿#include "UIHooks.h"

#include <d3d11.h>
#include <filesystem>
#include <imgui.h>
#include <imgui_impl_dx10.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <sstream>
#include <thread>

#include "../Logger/Logger.h"
#include "../Module/BKUCModule.h"
#include "../Util/ClientUtil.h"

ImVec4 ImVec4i(const int r, const int g, const int b, const int a = 255)
{
    return { (float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f };
}

void LoadBKCCBaseTheme()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4i(20, 20, 20);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4i(255, 180, 230);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4i(255, 180, 230, 140);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4i(255, 180, 230, 100);
    colors[ImGuiCol_FrameBgActive]          = ImVec4i(255, 180, 230, 170);
    colors[ImGuiCol_TitleBg]                = ImVec4i(15, 15, 15);
    colors[ImGuiCol_TitleBgActive]          = ImVec4i(255, 180, 230);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4i(15, 15, 15);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4i(255, 180, 230);
    colors[ImGuiCol_SliderGrab]             = ImVec4i(255, 180, 230);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4i(255, 180, 230);
    colors[ImGuiCol_Button]                 = ImVec4i(255, 180, 230, 100);
    colors[ImGuiCol_ButtonHovered]          = ImVec4i(255, 180, 230, 170);
    colors[ImGuiCol_ButtonActive]           = ImVec4i(255, 180, 230);
    colors[ImGuiCol_Header]                 = ImVec4i(255, 180, 230, 80);
    colors[ImGuiCol_HeaderHovered]          = ImVec4i(255, 180, 230, 205);
    colors[ImGuiCol_HeaderActive]           = ImVec4i(255, 180, 230);
    colors[ImGuiCol_Separator]              = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4i(255, 255, 175);
    colors[ImGuiCol_SeparatorActive]        = ImVec4i(255, 255, 255);
    colors[ImGuiCol_ResizeGrip]             = ImVec4i(255, 180, 230, 50);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4i(255, 180, 230, 170);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4i(255, 180, 230, 240);
    colors[ImGuiCol_Tab]                    = ImVec4i(255, 180, 230, 220);
    colors[ImGuiCol_TabHovered]             = ImVec4i(255, 180, 230, 205);
    colors[ImGuiCol_TabActive]              = ImVec4i(255, 180, 230);
    colors[ImGuiCol_TabUnfocused]           = ImVec4i(100, 50, 80);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4i(175, 75, 140, 255);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style->WindowTitleAlign         = ImVec2(1.0f, 0.5f);
    style->WindowMenuButtonPosition = ImGuiDir_Right;
    style->SeparatorTextAlign       = ImVec2(0.5f, 0.5f);
    style->DisplaySafeAreaPadding   = ImVec2(4, 4);
    
    style->WindowPadding     = ImVec2(4.00f, 4.00f);
    style->FramePadding      = ImVec2(4.00f, 1.00f);
    style->CellPadding       = ImVec2(2.00f, 2.00f);
    style->ItemSpacing       = ImVec2(6.00f, 4.00f);
    style->ItemInnerSpacing  = ImVec2(4.00f, 0.00f);
    style->TouchExtraPadding = ImVec2(0.00f, 0.00f);
    
    style->IndentSpacing     = 12;
    style->ScrollbarSize     = 10;
    style->GrabMinSize       = 6;
    
    style->WindowRounding    = 4;
    style->ChildRounding     = 0;
    style->FrameRounding     = 2;
    style->PopupRounding     = 0;
    style->ScrollbarRounding = 12;
    style->GrabRounding      = 12;
    style->LogSliderDeadzone = 2;
    style->TabRounding       = 2;

    style->ChildBorderSize         = 0;
    style->FrameBorderSize         = 0;
    style->PopupBorderSize         = 0;
    style->TabBorderSize           = 0;
    style->WindowBorderSize        = 1;
    style->TabBarBorderSize        = 0;
    style->SeparatorTextBorderSize = 1;
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

void* imgui_handle;
float scale_factor;

static ImU32 color_title = ImGui::ColorConvertFloat4ToU32(ImVec4i(255, 180, 230));
std::string current_font = "C:/Windows/Fonts/micross.ttf";

ImFont* gui_font;
ImFont* watermark_font;
ImFont* arraylist_font;

void UIHooks::UnloadImGui(bool is_dx_11)
{
    if (is_dx_11)
    {
        ImGui_ImplDX11_InvalidateDeviceObjects();
        ImGui_ImplDX11_Shutdown();
    }
    else
    {
        ImGui_ImplDX10_InvalidateDeviceObjects();
        ImGui_ImplDX10_Shutdown();
    }
    
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UIHooks::SetUpImGuiWindow(void* handle, void* device, void* device_context, bool is_dx_11)
{
    Logger::log_info("Setting up ImGui...");
    imgui_handle = handle;
    std::string title = "boykisser.cc v2.6"; // hardcode for now...
    
    IMGUI_CHECKVERSION();
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // Load Theme
    LoadBKCCBaseTheme();
    
    ImGui_ImplWin32_Init(imgui_handle);
    
    if (is_dx_11) ImGui_ImplDX11_Init((ID3D11Device*)device, (ID3D11DeviceContext*)device_context);
    else ImGui_ImplDX10_Init((ID3D10Device*)device);
    
    int horizontal = 0;
    int vertical = 0;
    
    GetDesktopResolution(horizontal, vertical);

    scale_factor = ((float)horizontal / 1920.0f + (float)vertical / 1080.0f) / 2.0f;
    std::stringstream multi_out;
    multi_out << "Using " << scale_factor << "x scale factor for ImGui fonts";
    Logger::log_info(multi_out.str());

    if (!std::filesystem::exists(current_font)){
        for (const auto &entry : std::filesystem::directory_iterator("C:/Windows/Fonts/")){
            if (entry.path().extension() == ".ttf"){
                current_font = entry.path().string();
                break;
            }
        }
    }
    
    gui_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
    watermark_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
    arraylist_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
}

void DrawClientSettingsWindow(bool is_dx_11)
{
    /*
    if (ImGui::BeginCombo("Font", current_font.c_str()))
    {
        for (std::string::size_type i = 0; i < fonts.size(); i++)
        {
            const bool selected = current_font == fonts[i];
                
            if (ImGui::Selectable(fonts[i].c_str(), selected))
            {
                current_font = fonts[i];
                ImGuiIO& io = ImGui::GetIO(); (void) io;
                gui_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
                watermark_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
                arraylist_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
                io.Fonts->Build();
                
                // force invalidation and new frames
                if (is_dx_11)
                {
                    ImGui_ImplDX11_InvalidateDeviceObjects();
                    ImGui_ImplDX11_NewFrame(); 
                }
                else
                {
                    ImGui_ImplDX10_InvalidateDeviceObjects();
                    ImGui_ImplDX10_NewFrame();
                }
                
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();
                Logger::log_info("Changed client font to " + current_font);
                return;
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }
    */

    bool test = false;
    ImGui::Checkbox("Boundless Sliders", &test);

    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Allow setting values on sliders below or above minimum and maximum when manually changing them (CTRL Clicking)");
    }
        
    if (ImGui::CollapsingHeader("Runtime Hooks (Dev)"))
    {
        /*
        ImGui::Indent();
            
        ImGui::InputText("Offset##rhd", offsets_rhd, sizeof(offsets_rhd));
        ImGui::InputText("Return##rhd", return_rhd, sizeof(return_rhd));
        ImGui::Checkbox("Float##rhd", &rhd_is_float);
        if (ImGui::Button("Create##rhd"))
        {
            try_runtime_hook();
        }
            
        ImGui::Unindent();
        */
    }

    if (ImGui::Button("Dump Item Records (Dev)"))
    {
        // Hooks::dump_item_records();
    }

    ImGui::SameLine();
    
    if (ImGui::Button("Dump All Records (Dev)"))
    {
        // Hooks::dump_all_records();
    }

    if (ImGui::Button("Send Test Notification"))
    {
        /*
        ModuleNotifications::add_notification("Force Rejoin", "Detected a disconnection, trying to force rejoin... " + std::to_string(count), 3000);
        count++;
        */
    }
}

void DrawConfigsWindow(bool is_dx_11)
{
    /*
    ImGui::InputText("##config_text", input_file, sizeof(input_file));
    ImGui::SameLine();
    
    if (ImGui::Button("Create New##config"))
    {
        save_config(input_file);
        combo_file = input_file;
    }

    std::vector<std::string> files = get_config_names();

    if (ImGui::BeginCombo("##config_combo", combo_file.c_str()))
    {
        for (std::string::size_type i = 0; i < files.size(); i++)
        {
            const bool selected = combo_file == files[i];

            if (ImGui::Selectable(files[i].c_str(), selected))
            {
                combo_file = files[i];
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }
        
    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        load_config(combo_file.c_str());
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        save_config(combo_file.c_str());
    }
    */
} 

std::string unwiden_string(std::wstring wide)
{
    return std::string(wide.begin(), wide.end());
}

void HandleModuleSettingRendering(BKUCModule& module)
{
    std::string last_separator;
    
    for (auto& setting : module.settings)
    {
        if (setting->category != last_separator)
        {
            ImGui::SeparatorText(("Settings: " + setting->category).c_str());
            last_separator = setting->category;
        }

        if (!BKUCModuleUtil::are_parents_enabled(setting)) continue;
        
        std::stringstream per_module_name;
        
        if (setting->type == 1)
        {
            auto* checkbox = (BKUCCheckbox*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::Checkbox(per_module_name.str().c_str(), &checkbox->checked);
        }
        else if (setting->type == 2)
        {
            auto* slider = (BKUCSlider*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::SliderFloat(per_module_name.str().c_str(), &slider->current, slider->min, slider->max);
            if (true) slider->current = std::ranges::clamp(slider->current, slider->min, slider->max);
        }
        else if (setting->type == 3)
        {
            auto* slider = (BKUCSliderInt*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::SliderInt(per_module_name.str().c_str(), &slider->current, slider->min, slider->max);
            if (true) slider->current = std::ranges::clamp(slider->current, slider->min, slider->max);
        }
        else if (setting->type == 4)
        {
            std::stringstream search;
            auto* dropdown = (BKUCDropdown*)setting;
            search << "Search..." << "##" << setting->name << module.name << setting->type;
            per_module_name << setting->name << "##" << module.name << setting->type;
            if (ImGui::BeginCombo(per_module_name.str().c_str(), unwiden_string(dropdown->current).c_str()))
            {
                if (dropdown->allow_search)
                {
                    ImGui::InputText(search.str().c_str(), dropdown->search_string, sizeof(dropdown->search_string));
                }
                
                for (std::string::size_type i = 0; i < dropdown->values.size(); i++)
                {
                    if (!dropdown->allow_search || ClientUtil::StrLow(unwiden_string(dropdown->values[i])).find(ClientUtil::StrLow(dropdown->search_string)) != std::string::npos)
                    {
                        const bool selected = dropdown->current == dropdown->values[i];
                    
                        if (ImGui::Selectable(unwiden_string(dropdown->values[i]).c_str(), selected))
                        {
                            dropdown->current = dropdown->values[i];
                            dropdown->current_index = dropdown->indexof(dropdown->current);
                        }
                        if (selected) ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
        }

        if (!setting->description.empty())
        {
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(setting->description.c_str());
            }
        }
    }
}

void HandleModuleRendering(BKUCModule& module)
{
    const bool collapsing = ImGui::CollapsingHeader(module.name.c_str());
    if (ImGui::IsItemHovered()) ImGui::SetTooltip(module.description.c_str());
    if (collapsing)
    {
        std::stringstream module_enabled_id;
        module_enabled_id << "Enabled##" << module.name;
        ImGui::Indent();
        ImGui::SeparatorText("Active Status");
        ImGui::Checkbox(module_enabled_id.str().c_str(), &module.enabled);
        HandleModuleSettingRendering(module);
        ImGui::Unindent();
    }
}


void HandleCategoryRendering(const std::string& name, const UIHooksCategory cat)
{
    for (const auto& module : BKUCModule::modules)
    {
        if (module->category != cat) continue;
        HandleModuleRendering(*module);
    }
    
    /*
    if (ImGui::CollapsingHeader(name.c_str()))
    {
        // inner
    }
    */
}

void UIHooks::StartImGui(void* g_mainRenderTargetView, void* g_pd3dDevice, void* g_pd3dDeviceContext, bool is_dx_11)
{
    while (gui_font == nullptr || watermark_font == nullptr || arraylist_font == nullptr)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    /*
    // Load Config
    if (modules_loaded && !config_loaded)
    {
        config_loaded = true;
        load_config("default");
        save_config("default");
        Logger::log_info("Loaded default config!");
    }
    */
    
    // NOTE: Make this not suck
    if (ClientUtil::has_font_changed)
    {
        ClientUtil::has_font_changed = false;
        ImGuiIO& io2 = ImGui::GetIO(); (void) io2;
        
        if (!std::filesystem::exists(current_font))
        {
            for (const auto &entry : std::filesystem::directory_iterator("C:/Windows/Fonts/"))
            {
                if (entry.path().extension() == ".ttf")
                {
                    current_font = entry.path().string();
                    break;
                }
            }
        }
        
        gui_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
        watermark_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
        arraylist_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
        io2.Fonts->Build();
        
        // force invalidation and new frames
        if (is_dx_11)
        {
            ImGui_ImplDX11_InvalidateDeviceObjects();
            ImGui_ImplDX11_NewFrame();
        }
        else
        {
            ImGui_ImplDX10_InvalidateDeviceObjects();
            ImGui_ImplDX10_NewFrame();
        }
        
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        Logger::log_info("Changed client font to " + current_font);
        return;
    }

    /*
    if (GlobalModuleDeclarations::hud_customizer_module != nullptr
        && ((ModuleBase*)GlobalModuleDeclarations::hud_customizer_module)->is_enabled()
        && GlobalModuleDeclarations::hud_customizer_module->apply_to_full_gui()) UpdateColorsByTheme();
        */
    
    // Start the Dear ImGui frame
    if (is_dx_11) ImGui_ImplDX11_NewFrame();
    else ImGui_ImplDX10_NewFrame();

    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    ImGui::PushFont(gui_font);
    
    if (ClientUtil::ui_hooks_render)
    {
        ImGui::Begin(ClientUtil::client_name.c_str(), nullptr);

        if (ImGui::Button("General")) ClientUtil::window_display = 0;
        ImGui::SameLine();
        if (ImGui::Button("Combat")) ClientUtil::window_display = 1;
        ImGui::SameLine();
        if (ImGui::Button("Visual")) ClientUtil::window_display = 2;
        ImGui::SameLine();
        if (ImGui::Button("Movement")) ClientUtil::window_display = 3;
        ImGui::SameLine();
        if (ImGui::Button("Player")) ClientUtil::window_display = 4;
        ImGui::SameLine();
        if (ImGui::Button("Exploit")) ClientUtil::window_display = 5;
        ImGui::SameLine();
        if (ImGui::Button("Configs")) ClientUtil::window_display = 6;
        ImGui::SameLine();
        if (ImGui::Button("Settings")) ClientUtil::window_display = 7;

        switch (ClientUtil::window_display)
        {
        case 0:
            HandleCategoryRendering("General", GENERAL);
            break;
        case 1:
            HandleCategoryRendering("Combat", COMBAT);
            break;
        case 2:
            HandleCategoryRendering("Visual", VISUAL);
            break;
        case 3:
            HandleCategoryRendering("Movement", MOVEMENT);
            break;
        case 4:
            HandleCategoryRendering("Player", PLAYER);
            break;
        case 5:
            HandleCategoryRendering("Exploit", EXPLOIT);
            break;
        case 6:
            DrawConfigsWindow(is_dx_11);
            break;
        case 7:
            DrawClientSettingsWindow(is_dx_11);
            break;
        default:
            ImGui::Text("Welcome to boykisser.cc (BKUC), Happy Modding!");
            ImGui::SameLine();
            ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "<3");
            ImGui::Text("Please select a category above to use the menu...");
            break;
        }
        
        ImGui::End();

        // ENABLE THIS FOR EASILY FINDING WHAT YOU NEED TO ADD TO THE GUI
        // ImGui::ShowDemoWindow();

        /*
        if (show_client_settings) DrawClientSettingsWindow(is_dx_11);
        if (show_configs) DrawConfigsWindow(is_dx_11);
        */
    }

    /*
    // Modules
    Hooks::draw_all();
    */
    
    for (const auto module : BKUCModuleUtil::get_modules_of_type(GUI_2D_RENDER))
    {
        module->run(nullptr);
    } 
    
    ImGui::PopFont(); 

    // Watermark
    ImGui::PushFont(watermark_font);
    const float size = ImGui::GetFontSize();
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 9,  4 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 0.5f }), ClientUtil::client_name.c_str());
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 9,  6 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 0.5f }), ClientUtil::client_name.c_str());
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 11, 4 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 0.5f }), ClientUtil::client_name.c_str());
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 11, 6 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 0.5f }), ClientUtil::client_name.c_str());
    // if (GlobalModuleDeclarations::hud_customizer_module != nullptr && ((ModuleBase*)GlobalModuleDeclarations::hud_customizer_module)->is_enabled()) ImGui::GetBackgroundDrawList()->AddText(nullptr, size, {10, 5}, GlobalModuleDeclarations::hud_customizer_module->get_color_scheme(ClientUtil::color_prog_offset), ClientUtil::client_name.c_str());
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 10, 5 }, color_title, ClientUtil::client_name.c_str());
    ImGui::PopFont();
    
    ImGui::Render();

    if (is_dx_11)
    {
        auto view = (ID3D11RenderTargetView*)g_mainRenderTargetView;
        ((ID3D11DeviceContext*)g_pd3dDeviceContext)->OMSetRenderTargets(1, &view, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        auto view = (ID3D10RenderTargetView*)g_mainRenderTargetView;
        ((ID3D10Device*)g_pd3dDevice)->OMSetRenderTargets(1, &view, nullptr);
        ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());
    }
}