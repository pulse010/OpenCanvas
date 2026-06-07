#include "mainUI.h"
#include "imgui/imgui.h"
#include <iostream>

bool show_new_project_window = false;

void MainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New...")) {
                show_new_project_window = true;
            }
            if (ImGui::MenuItem("Open...")) {}
            if (ImGui::MenuItem("Open As...")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {} // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void NewFile() {
    if (show_new_project_window) {
        // This allows the user to still drag and resize the window manually afterward.
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

        // You can also optionally set a starting position on the screen (X, Y)
        ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver);  
        
        ImGui::Begin("New File", &show_new_project_window);
        ImGui::Text("NEW FUCKING PROJECT.");
        ImGui::End();
    }
}