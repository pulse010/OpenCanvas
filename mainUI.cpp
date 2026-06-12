#include "mainUI.h"
#include "imGui/imgui.h"
#include "imGui/imgui.h"
#include "glfw/include/GLFW/glfw3.h"
#include "glfw/include/GLFW/glfw3native.h"

bool show_new_project_window = false;

//=======================================================================
//  M   A   I   N      M   E   N   U      F   U   N   C   T   I   O   N
//=======================================================================
void MainMenuBar(GLFWwindow* window)
{
    if (ImGui::BeginMainMenuBar())
    {
        // ==========
        // FILE MENU
        // ==========
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New...")) {
                show_new_project_window = true;
            }
            if (ImGui::MenuItem("Open...")) {}
            if (ImGui::MenuItem("Open As...")) {}
            ImGui::EndMenu();
        }

        // ==========
        // EDIT MENU
        // ==========
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



        //=========================
        //HORIZONTAL OPTIONS
        //=========================

        float rightSideOffset = ImGui::GetWindowWidth() - 100.0f;
        ImGui::SameLine(rightSideOffset);

        if (ImGui::Button("_", ImVec2(25, 20))) {
            glfwIconifyWindow(window);
        }

        static bool isMaximized = false;
        if (ImGui::Button("[ ]", ImVec2(25,20))){
            if (!isMaximized){
                glfwMaximizeWindow(window);
                isMaximized = true;
            } else {
                glfwRestoreWindow(window);
                isMaximized = false;
            }
        }

        if (ImGui::Button("X", ImVec2(25, 20))){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }



        ImGui::EndMainMenuBar();
    }
}

//===========================================================================
// H  A  N  D  L  E    W  I  N  D  O  W    D  R  A  G  G  I  N  G
//===========================================================================
void HnadleWindowDragging(GLFWwindow* window){
    static bool isDragging = false;
    static int mouseStartX, mouseStartY;
    static int windowStartX, windowStartY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (!isDragging && mouseY >= 0 && mouseY <= 25) {
            isDragging = true;

            double globalMouseX, globalMouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            glfwGetWindowPos(window, &windowStartX, &windowStartY);

            mouseStartX = (int)mouseX;
            mouseStartY = (int)mouseY;
        }

        if (isDragging) {
            double currentMouseX, currentMouseY;
            glfwGetCursorPos(window, &currentMouseX, &currentMouseY);

            int deltaX = (int)currentMouseX - mouseStartX;
            int deltaY = (int)currentMouseY - mouseStartY;

            int currentWinX, currentWinY;
            glfwGetCursorPos(window, &currentMouseX, &currentMouseY);
            glfwSetWindowPos(window, currentWinX + deltaX, currentWinY + deltaY);
        }
    } else{
        isDragging = false;
    }
}


//================================================================
//  T   O   O   L   B   A   R      F   U   N   C   T   I   O   N
//================================================================
void ShowFixedToolBar(ToolType& currentTool)
{
    
    ImGuiViewport* viewport = ImGui::GetMainViewport();


    float menuOffset = 25.0f;

    float startX = viewport->Pos.x;
    float startY = viewport->Pos.y + menuOffset;
    ImGui::SetNextWindowPos(ImVec2(startX, startY));

    float width = 60.0f;
    float height = viewport->Size.y - menuOffset;
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove 
                                  | ImGuiWindowFlags_NoResize 
                                  | ImGuiWindowFlags_NoCollapse 
                                  | ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("FixedToolBar", nullptr, window_flags);

    ImVec2 buttonSize(41.5f, 41.5f);

    //==========================================================
    // --- BUTTON 1: MOVE
    //==========================================================
    bool isMoveActive = (currentTool == TOOL_MOVE);

    if (currentTool == TOOL_MOVE) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f)); // Green highlight
    }
    if (ImGui::Button("Move", buttonSize)) {
        currentTool = TOOL_MOVE; // Change global state when clicked
    }
    if (isMoveActive) ImGui::PopStyleColor(); // Clean up color

    ImGui::Spacing();

    //==========================================================
    // --- BUTTON 2: BRUSH ---
    //==========================================================
    bool isBrushActive = (currentTool == TOOL_BRUSH);

    if (currentTool == TOOL_BRUSH) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
    }
    if (ImGui::Button("Brush", buttonSize)) {
        currentTool = TOOL_BRUSH;
    }
    if (isBrushActive) ImGui::PopStyleColor();

    ImGui::Spacing();

    //==========================================================
    // --- BUTTON 3: ERASER ---
    //==========================================================
    bool isEraserActive = (currentTool == TOOL_ERASER);

    if (currentTool == TOOL_ERASER) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
    }
    if (ImGui::Button("Erase", buttonSize)) {
        currentTool = TOOL_ERASER;
    }
    if (isEraserActive) ImGui::PopStyleColor();

    ImGui::End();
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