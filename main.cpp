#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include "glfw/include/GLFW/glfw3.h" 
#include <iostream>
#include <string>
// #include <vector>

// Canvas Data
using std::cout;

struct Project {
  std::string name;
  int width;
  int height;
  unsigned int textureID; // OpenGL texture reference
};

// Global Program Settings
struct ApplicationState {
    bool hasActiveProject = false;
    int inputWidth = 800;
    int inputHeight = 600;
};

int main() {
    ApplicationState appState;
    Project currentProject;
    //std::vector<Project> openProjects;
    //int activeProjectIndex = -1;

    char nameBuffer[128] = "Untitled Project";

    // Start up
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "LibrePhoto", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    // Bind ImGui to our specific window and graphics driver
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Loop
    while (!glfwWindowShouldClose(window)) {
        // 1. Check for inputs (mouse clicks, keyboard presses)
        glfwPollEvents();

        // 2. Start a fresh, blank slate for this frame's UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
        
        float windowWidth = ImGui::GetIO().DisplaySize.x;
        
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f));
        
        ImGui::SetNextWindowSize(ImVec2(windowWidth - 20.0f, 40.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 10.0f));

        
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Project")) {
                    appState.hasActiveProject = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        

        /* // 3. Optional Window
        ImGuiWindowFlags menuFlags = ImGuiWindowFlags_NoTitleBar | 
                                     ImGuiWindowFlags_NoResize | 
                                     ImGuiWindowFlags_NoMove | 
                                     ImGuiWindowFlags_NoScrollbar | 
                                     ImGuiWindowFlags_MenuBar;

        // 4. DRAW THE CUSTOM BAR 
        if (ImGui::Begin("TopMenuBarContainer", nullptr, menuFlags)) {
            if (ImGui::BeginMenuBar()) { // Inside a regular window, we use BeginMenuBar
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New Project")) {
                        appState.hasActiveProject = false;
                        // Reset the typing box back to default when they hit New Project
                        strcpy(nameBuffer, "Untitled Project");
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::End(); // Closes "TopMenuBarContainer"
        }*/

        ImGui::PopStyleVar(2);



        if (!appState.hasActiveProject) {
            ImGui::Begin("New Canvas Setup");

            ImGui::InputText("Project Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
            // Pass the RAM address of our width and height variables
            ImGui::InputInt("Width", &appState.inputWidth);
            ImGui::InputInt("Height", &appState.inputHeight);

            if (ImGui::Button("Create Canvas")) {
                currentProject.name = std::string(nameBuffer);
                currentProject.width = appState.inputWidth;
                currentProject.height = appState.inputHeight;
                currentProject.textureID = 0;

                appState.hasActiveProject = true;
            }
            ImGui::End();
        }
        else {
            ImGui::Begin("Properties");
            ImGui::Text("Project Name: %s", currentProject.name.c_str());
            ImGui::Text("Canvas: %d x %d", currentProject.width, currentProject.height);
            ImGui::End();
        }
        
        ImGui::Render(); // Finalizes the frame data
        glClear(GL_COLOR_BUFFER_BIT); // Wipes the window background clear
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Draws it via OpenGL
        glfwSwapBuffers(window);
    }

    cout << "DEBUG: Successfully reached the render block!\n";

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}