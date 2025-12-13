// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "WindowManager.h"

WindowManager* WindowManager::Instance = nullptr;

WindowManager::WindowManager()
	: MainWindow(nullptr)
	, OutputWindow(nullptr)
{
	
}

WindowManager::~WindowManager()
{
	DestroyMainWindow();
	DestroyOutputWindow();
	Destroy();
}

WindowManager* WindowManager::GetWindowManager()
{
	if (Instance == nullptr)
	{
		Instance = new WindowManager();
	}

	return Instance;
}

UTMainWindow* WindowManager::GetMainWindow() const
{
	return MainWindow;
}

UTOutputWindow* WindowManager::GetOutputWindow() const
{
	return OutputWindow;
}

void WindowManager::Destroy()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void WindowManager::CreateMainWindow()
{
	GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
	const int MonitorWidth = Mode->width;
	const int MonitorHeight = Mode->height;
	
	const int MainWindowWidth = MonitorWidth * 5 / 10;
	const int MainWindowHeight = MonitorHeight * 9 / 10;
	
	MainWindow = new UTMainWindow("3D CG With OpenGL by biomatic", MainWindowWidth, MainWindowHeight);
	if(MainWindow == nullptr)
		return;
	
	const int MainWindowPositionX = MonitorWidth * 1 / 10;
	const int MainWindowPositionY = MonitorHeight * 1 / 20;
	glfwSetWindowPos(MainWindow->GetGLFWWindow(), MainWindowPositionX, MainWindowPositionY);
}

void WindowManager::CreateOutputWindow()
{
	GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
	const int MonitorWidth = Mode->width;
	const int MonitorHeight = Mode->height;
	int OutputWindowWidth = MonitorWidth * 3 / 10;
	int OutputWindowHeight = MonitorHeight * 9 / 10;
	OutputWindow = new UTOutputWindow("Output", OutputWindowWidth, OutputWindowHeight);
	if (OutputWindow == nullptr)
		return;

	const int OutputWindowPositionX = MonitorWidth * 6 / 10;
	const int OutputWindowPositionY = MonitorHeight * 1 / 20;
	glfwSetWindowPos(OutputWindow->GetGLFWWindow(), OutputWindowPositionX, OutputWindowPositionY);
	glfwHideWindow(OutputWindow->GetGLFWWindow());
}

void WindowManager::HideOutputWindow(bool bHide)
{
	if(OutputWindow == nullptr)
		return;

	if (bHide)
	{
		glfwHideWindow(OutputWindow->GetGLFWWindow());
	}
	else
	{
		glfwShowWindow(OutputWindow->GetGLFWWindow());
	}
}

void WindowManager::DestroyMainWindow()
{
	if (MainWindow != nullptr)
	{
		delete MainWindow;
		MainWindow = nullptr;
	}
}

void WindowManager::DestroyOutputWindow()
{
	if (OutputWindow != nullptr)
	{
		delete OutputWindow;
		OutputWindow = nullptr;
	}
}

void WindowManager::Update()
{

}