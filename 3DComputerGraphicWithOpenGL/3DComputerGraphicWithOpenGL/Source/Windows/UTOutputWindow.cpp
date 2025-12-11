// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTOutputWindow.h"
#include "Common.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"

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

#pragma region Chapter5
	StartDrawFunctions[5][2] = &UTOutputWindow::Code_5_2_Start;
	DrawFunctions[5][2] = &UTOutputWindow::Code_5_2;
	EndDrawFunctions[5][2] = &UTOutputWindow::Code_5_2_End;
	
	StartDrawFunctions[5][4] = &UTOutputWindow::Code_5_4_Start;
	DrawFunctions[5][4] = &UTOutputWindow::Code_5_4;
	EndDrawFunctions[5][4] = &UTOutputWindow::Code_5_4_End;
	
	StartDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_Start;
	DrawFunctions[5][5] = &UTOutputWindow::Code_5_5;
	EndDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_End;

	StartDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_Start;
	DrawFunctions[5][6] = &UTOutputWindow::Code_5_6;
	EndDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_End;

	StartDrawFunctions[5][7] = &UTOutputWindow::Code_5_7_Start;
	DrawFunctions[5][7] = &UTOutputWindow::Code_5_7;
	EndDrawFunctions[5][7] = &UTOutputWindow::Code_5_7_End;
	TopLeftX_5_7 = -0.85;
	TopLeftY_5_7 = 0.85;
	BottomRightX_5_7 = 0.85;
	BottomRightY_5_7 = -0.85;

	StartDrawFunctions[5][13] = &UTOutputWindow::Code_5_13_Start;
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
	StartDrawFunctions[6][3] = &UTOutputWindow::Code_6_3_Start;
	DrawFunctions[6][3] = &UTOutputWindow::Code_6_3;
	EndDrawFunctions[6][3] = &UTOutputWindow::Code_6_3_End;

	StartDrawFunctions[6][6] = &UTOutputWindow::Code_6_6_Start;
	DrawFunctions[6][6] = &UTOutputWindow::Code_6_6;
	EndDrawFunctions[6][6] = &UTOutputWindow::Code_6_6_End;
	EarthOrbitAngle_6_6 = 0.f;
	EarthRotationAngle_6_6 = 0.f;
	MoonOrbitAngle_6_6 = 0.f;

	StartDrawFunctions[6][8] = &UTOutputWindow::Code_6_8_Start;
	DrawFunctions[6][8] = &UTOutputWindow::Code_6_8;
	EndDrawFunctions[6][8] = &UTOutputWindow::Code_6_8_End;

	StartDrawFunctions[6][9] = &UTOutputWindow::Code_6_9_Start;
	DrawFunctions[6][9] = &UTOutputWindow::Code_6_9;
	EndDrawFunctions[6][9] = &UTOutputWindow::Code_6_9_End;
	Gravity_6_9 = 9.8f;
	Elastic_6_9 = 0.55f;
	InitialHeight_6_9 = 30.f;
	InitialVerticalVelocity_6_9 = 0.f;
	Time_6_9 = 0.f;

	StartDrawFunctions[6][10] = &UTOutputWindow::Code_6_10_Start;
	DrawFunctions[6][10] = &UTOutputWindow::Code_6_10;
	EndDrawFunctions[6][10] = &UTOutputWindow::Code_6_10_End;
	time_6_10 = 0;
	time2_6_10 = 0;
	time3_6_10 = 0;
	time4_6_10 = 0;
	time6_6_10 = 0;
	Time_6_10 = 0.f;
	LastTime_6_10 = 0.f;

	R_Arm_x_6_10 = 0.f;
	R_Arm_y_6_10 = 0.f;
	L_Arm_x_6_10 = 0.f;
	L_Arm_y_6_10 = 0.f;
	R_Leg_x_6_10 = 0.f;
	R_Leg_y_6_10 = 0.f;
	L_Leg_x_6_10 = 0.f;
	L_Leg_y_6_10 = 0.f;
	R_6_10 = 0.f;
	R2_6_10 = 0.f;

	cyl_6_10 = nullptr;

	a_6_10 = 0;
	b_6_10 = 0;
	c_6_10 = 0;

	flag_6_10 = 0;
	key_6_10 = 1;
#pragma endregion

#pragma region Chapter7
	StartDrawFunctions[7][1] = &UTOutputWindow::Code_7_1_Start;
	DrawFunctions[7][1] = &UTOutputWindow::Code_7_1;
	EndDrawFunctions[7][1] = &UTOutputWindow::Code_7_1_End;
#pragma endregion

#pragma region Chapter8
	StartDrawFunctions[8][3] = &UTOutputWindow::Code_8_3_Start;
	DrawFunctions[8][3] = &UTOutputWindow::Code_8_3;
	EndDrawFunctions[8][3] = &UTOutputWindow::Code_8_3_End;

	StartDrawFunctions[8][6] = &UTOutputWindow::Code_8_6_Start;
	DrawFunctions[8][6] = &UTOutputWindow::Code_8_6;
	EndDrawFunctions[8][6] = &UTOutputWindow::Code_8_6_End;
#pragma endregion

#pragma region Chapter9
	StartDrawFunctions[9][10] = &UTOutputWindow::Code_9_10_Start;
	DrawFunctions[9][10] = &UTOutputWindow::Code_9_10;
	EndDrawFunctions[9][10] = &UTOutputWindow::Code_9_10_End;

	StartDrawFunctions[9][15] = &UTOutputWindow::Code_9_15_Start;
	DrawFunctions[9][15] = &UTOutputWindow::Code_9_15;
	EndDrawFunctions[9][15] = &UTOutputWindow::Code_9_15_End;
	Index_9_15 = 0;
	ElapsedTime_9_15 = 0.f;
	Time_9_15 = 0.f;
	bSmooth_9_15 = false;
	bBlend_9_15 = false;
	bChangePalette = false;
#pragma endregion

#pragma region Chapter10
	StartDrawFunctions[10][11] = &UTOutputWindow::Code_10_11_Start;
	DrawFunctions[10][11] = &UTOutputWindow::Code_10_11;
	EndDrawFunctions[10][11] = &UTOutputWindow::Code_10_11_End;
	bEnableLight0_10_11 = true;
	bEnableLight1_10_11 = true;
	
	StartDrawFunctions[10][12] = &UTOutputWindow::Code_10_12_Start;
	DrawFunctions[10][12] = &UTOutputWindow::Code_10_12;
	EndDrawFunctions[10][12] = &UTOutputWindow::Code_10_12_End;
	LightSpinAngle_10_12 = 0.f;
	Time_10_12 = 0.f;
	ElapsedTime_10_12 = 0.f;
	Stacks_10_12 = 60;
	Slices_10_12 = 60;
#pragma endregion

#pragma region Chapter11
	StartDrawFunctions[11][7] = &UTOutputWindow::Code_11_7_Start;
	DrawFunctions[11][7] = &UTOutputWindow::Code_11_7;
	EndDrawFunctions[11][7] = &UTOutputWindow::Code_11_7_End;
	TextureObject_11_7 = 0;
	QuardricObj_11_7 = nullptr;

	StartDrawFunctions[11][9] = &UTOutputWindow::Code_11_9_Start;
	DrawFunctions[11][9] = &UTOutputWindow::Code_11_9;
	EndDrawFunctions[11][9] = &UTOutputWindow::Code_11_9_End;

	StartDrawFunctions[11][11] = &UTOutputWindow::Code_11_11_Start;
	DrawFunctions[11][11] = &UTOutputWindow::Code_11_11;
	EndDrawFunctions[11][11] = &UTOutputWindow::Code_11_11_End;
	Terrain_11_11 = nullptr;
	Skybox_11_11 = nullptr;
	Camera_11_11 = nullptr;
	Time_11_11 = 0.f;
	ElapsedTime_11_11 = 0.f;
#pragma endregion

#pragma region Chapter12
	StartDrawFunctions[12][8] = &UTOutputWindow::Code_12_8_Start;
	DrawFunctions[12][8] = &UTOutputWindow::Code_12_8;
	EndDrawFunctions[12][8] = &UTOutputWindow::Code_12_8_End;
	StartX_12_8 = 0, StartY_12_8 = 0;
	EndX_12_8 = 0, EndY_12_8 = 0;;
#pragma endregion

#pragma region Chapter14
	StartDrawFunctions[14][1] = &UTOutputWindow::Code_14_1_Start;
	DrawFunctions[14][1] = &UTOutputWindow::Code_14_1;
	EndDrawFunctions[14][1] = &UTOutputWindow::Code_14_1_End;
	bDrawStyle_14_1 = 1 << 2;
	bDrawingShape_14_1 = 1 << 0;

	StartDrawFunctions[14][2] = &UTOutputWindow::Code_14_2_Start;
	DrawFunctions[14][2] = &UTOutputWindow::Code_14_2;
	EndDrawFunctions[14][2] = &UTOutputWindow::Code_14_2_End;
	
	for(int i = 0 ; i < 4 ; ++i)
	{
		for(int j = 0 ; j < 4 ; ++j)
		{
			weight_14_2[i][j] = 1.f;
		}
	}
	
	point_mat_diffuse[0] = 1.f;
	point_mat_diffuse[1] = 0.5f;
	point_mat_diffuse[2] = 1.f;
	point_mat_diffuse[3] = 1.f;
	
	point_mat_specular[0] = 0.8f;
	point_mat_specular[1] = 0.f;
	point_mat_specular[2] = 0.8f;
	point_mat_specular[3] = 0.f;

	point_mat_emission[0] = 0.f;
	point_mat_emission[1] = 0.f;
	point_mat_emission[2] = 0.f;
	point_mat_emission[3] = 1.f;

	point_mat_shininess[0] = 30.f;

	surface_mat_diffuse[0] = 0.8f;
	surface_mat_diffuse[1] = 0.8f;
	surface_mat_diffuse[2] = 0.2f;
	surface_mat_diffuse[3] = 1.f;

	surface_mat_specular[0] = 0.8f;
	surface_mat_specular[1] = 0.f;
	surface_mat_specular[2] = 0.8f;
	surface_mat_specular[3] = 0.0f;

	surface_mat_emission[0] = 0.f;
	surface_mat_emission[1] = 0.f;
	surface_mat_emission[2] = 0.f;
	surface_mat_emission[3] = 1.f;

	surface_mat_shininess[0] = 30.f;

	ElapsedTime_14_2 = 0.f;
	Time_14_2 = 0.f;
#pragma endregion

#pragma region Chapter 15
	StartDrawFunctions[15][2] = &UTOutputWindow::Code_15_2_Start;
	DrawFunctions[15][2] = &UTOutputWindow::Code_15_2;
	EndDrawFunctions[15][2] = &UTOutputWindow::Code_15_2_End;
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

	if (StartDrawFunctions.at(InChapter).find(InCodeIndex) != StartDrawFunctions.at(InChapter).end())
	{
		OutputExampleCodeData.StartDrawFunction = StartDrawFunctions[InChapter][InCodeIndex];
	}
	else
	{
		OutputExampleCodeData.StartDrawFunction = nullptr;
	}
	
	if (EndDrawFunctions.at(InChapter).find(InCodeIndex) != EndDrawFunctions.at(InChapter).end())
	{
		OutputExampleCodeData.EndDrawFunction = EndDrawFunctions[InChapter][InCodeIndex];
	}
	else
	{
		OutputExampleCodeData.EndDrawFunction = nullptr;
	}

	if (LastOutputExampleCodeData.IsValid() && LastOutputExampleCodeData.EndDrawFunction)
		(this->*LastOutputExampleCodeData.EndDrawFunction)();

	if(OutputExampleCodeData.IsValid() && OutputExampleCodeData.StartDrawFunction)
		(this->*OutputExampleCodeData.StartDrawFunction)();

	glfwSetWindowShouldClose(GetGLFWWindow(), GLFW_FALSE);
}
