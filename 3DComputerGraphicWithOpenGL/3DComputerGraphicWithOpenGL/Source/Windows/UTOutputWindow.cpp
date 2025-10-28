﻿// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "glad/glad.h"
#include "UTOutputWindow.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#include "Common.h"

FExampleCode::FExampleCode()
	: Title(L"")
	, DrawFunction(nullptr)
{
}

FExampleCode::FExampleCode(const std::wstring& InTitle)
	: Title(InTitle)
	, DrawFunction(nullptr)
{
}

FExampleCode::FExampleCode(const std::wstring& InTitle, void (UTOutputWindow::* InDrawFunction)(), void (UTOutputWindow::* InStartDrawFunction)(), void(UTOutputWindow::* InEndDrawFunction)())
	: Title(InTitle)
	, DrawFunction(InDrawFunction)
	, StartDrawFunction(InStartDrawFunction)
	, EndDrawFunction(InEndDrawFunction)
{
}

FExampleCode::FExampleCode(const FExampleCode& Other)
{
	Title = Other.Title;
	DrawFunction = Other.DrawFunction;
	StartDrawFunction = Other.StartDrawFunction;
	EndDrawFunction = Other.EndDrawFunction;
}

FExampleCode::~FExampleCode()
{
	if (DrawFunction)
	{
		DrawFunction = nullptr;
	}

	if (StartDrawFunction)
	{
		StartDrawFunction = nullptr;
	}

	if (EndDrawFunction)
	{
		EndDrawFunction = nullptr;
	}
}

const FExampleCode& FExampleCode::operator=(const FExampleCode& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		DrawFunction = Other.DrawFunction;
		StartDrawFunction = Other.StartDrawFunction;
		EndDrawFunction = Other.EndDrawFunction;
	}
	return *this;
}

bool FExampleCode::IsValid() const
{
	return !Title.empty();
}

UTOutputWindow::UTOutputWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
	, DrawFunctions()
{
	Initialize();
}

UTOutputWindow::~UTOutputWindow()
{

}

void UTOutputWindow::Initialize()
{
	UTWindow::Initialize();

	DrawFunctions.clear();
	DrawFunctions.resize(7);
	DrawFunctions[5].resize(16);
	DrawFunctions[6].resize(6);

	StartDrawFunctions.resize(7);
	StartDrawFunctions[5].resize(16);
	StartDrawFunctions[6].resize(6);

	EndDrawFunctions.resize(7);
	EndDrawFunctions[5].resize(16);
	EndDrawFunctions[6].resize(6);

#pragma region Chapter5
	DrawFunctions[5][2] = &UTOutputWindow::Code_5_2;
	
	DrawFunctions[5][4] = &UTOutputWindow::Code_5_4;
	
	StartDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_Start;
	DrawFunctions[5][5] = &UTOutputWindow::Code_5_5;
	EndDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_End;

	StartDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_Start;
	DrawFunctions[5][6] = &UTOutputWindow::Code_5_6;
	EndDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_End;

	StartDrawFunctions[5][7] = &UTOutputWindow::Code_5_7_Start;
	DrawFunctions[5][7] = &UTOutputWindow::Code_5_7;
	EndDrawFunctions[5][7] = &UTOutputWindow::Code_5_7_End;

	DrawFunctions[5][13] = &UTOutputWindow::Code_5_13;
	EndDrawFunctions[5][13] = &UTOutputWindow::Code_5_13_End;

	StartDrawFunctions[5][14] = &UTOutputWindow::Code_5_14_Start;
	DrawFunctions[5][14] = &UTOutputWindow::Code_5_14;
	EndDrawFunctions[5][14] = &UTOutputWindow::Code_5_14_End;
	MyListID_5_14 = 0;

	StartDrawFunctions[5][15] = &UTOutputWindow::Code_5_15_Start;
	DrawFunctions[5][15] = &UTOutputWindow::Code_5_15;
	EndDrawFunctions[5][15] = &UTOutputWindow::Code_5_15_End;
	FlatShadeMode_5_15 = false;
	WireframeMode_5_15 = false;
	cursor_xpos_5_15 = 0.5;
	cursor_ypos_5_15 = 0.5;
#pragma endregion

#pragma region Chapter6
	DrawFunctions[6][3] = &UTOutputWindow::Code_6_3;
	EndDrawFunctions[6][3] = &UTOutputWindow::Code_6_3_End;

	StartDrawFunctions[6][5] = &UTOutputWindow::Code_6_6_Start;
	DrawFunctions[6][5] = &UTOutputWindow::Code_6_6;
	EndDrawFunctions[6][5] = &UTOutputWindow::Code_6_6_End;
	EarthOrbitAngle_6_6 = 0.f;
	EarthRotationAngle_6_6 = 0.f;
	MoonOrbitAngle_6_6 = 0.f;
#pragma endregion
}

void UTOutputWindow::RenderDrawData()
{
	if (OutputExampleCodeData.IsValid() && OutputExampleCodeData.DrawFunction)
	{
		(this->*OutputExampleCodeData.DrawFunction)();
	}
}

void UTOutputWindow::SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter,unsigned int InSection, unsigned int InCodeIndex)
{
	LastOutputExampleCodeData = OutputExampleCodeData;

	OutputExampleCodeData.Title = RESOURCE_MANAGER->FindTitleContext(InPart, InChapter, InSection,InCodeIndex).c_str();
	OutputExampleCodeData.DrawFunction = DrawFunctions[InChapter][InCodeIndex];
	
	if(StartDrawFunctions.at(InChapter).at(InCodeIndex))
		OutputExampleCodeData.StartDrawFunction = StartDrawFunctions[InChapter][InCodeIndex];
	
	if(EndDrawFunctions.at(InChapter).at(InCodeIndex))
		OutputExampleCodeData.EndDrawFunction = EndDrawFunctions[InChapter][InCodeIndex];

	if (LastOutputExampleCodeData.IsValid() && LastOutputExampleCodeData.EndDrawFunction)
		(this->*LastOutputExampleCodeData.EndDrawFunction)();

	if(OutputExampleCodeData.IsValid() && OutputExampleCodeData.StartDrawFunction)
		(this->*OutputExampleCodeData.StartDrawFunction)();

	glfwSetWindowShouldClose(GetGLFWWindow(), GLFW_FALSE);
}

void UTOutputWindow::ResetAll()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glFlush();
	glGetError();
}

void UTOutputWindow::DumpGLState(const char* tag)
{
	glfwMakeContextCurrent(GetGLFWWindow());
	GLint iv[4];
	GLfloat fv[16];
	GLint i;
	GLint prog = 0;
	GLint tex = 0;
	GLfloat clearColor[4];
	GLfloat depthClear;
	GLint shadeModel;
	GLint frontFace;
	GLint activeTexture;
	GLfloat mv[16], pr[16];

	printf("---- GL STATE DUMP %s ----\n", tag);

	glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
	glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClear);
	printf("CLEAR COLOR: %f %f %f %f  DEPTH CLEAR: %f\n", clearColor[0], clearColor[1], clearColor[2], clearColor[3], depthClear);

	glGetIntegerv(GL_SHADE_MODEL, &shadeModel);
	printf("SHADE MODEL (enum): %d (GL_FLAT=0x1D00, GL_SMOOTH=0x1D01)\n", shadeModel);

	glGetIntegerv(GL_FRONT_FACE, &frontFace);
	printf("FRONT_FACE (enum): %d (GL_CCW=0x0901, GL_CW=0x0900)\n", frontFace);

	printf("GL_DEPTH_TEST: %s\n", glIsEnabled(GL_DEPTH_TEST) ? "ENABLED" : "DISABLED");
	printf("GL_LIGHTING: %s\n", glIsEnabled(GL_LIGHTING) ? "ENABLED" : "DISABLED");
	printf("GL_LIGHT0: %s\n", glIsEnabled(GL_LIGHT0) ? "ENABLED" : "DISABLED");
	printf("GL_NORMALIZE: %s\n", glIsEnabled(GL_NORMALIZE) ? "ENABLED" : "DISABLED");
	printf("GL_COLOR_MATERIAL: %s\n", glIsEnabled(GL_COLOR_MATERIAL) ? "ENABLED" : "DISABLED");
	printf("GL_TEXTURE_2D: %s\n", glIsEnabled(GL_TEXTURE_2D) ? "ENABLED" : "DISABLED");
	printf("GL_CULL_FACE: %s\n", glIsEnabled(GL_CULL_FACE) ? "ENABLED" : "DISABLED");

	glGetIntegerv(GL_ACTIVE_TEXTURE, &activeTexture);
	printf("ACTIVE_TEXTURE enum: 0x%X\n", activeTexture);

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
	printf("BOUND TEXTURE_2D id: %d\n", tex);

	// 현재 바인드된 GL program (if using shaders)
	glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
	printf("CURRENT_PROGRAM id: %d\n", prog);

	// 라이트0 파라미터
	GLfloat lightPos[4], lightDiff[4], lightSpec[4], lightAmb[4];
	glGetLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glGetLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	printf("LIGHT0 POS: %f %f %f %f\n", lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
	printf("LIGHT0 DIFFUSE: %f %f %f %f\n", lightDiff[0], lightDiff[1], lightDiff[2], lightDiff[3]);
	printf("LIGHT0 SPECULAR: %f %f %f %f\n", lightSpec[0], lightSpec[1], lightSpec[2], lightSpec[3]);

	// 머티리얼(프런트)
	GLfloat matDiffuse[4], matSpecular[4], matAmbient[4], matShininess[1];
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glGetMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glGetMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	printf("MATERIAL FRONT DIFFUSE: %f %f %f %f\n", matDiffuse[0], matDiffuse[1], matDiffuse[2], matDiffuse[3]);
	printf("MATERIAL FRONT SPEC: %f %f %f %f\n", matSpecular[0], matSpecular[1], matSpecular[2], matSpecular[3]);
	printf("MATERIAL FRONT AMBIENT: %f %f %f %f\n", matAmbient[0], matAmbient[1], matAmbient[2], matAmbient[3]);
	printf("MATERIAL SHININESS: %f\n", matShininess[0]);

	// 행렬들
	glGetFloatv(GL_MODELVIEW_MATRIX, mv);
	glGetFloatv(GL_PROJECTION_MATRIX, pr);
	printf("MODELVIEW MATRIX:\n");
	for (i = 0; i < 16; ++i) { printf("%f ", mv[i]); if ((i + 1) % 4 == 0) printf("\n"); }
	printf("PROJECTION MATRIX:\n");
	for (i = 0; i < 16; ++i) { printf("%f ", pr[i]); if ((i + 1) % 4 == 0) printf("\n"); }

	// 클라이언트 상태
	printf("CLIENT STATE VERTEX_ARRAY: %s\n", glIsEnabled(GL_VERTEX_ARRAY) ? "ENABLED" : "DISABLED");
	printf("CLIENT STATE COLOR_ARRAY: %s\n", glIsEnabled(GL_COLOR_ARRAY) ? "ENABLED" : "DISABLED");
	printf("CLIENT STATE_NORMAL_ARRAY: %s\n", glIsEnabled(GL_NORMAL_ARRAY) ? "ENABLED" : "DISABLED");
	printf("------------------------------\n");
}
