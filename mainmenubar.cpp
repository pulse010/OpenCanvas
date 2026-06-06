#include "mainmenubar.h"
#include "imgui/imgui.h"
#include <iostream>

bool show_new_project_window = false;

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