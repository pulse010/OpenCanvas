#pragma once

extern bool show_new_project_window; 

enum ToolType {
    TOOL_MOVE,
    TOOL_BRUSH,
    TOOL_ERASER,
    TOOL_BUCKET
};

void MainMenuBar();
void NewFile();
void ShowFixedToolBar(ToolType& currentTool);
