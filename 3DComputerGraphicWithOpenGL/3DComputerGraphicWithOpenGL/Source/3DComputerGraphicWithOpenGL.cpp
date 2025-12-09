// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once


#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#include <GLFW/glfw3.h>
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include <GL/freeglut_std.h>

// should be last include
#include "stb_image.h"

void UpdateManager()
{
	RESOURCE_MANAGER->Update();
}

int main(int argc, char** argv)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	IMGUI_CHECKVERSION();

	WINDOW_MANAGER->CreateMainWindow();
	WINDOW_MANAGER->CreateOutputWindow();

	glfwMakeContextCurrent(MAIN_WINDOW->GetGLFWWindow());
	
	ImGui::SetCurrentContext(MAIN_WINDOW->GetGuiContext());
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui_ImplGlfw_InitForOpenGL(MAIN_WINDOW->GetGLFWWindow(), true);
	ImGuiIO& io = ImGui::GetIO();
	DefaultFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 16.f, NULL, io.Fonts->GetGlyphRangesKorean());
	MediumFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 24.f, NULL, io.Fonts->GetGlyphRangesKorean());
	BigFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 32.f, NULL, io.Fonts->GetGlyphRangesKorean());
	MonospaceFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\cour.ttf", 16.f, NULL, io.Fonts->GetGlyphRangesKorean());

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
	while (MAIN_WINDOW->ShouldClose() == false)
	{
		UpdateManager();
		glfwPollEvents();
		
		MAIN_WINDOW->NewFrame();
		MAIN_WINDOW->RenderUI();
		MAIN_WINDOW->RenderDrawData();
	
		if (OUTPUT_WINDOW)
		{
			if (OUTPUT_WINDOW->ShouldClose() == false)
			{
				OUTPUT_WINDOW->NewFrame();
				OUTPUT_WINDOW->RenderDrawData();
			}
			else
			{
				WINDOW_MANAGER->HideOutputWindow();
			}
		}
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	
	WINDOW_MANAGER->DestroyMainWindow();
	WINDOW_MANAGER->DestroyOutputWindow();

	return 0;
}