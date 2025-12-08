// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "3DComputerGraphicWithOpenGL.h"
#include "UTWindow.h"
#include "Windows/OutputCode/camera.h"
#include "Windows/OutputCode/skybox.h"
#include "Windows/OutputCode/terrain.h"
#include <vector>

#include "io.h"

#define M_PI 3.14159265358979323846

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
	void Code_5_2_Start();
	void Code_5_2();
	void Code_5_2_End();

	void Code_5_4_Start();
	void Code_5_4();
	void Code_5_4_End();

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
	GLfloat TopLeftX_5_7;
	GLfloat TopLeftY_5_7;
	GLfloat BottomRightX_5_7;
	GLfloat BottomRightY_5_7;

	void Code_5_13_Start();
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
	static void Code_5_15_CursorPosition(GLFWwindow* Window, double xpos, double ypos);
	bool FlatShadeMode_5_15;
	bool WireframeMode_5_15;
	std::vector<Vertex> vertices_5_15;
	std::vector<unsigned int> indices_5_15;
	std::vector<MaterialInfo> materials_5_15;
	GLfloat light_position_5_15[5];
	double cursor_xpos_5_15, cursor_ypos_5_15;
#pragma endregion

#pragma region Chapter6
private:
	void Code_6_3_Start();
	void Code_6_3();
	void Code_6_3_End();

	void Code_6_6_Start();
	void Code_6_6();
	void Code_6_6_End();
	static void Code_6_6_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	GLfloat EarthOrbitAngle_6_6;
	GLfloat EarthRotationAngle_6_6;
	GLfloat MoonOrbitAngle_6_6;

	void Code_6_8_Start();
	void Code_6_8();
	void Code_6_8_End();
	std::vector<Vertex> vertices_6_8;
	std::vector<unsigned int> indices_6_8;
	std::vector<MaterialInfo> materials_6_8;

	void Code_6_9_Start();
	void Code_6_9();
	void Code_6_9_End();
	static void Code_6_9_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	struct BoundcingBall_physics
	{
		GLfloat Gravity;   // 중력 가속도 (>0)
		GLfloat Elastic;   // 탄성 계수 (0 <= e <= 1)
		GLfloat IniitlaiHeight;  // 초기 높이 (>=0)
		GLfloat InitialVerticalVelocity;  // 초기 수직 속도 (양수: 위, 음수: 아래)
		GLfloat HorizonalVelocity; // 수평 속도
	};
	std::array<GLfloat, 2> GetBallState_6_9(const BoundcingBall_physics Physics, const GLfloat Time);
	 GLfloat GetBallHeight(const BoundcingBall_physics Physics, const GLfloat Time, const double epsilon = 1e-12);
	 GLfloat Gravity_6_9;
	 GLfloat Elastic_6_9;
	 GLfloat InitialHeight_6_9;
	 GLfloat InitialVerticalVelocity_6_9;
	 GLfloat HorizonalVelocity_6_9;
	 GLfloat Time_6_9;
	 std::vector<Vertex> vertices_6_9;
	 std::vector<unsigned int> indices_6_9;
	 std::vector<MaterialInfo> materials_6_9;

	void Code_6_10_Start();
	void Code_6_10();
	void Code_6_10_End();
	static void Code_6_10_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	void Draw_Color(int i);
	void Change_Wire_Or_Solid(int i);
	void DrawL_Arm(int x, int a, int b, int c);
	void DrawL_Hand(int y, int a, int b, int c);
	void DrawL_HandRocket();
	void DrawR_Arm(int x, int a, int b, int c);
	void DrawR_Hand(int y, int a, int b, int c);
	void DrawR_HandRocket();
	void DrawBody(int x, int a, int b, int c);
	void DrawL_Legs(int x, int a, int b, int c);
	void DrawL_foot(int y, int a, int b, int c);
	void DrawR_Legs(int x, int a, int b, int c);
	void DrawR_foot(int y, int a, int b, int c);
	void Drawneck();
	void DrawGround();
	void DrawHead();
	void DrawAndroid();
	void Run();
	void Jap();
	void ex();
	void Show();
	void Rocket();
	double time_6_10;  // Run_time 변수
	double time2_6_10; // Jap_time 변수
	double time3_6_10; // Rocket_time 변수
	double time4_6_10; // ground_time 변수
	double time6_6_10; // exit_time 변수
	GLfloat Time_6_10;
	GLfloat LastTime_6_10;

	GLfloat R_Arm_x_6_10; 
	GLfloat R_Arm_y_6_10; 
	GLfloat L_Arm_x_6_10; 
	GLfloat L_Arm_y_6_10; 
	GLfloat R_Leg_x_6_10; 
	GLfloat R_Leg_y_6_10; 
	GLfloat L_Leg_x_6_10; 
	GLfloat L_Leg_y_6_10; 
	GLfloat R_6_10; 
	GLfloat R2_6_10;

	GLUquadricObj* cyl_6_10;

	int a_6_10; // x축 기준(값이 1일 때 x축을 기준으로 회전)
	int b_6_10; // y축 기준(값이 1일 때 y축을 기준으로 회전)
	int c_6_10;

	int flag_6_10; // wireframe 모드와 solid rendering 모드 구분 변수
	int key_6_10;  // 동작 모드와 색상 변경 변수

#define RUN		1
#define JAP		2
#define ROCKET	3
#define YUNA	4
#define EXIT	5
#pragma endregion 

#pragma region Chapter7
private:
	void Code_7_1_Start();
	void Code_7_1();
	void Code_7_1_End();
	void Code_7_1_DrawScene();
	std::vector<Vertex> vertices_7_1;
	std::vector<unsigned int> indices_7_1;
	std::vector<MaterialInfo> materials_7_1;
#pragma endregion

#pragma region Chapter8
private:
	void Code_8_3_Start();
	void Code_8_3();
	void Code_8_3_End();
	std::vector<Vertex> vertices_8_3;
	std::vector<unsigned int> indices_8_3;
	std::vector<MaterialInfo> materials_8_3;

	void Code_8_6_Start();
	void Code_8_6();
	void Code_8_6_End();
#pragma endregion

#pragma region Chapter9
private:
	void Code_9_10_Start();
	void Code_9_10();
	void Code_9_10_End();

	void Code_9_15_Start();
	void Code_9_15();
	void Code_9_15_End();
	static void Code_9_15_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	unsigned char PALETTE[16][3] =
	{
	{ 255, 255, 255 },      // WHITE
	{   0, 255, 255 },      // CYAN
	{ 255,   0, 255 },      // PURPLE
	{   0,   0, 255 },      // BLUE
	{ 192, 192, 192 },      // LIGHT GRAY
	{ 128, 128, 128 },      // DARK GRAY
	{   0, 128, 128 },      // DARK TEAL
	{ 128,   0, 128 },      // DARK PURPLE
	{   0,   0, 128 },      // DARK BLUE
	{ 255, 255,   0 },      // YELLOW
	{   0, 255,   0 },      // GREEN
	{ 128, 128,   0 },      // DARK YELLOW
	{   0, 128,   0 },      // DARK GREEN
	{ 255,   0,   0 },      // RED
	{ 128,   0,   0 },      // DARK RED
	{   0,   0,   0 },      // BLACK
	};

	GLint Index_9_15;
	GLfloat ElapsedTime_9_15;
	GLfloat Time_9_15;
	bool bSmooth_9_15;
	bool bBlend_9_15;
	bool bChangePalette;
#pragma endregion

#pragma region Chapter10
private:
	void Code_10_11_Start();
	void Code_10_11();
	void Code_10_11_End();
	static void Code_10_11_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	bool bEnableLight0_10_11;
	bool bEnableLight1_10_11;

	void Code_10_12_Start();
	void Code_10_12();
	void Code_10_12_End();
	GLfloat LightSpinAngle_10_12;
	GLfloat ElapsedTime_10_12;
	GLfloat Time_10_12;
	GLint Stacks_10_12;
	GLint Slices_10_12;
#pragma endregion

#pragma region Chapter11
private:
	void Code_11_7_Start();
	void Code_11_7();
	void Code_11_7_End();

#define Width_11_7 4
#define Height_11_7 4
	GLubyte Texture_11_7[Width_11_7][Height_11_7][3];
	GLuint TextureObject_11_7;
	GLUquadricObj* QuardricObj_11_7;
	
	void Code_11_9_Start();
	void Code_11_9();
	void Code_11_9_End();

	void Code_11_11_Start();
	void Code_11_11();
	void Code_11_11_End();
	static void Code_11_11_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	void dispose();
	void fog();

	Terrain* Terrain_11_11;
	Skybox* Skybox_11_11;
	Camera* Camera_11_11;
	GLfloat Time_11_11;
	GLfloat ElapsedTime_11_11;

	enum EKeyInputAction
	{
		LEFT = 0,
		RIGHT,
		FORWARD,
		BACKWARD,
		UP,
		DOWN,
		PITCH_UP,
		PITCH_DOWN,
		YAW_LEFT,
		YAW_RIGHT,
		ROLL_LEFT,
		ROLL_RIGHT
	};
	
	std::array<bool, 12> Actions{};
	bool LINE_MODE_11_11 = false;
	bool FILL_MODE_11_11 = true;
#pragma endregion

#pragma region Chapter12
private:
	void Code_12_8_Start();
	void Code_12_8();
	void Code_12_8_End();
	static void Code_12_8_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	void DrawScene_12_8();
	GLint StartX_12_8, StartY_12_8;
	GLint EndX_12_8, EndY_12_8;
#pragma endregion

#pragma region Chapter14
private:
	void Code_14_1_Start();
	void Code_14_1();
	void Code_14_1_End();
	static void Code_14_1_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	GLUquadricObj* QuardricObj_14_1;
	unsigned int bDrawStyle_14_1;
	unsigned int bDrawingShape_14_1;

	void Code_14_2_Start();
	void Code_14_2();
	void Code_14_2_End();
	static inline GLfloat weight_14_2[4][4];
	static inline GLfloat ctlpointsCoordi_14_2[4][4][4];
	static inline GLfloat ctlpoints_14_2[4][4][4];
	GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
	static inline GLUnurbsObj* Nurbs_14_2;
	GLfloat point_mat_diffuse[4];
	GLfloat point_mat_specular[4];
	GLfloat point_mat_emission[4];
	GLfloat point_mat_shininess[1];
	GLfloat surface_mat_diffuse[4];
	GLfloat surface_mat_specular[4];
	GLfloat surface_mat_emission[4];
	GLfloat surface_mat_shininess[1];
	GLfloat ElapsedTime_14_2;
	GLfloat Time_14_2;
#pragma endregion

#pragma region Chapter15
private:
	void Code_15_2_Start();
	void Code_15_2();
	void Code_15_2_End();
	char* ReadShaderSource(char* fileName);
	GLhandleARB h_vertex_15_2, h_frag_15_2, h_program_15_2;
#pragma endregion

private:
#define MAX_CHAPTER_COUNT 15
	using DrawFuncPtr = void (UTOutputWindow::*)();
	std::array<std::unordered_map<unsigned int, DrawFuncPtr>, MAX_CHAPTER_COUNT + 1> DrawFunctions;

	std::array<std::unordered_map<unsigned int, DrawFuncPtr>, MAX_CHAPTER_COUNT + 1> StartDrawFunctions;
	std::array<std::unordered_map<unsigned int, DrawFuncPtr>, MAX_CHAPTER_COUNT + 1 > EndDrawFunctions;

public:
	FExampleCode OutputExampleCodeData;
	FExampleCode LastOutputExampleCodeData;
};