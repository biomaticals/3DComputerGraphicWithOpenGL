// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "3DComputerGraphicWithOpenGL.h"
#include "UTWindow.h"
#include <vector>

#define REGISTER_DRAW_FUNCTION(Chapter, CodeIndex) \
	{ \
		if (this->DrawFunctions.size() <= Chapter) \
		{ \
			this->DrawFunctions.resize(Chapter + 1); \
		} \
		if (this->DrawFunctions[Chapter].size() <= CodeIndex) \
		{ \
			this->DrawFunctions[Chapter].resize(CodeIndex + 1); \
		} \
		(this->DrawFunctions)[Chapter][CodeIndex] = &UTOutputWindow::MyDisplay_##Chapter##_##CodeIndex; \
	} \

class UTOutputWindow;

struct FExampleCode
{
	FExampleCode();
	FExampleCode(const std::wstring& InTitle);
	FExampleCode(const std::wstring& InTitle, void (UTOutputWindow::* InDrawFunction)(), void (UTOutputWindow::* InStartDrawFunction)(), void(UTOutputWindow::* InEndDrawFunction)());
	FExampleCode(const FExampleCode& Other);
	~FExampleCode();
	const FExampleCode& operator=(const FExampleCode& Other);
	bool IsValid() const;

	std::wstring Title;
	void (UTOutputWindow::* DrawFunction)() = nullptr;
	void (UTOutputWindow::* StartDrawFunction)() = nullptr;
	void (UTOutputWindow::* EndDrawFunction)() = nullptr;
};

class UTOutputWindow : public UTWindow
{
public:
	UTOutputWindow(const std::string& Title, int Width, int Height);
	virtual ~UTOutputWindow() override;
	void Initialize() override;
	virtual void RenderDrawData() override;

public:
	void SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);
	void ResetAll();

	void DumpGLState(const char* tag = "");
#pragma region Chapter5
private:
	void Code_5_2();

	void Code_5_4();

	void Code_5_5_Start();
	void Code_5_5();
	void Code_5_5_End();
	static void Code_5_5_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight);


	void Code_5_6_Start();
	void Code_5_6();
	void Code_5_6_End();
	static void Code_5_6_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	int Width_5_6;
	int Height_5_6;

	void Code_5_7_Start();
	void Code_5_7();
	void Code_5_7_End();
	static void Code_5_7_MouseButton(GLFWwindow* Window, int button, int action, int mods);
	static void Code_5_7_CursorPosition(GLFWwindow* Window, double xpos, double ypos);
	GLfloat TopLeftX_5_7 = -1;
	GLfloat TopLeftY_5_7 = 1;
	GLfloat BottomRightX_5_7 = 1;
	GLfloat BottomRightY_5_7 = -1;

	void Code_5_13();
	void Code_5_13_End();
	inline static GLfloat Vertices_5_13[8][3]
	{
		{ -0.25f, -0.25f, 0.25f },
		{ -0.25f,  0.25f, 0.25f },
		{  0.25f,  0.25f, 0.25f },
		{  0.25f, -0.25f, 0.25f },
		{ -0.25f, -0.25f, -0.25f },
		{ -0.25f,  0.25f, -0.25f },
		{  0.25f,  0.25f, -0.25f },
		{  0.25f, -0.25f, -0.25f }
	};

	inline static GLfloat Colors_5_13[8][3]
	{
		{ 0.2f, 0.2f, 0.2f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f }
	};

	inline static GLubyte VertexList_5_13[24]
	{
		0, 3, 2, 1,
		2, 3, 7, 6,
		0, 4, 7, 3,
		1, 2, 6, 5,
		4, 5, 6, 7,
		0, 1, 5, 4
	};

	void Code_5_14_Start();
	void Code_5_14();
	void Code_5_14_End();
	GLuint MyListID_5_14;

	void Code_5_15_Start();
	void Code_5_15();
	void Code_5_15_End();
	static void Code_5_15_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight);
	static void Code_5_15_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	static void Code_5_15_MouseButton(GLFWwindow* Window, int button, int action, int mods);
	static void Code_5_15_CursorPosition(GLFWwindow* Window, double xpos, double ypos);
	bool FlatShadeMode_5_15;
	bool WireframeMode_5_15;
	std::vector<Vertex> vertices_5_15;
	std::vector<unsigned int> indices_5_15;
	std::vector<MaterialInfo> materials_5_15;
	GLfloat light_position_5_15[5];
	double cursor_xpos_5_15, cursor_ypos_5_15;
#pragma endregion
//Chapter5

#pragma region Chapter6
private:
	void Code_6_3();
	void Code_6_3_End();
#pragma endregion 
//Chapter6

private:
	using DrawFuncPtr = void (UTOutputWindow::*)();
	std::vector<std::vector<DrawFuncPtr>> DrawFunctions;

	std::vector<std::vector<DrawFuncPtr>> StartDrawFunctions;
	std::vector<std::vector<DrawFuncPtr>> EndDrawFunctions;

public:
	FExampleCode OutputExampleCodeData;
	FExampleCode LastOutputExampleCodeData;
};