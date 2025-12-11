// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"

class UTWindow 
{
public:
    UTWindow(const std::string& Title, int Width, int Height);
    virtual ~UTWindow();
    virtual void Initialize();
    virtual void NewFrame();
    virtual void RenderDrawData();
    
    bool ShouldClose() const;
    bool IsVisible() const;
    bool IsFocused() const;
    bool IsMinimized() const;
    
    GLFWwindow* GetGLFWWindow() const;

private:
    GLFWwindow* GLFWWindow;
    std::string Title;
    int Width;
    int Height;
	static bool gladInitialized;
};