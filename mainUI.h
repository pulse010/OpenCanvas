#pragma once

extern bool show_new_project_window; 

struct GLFWwindow;

enum ToolType {
    TOOL_MOVE,
    TOOL_BRUSH,
    TOOL_ERASER,
    TOOL_BUCKET
};

void MainMenuBar(GLFWwindow* window);
void NewFile();
void ShowFixedToolBar(ToolType& currentTool);
void HnadleWindowDragging(GLFWwindow* window);
