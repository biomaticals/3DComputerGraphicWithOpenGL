// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "Manager/ResourceManager.h"
#include<windows.h>
#include<MMSystem.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>
#include<cmath>

void UTOutputWindow::Code_6_3()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);

	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 1.f, 1.f);

	// 원점
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.1f, 0.f);
	glVertex3f(0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, 0.1f, 0.f);
	glEnd();

	// 45도 회전 후, x축으로 0.6만큼 이동
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(45.f, 0.f, 0.f, 1.f);
	glTranslatef(0.6f, 0.f, 0.f);
	glColor3f(1.f, 0.f, 0.f);

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.1f, 0.f);
	glVertex3f(0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, 0.1f, 0.f);
	glEnd();

	// 먼저 x축으로 0.6만큼 이동 후, 45도 회전
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.6f, 0.f, 0.f);
	glRotatef(45.f, 0.f, 0.f, 1.f);
	glColor3f(0.f, 1.f, 0.f);

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.1f, 0.f);
	glVertex3f(0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, -0.1f, 0.f);
	glVertex3f(-0.1f, 0.1f, 0.f);
	glEnd();

	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_6_3_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.f, 1.f, 1.f);
}

void UTOutputWindow::Code_6_6_Start()
{
	ResetAll();
	glfwSetKeyCallback(GetGLFWWindow(), Code_6_6_Key);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void UTOutputWindow::Code_6_6()
{
	// 이전의 Code들을 참고해줘. 태양계 모델링을 할거야. 태양, 지구, 달을 그릴 거고, 사용자에게 1를 입력받아서 지구의 자전, 달의 공전을 점점 진행하게 해주고 2를 입력 받아서 지구의 공전을 실행시켜줘
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.f, 5.f, -5.f, 5.f, -5.f, 5.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 태양
	glPushMatrix();
	glColor3f(1.f, 0.84f, 0.f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 30)
	{
		float rad = i * 3.14159f / 180.f;
		glVertex3f(0.5f * cos(rad), 0.5f * sin(rad), 0.f);
	}
	glEnd();

	// 지구
	glRotatef(EarthOrbitAngle_6_6, 0.f, 0.f, 1.f); // 지구 공전
	glTranslatef(3.f, 0.f, 0.f);
	glRotatef(EarthRotationAngle_6_6, 0.f, 0.f, 1.f); // 지구 자전
	glPushMatrix();

	glColor3f(0.2f, 0.5f, 0.9f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 30)
	{
		float rad = i * 3.14159f / 180.f;
		glVertex3f(0.2f * cos(rad), 0.2f * sin(rad), 0.f);
	}
	glEnd();

	// 달
	glRotatef(MoonOrbitAngle_6_6, 0.f, 0.f, 1.f); // 달 공전
	glTranslatef(0.7f, 0.f, 0.f);
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 30)
	{
		float rad = i * 3.14159f / 180.f;
		glVertex3f(0.05f * cos(rad), 0.05f * sin(rad), 0.f);
	}
	glEnd();

	glPopMatrix(); // 지구 복원
	glPopMatrix(); // 태양 복원

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_6_6_End()
{
	ResetAll();
}

void UTOutputWindow::Code_6_6_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action == GLFW_PRESS)
	{
		switch (Key)
		{
		case GLFW_KEY_1:
		{
			OUTPUT_WINDOW->EarthRotationAngle_6_6 += 10.f;
			OUTPUT_WINDOW->MoonOrbitAngle_6_6 += 6.f;
			break;
		}
		case GLFW_KEY_2:
		{
			OUTPUT_WINDOW->EarthOrbitAngle_6_6 += 5.f;
			break;
		}
		case GLFW_KEY_R:
		{
			OUTPUT_WINDOW->EarthOrbitAngle_6_6 = 0.f;
			OUTPUT_WINDOW->EarthRotationAngle_6_6 = 0.f;
			OUTPUT_WINDOW->MoonOrbitAngle_6_6 = 0.f;
			break;
		}
		case GLFW_KEY_Q:
		{
			exit(0);
			break;
		}
		default:
			break;
		}
	}
}

void UTOutputWindow::Code_6_8_Start()
{
	ResetAll();
	const std::string basepath = "Resource/Object/Chaynik/";
	const std::string texbasepath = "Resource/Object/Chaynik/textures";
	const std::string objpath = basepath + "Chaynik.obj";
	LoadObjWithMaterial(objpath, vertices_6_8, indices_6_8, materials_6_8);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	GLfloat mat_diffuse[] = { 0.f, 0.4f, 0.3f, 1.f };
	GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat mat_ambient[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat mat_shininess[] = { 15.f };
	GLfloat light_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
	GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.f };
	GLfloat light_position[] = { -3.f, 6.f, 3.f, 0.f };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glFlush();
}

void UTOutputWindow::Code_6_8()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float)display_w / (float)display_h,
		0.1f,
		10000.0f
	);
	glLoadMatrixf(&projection[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::mat4 view = glm::lookAt(
		glm::vec3(1.5f, 0.6f, -1.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	);
	glLoadMatrixf(&view[0][0]);

	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < indices_6_8.size(); i++)
	{
		const Vertex& v = vertices_6_8[indices_6_8[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_6_8_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.f, 1.f, 1.f);
}

void UTOutputWindow::Code_6_9_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), Code_6_9_Key);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	Gravity_6_9 = 9.8f;
	Elastic_6_9 = 0.75f;
	InitialHeight_6_9 = 30.f;
	InitialVerticalVelocity_6_9 = 0.f;
	HorizonalVelocity_6_9 = 5.f;
	Time_6_9 = glfwGetTime();

	const std::string basepath = "Resource/Object/Soccer_ball/";
	const std::string texbasepath = "Resource/Object/Soccer_ball/textures";
	const std::string objpath = basepath + "10536_soccerball_V1_iterations-2.obj";
	LoadObjWithMaterial(objpath, vertices_6_9, indices_6_9, materials_6_9);

	GLfloat light_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
	GLfloat light_ambient[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat global_ambient[] = { 0.6f, 0.6f, 0.6f, 1.f };

	light_position_5_15[0] = 50.f;
	light_position_5_15[1] = 50.f;
	light_position_5_15[2] = 0.f;
	light_position_5_15[3] = 0.f;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.f);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
}

void UTOutputWindow::Code_6_9()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, 100.f, -7.5f, 100.f, -100.f, 100.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if (!materials_6_9.empty() && materials_6_9[0].textureId != 0)
	{
		glBindTexture(GL_TEXTURE_2D, materials_6_9[0].textureId);
	}

	BoundcingBall_physics Physics{};
	Physics.Gravity = Gravity_6_9; // 중력 가속도
	Physics.Elastic = Elastic_6_9; // 탄성 계수
	Physics.IniitlaiHeight = InitialHeight_6_9; // 초기 높이
	Physics.InitialVerticalVelocity = InitialVerticalVelocity_6_9; // 초기 수직 속도
	Physics.HorizonalVelocity = HorizonalVelocity_6_9; // 수평 속도

	GLfloat currentTime = glfwGetTime();
	GLfloat deltaTime = (currentTime - Time_6_9);

	std::array<GLfloat, 2> BallPosition = GetBallState_6_9(Physics, deltaTime);

	if (BallPosition[0] >= 100.f)
	{
		Time_6_9 = currentTime;
		deltaTime = 0.f;
		BallPosition = GetBallState_6_9(Physics, deltaTime);
	}

	glTranslatef(BallPosition[0], BallPosition[1], 0.f);
	glRotatef(deltaTime * 30.f, 0.f, 0.f, -1.f);

	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < indices_6_9.size(); i++)
	{
		const Vertex& v = vertices_6_9[indices_6_9[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();

	std::wstring debugContext = L"중력가속도 증감(1/2), 탄성계수 증감(3/4), 초기 높이 증감(5/6), 초기 수직 속도 증감(7/8), 초기화(R)\n";
	debugContext += L"중력 가속도는 " + std::to_wstring(Gravity_6_9) + L", 탄성 계수는 " + std::to_wstring(Elastic_6_9) + L", 초기 높이는 " + std::to_wstring(InitialHeight_6_9) + L", 초기 수직 속도는 " + std::to_wstring(InitialVerticalVelocity_6_9);
	MAIN_WINDOW->DebugContext = debugContext;

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_6_9_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.f, 1.f, 1.f);
	Time_6_9 = 0.f;

	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_6_9_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{
		if (Action == GLFW_PRESS && Scancode == 0)
		{
	case GLFW_KEY_1:
		OUTPUT_WINDOW->Gravity_6_9 += 1.f; OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_2:
		OUTPUT_WINDOW->Gravity_6_9 = std::max(0.f, OUTPUT_WINDOW->Gravity_6_9 - 1.f); OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_3:
		OUTPUT_WINDOW->Elastic_6_9 = std::min(1.f, OUTPUT_WINDOW->Elastic_6_9 + 0.05f); OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_4:
		OUTPUT_WINDOW->Elastic_6_9 = std::max(0.f, OUTPUT_WINDOW->Elastic_6_9 - 0.05f); OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_5:
		OUTPUT_WINDOW->InitialHeight_6_9 += 1.f; OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_6:
		OUTPUT_WINDOW->InitialHeight_6_9 = std::max(0.f, OUTPUT_WINDOW->InitialHeight_6_9 - 1.f); OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_7:
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 += 1.f; OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_8:
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 -= 1.f; OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	case GLFW_KEY_R:
		OUTPUT_WINDOW->Gravity_6_9 = 9.8f;
		OUTPUT_WINDOW->Elastic_6_9 = 0.75f;
		OUTPUT_WINDOW->InitialHeight_6_9 = 30.f;
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 = 0.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		}
	}
}

std::array<GLfloat, 2> 	UTOutputWindow::GetBallState_6_9(const BoundcingBall_physics Physics, const GLfloat Time)
{
	std::array<GLfloat, 2> Position{};
	Position[0] = Physics.HorizonalVelocity * Time;
	Position[1] = GetBallHeight(Physics, Time);

	return Position;
}

GLfloat UTOutputWindow::GetBallHeight(const BoundcingBall_physics Physics, const GLfloat time, const double eps /* = 1e-12 */)
{
	if (time < 0.f)
		return Physics.IniitlaiHeight;

	if (Physics.IniitlaiHeight <= 0.f && Physics.InitialVerticalVelocity <= 0.f)
		return 0.f;

	const GLfloat G = Physics.Gravity;
	const GLfloat E = Physics.Elastic;
	const GLfloat Y0 = Physics.IniitlaiHeight;
	const GLfloat V0 = Physics.InitialVerticalVelocity;

	GLfloat U0 = sqrt(std::max(0.f, V0 * V0 + 2.f * G * Y0));
	if (U0 < eps)
		return 0.f;

	GLfloat t_first_bounce = (V0 + U0) / G;
	if (time < t_first_bounce)
	{
		return std::max(0.f, Y0 + V0 * time - 0.5f * G * time * time);
	}

	GLfloat T = t_first_bounce;
	GLfloat U_n = E * U0;
	if (E <= 0.f)
	{
		GLfloat dt_after = 2.f * U_n / G;
		if (time < T + dt_after)
		{
			GLfloat t_in_bounce = time - T;
			return std::max(0.f, t_in_bounce * (U_n * t_in_bounce - 0.5f * G * t_in_bounce));
		}
		else
		{
			return 0.f;
		}
	}

	GLint n = 1;
	while (true)
	{
		GLfloat dt_n = 2.f * U_n / G;
		if (time < T + dt_n || U_n <= eps)
		{
			GLfloat t_in_bounce = time - T;
			return std::max(0.f, t_in_bounce * (U_n - 0.5f * G * t_in_bounce));
		}

		T += dt_n;
		U_n *= E;
		if (U_n < eps)
			break;
		n++;
	}
	return 0.f;
}

static double time_6_10 = 0;  // Run_time 변수
static double time2_6_10 = 0; // Jap_time 변수
static double time3_6_10 = 0; // Rocket_time 변수
static double time4_6_10 = 0; // ground_time 변수
static double time6_6_10 = 0; // exit_time 변수

GLfloat R_Arm_x_6_10 = 0; // 오른쪽 어깨
GLfloat R_Arm_y_6_10 = 0; // 오른쪽 팔
GLfloat L_Arm_x_6_10 = 0; // 왼쪽 어깨
GLfloat L_Arm_y_6_10 = 0; // 왼쪽 팔
GLfloat R_Leg_x_6_10 = 0; // 오른 허벅지
GLfloat R_Leg_y_6_10 = 0; // 오른 종아리
GLfloat L_Leg_x_6_10 = 0; // 왼 허벅지
GLfloat L_Leg_y_6_10 = 0; // 왼 종아리
GLfloat R_6_10 = 0; // 왼쪽 로켓 펀치 움직임 변수
GLfloat R2_6_10 = 0;// 오른쪽 로켓 펀치 움직임 변수

GLUquadricObj* cyl_6_10;// 실린더 객체 선언

int a_6_10 = 0; // x축 기준(값이 1일 때 x축을 기준으로 회전)
int b_6_10 = 0; // y축 기준(값이 1일 때 y축을 기준으로 회전)
int c_6_10 = 0; // z축 기준(값이 1일 때 z축을 기준으로 회전)

static int flag_6_10 = 0; // wireframe 모드와 solid rendering 모드 구분 변수
static int key = 1;  // 동작 모드와 색상 변경 변수

#define RUN		1
#define JAP		2
#define ROCKET	3
#define YUNA	4
#define EXIT	5

void UTOutputWindow::Code_6_10_Start()
{
	ResetAll();
	glfwSetKeyCallback(GetGLFWWindow(), Code_6_10_Key);
	std::wstring MusicPath = RESOURCE_MANAGER->GetSoundPath() + L"\\funny-comedy-cartoon-background-music.mp3";
	bool Result = 0;
	if (std::filesystem::exists(MusicPath))
	{
		//Result = sndPlaySound(MusicPath.c_str(), SND_ASYNC | SND_NOSTOP);
		MCIERROR err = mciSendStringW((L"open \"" + MusicPath + L"\" type mpegvideo alias bgm").c_str(), NULL, 0, NULL);
		if (err != 0)
		{
			wchar_t errorText[256];
			mciGetErrorStringW(err, errorText, 256);
			std::wstring errorMessage = L"MCI Error: " + std::wstring(errorText);
			MAIN_WINDOW->DebugContext = errorMessage;
		}
		else
		{
			mciSendStringW(L"play bgm repeat", NULL, 0, NULL);
		}
	}

	glEnable(GL_DEPTH_TEST); // 깊이 테스팅 사용
	glEnable(GL_NORMALIZE);  // 정규화
	glEnable(GL_SMOOTH);     // 각 정점의 색상을 부드럽게 연결하여 칠해지도록  하므로, 각정점에 적용된 색상이 혼합되어 적용된다. 
	glEnable(GL_LIGHTING);   // 지엘 조명. 빛을 받는 각도에 따라 로봇 색상이 변화

	/* 빛을 받는 각도에 따라 로봇 색깔의 변화를 위한 설정 */
	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0,300.0,-700.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 검은색
	glMatrixMode(GL_PROJECTION);   // 모드 설정
	glLoadIdentity();              // CTM 값 초기화 
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 가시 범위 설정

	Time_6_10 = glfwGetTime();
	LastTime_6_10 = Time_6_10;
}

void Draw_Color(int i)
{ // 색상을 그리는 함수
	if (i == RUN) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (i == JAP) {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (i == ROCKET) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (i == YUNA) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (i == EXIT) {
		glColor3f(0.2, 0.2, 0.2);
	}
}

void Change_Wire_Or_Solid(int i)
{          // 솔리드, 와이어 선택
	if (flag_6_10 == 1)
		gluQuadricDrawStyle(cyl_6_10, GLU_LINE); // 스타일을 와이어로 변경
}
/*
로봇 왼팔을 그리는 함수
*/
void DrawL_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);       // 색 설정
	cyl_6_10 = gluNewQuadric();   // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0);    // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

/*
로봇 왼쪽 손을 그리는 함수
*/
void DrawL_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);       // 색 설정
	cyl_6_10 = gluNewQuadric();   // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c);        // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	if (key == YUNA) gluCylinder(cyl_6_10, 0.05, 0.02, 0.2, 15, 1); // 깔때기 모양 실린더를 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 15, 1);           // 실린더를 그림
	glPopMatrix();
}
/*
로봇 왼쪽 주먹
*/
void DrawL_HandRocket()
{
	glPushMatrix();
	Draw_Color(key);     // 색 설정
	cyl_6_10 = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R_6_10); // 왼쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}
/*
로봇 오른팔을 그리는 함수
*/
void DrawR_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);     // 색 설정
	cyl_6_10 = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축을 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); //우측 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); //우측 어깨 -15도 y축기준 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림

}
/*
로봇 오른쪽 손을 그리는 함수
*/
void DrawR_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22);//오른쪽 손 시작점
	glRotatef(y, a, b, c);// 파라미터값 만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	if (key == YUNA) gluCylinder(cyl_6_10, 0.05, 0.02, 0.2, 50, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}

/*
로봇 오른쪽 로켓트 함수
*/

void DrawR_HandRocket()
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glTranslatef(0, 0, R2_6_10);//오른주먹 위치 파라미터만큼 이동
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 몸체를 그리는 함수
*/
void DrawBody(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glRotatef(x, a, b, c);//파라미터값 만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.2, 0.2, 0.45, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 왼쪽 허벅지를 그리는 함수
*/
void DrawL_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.1, 0.0, 0.42);//왼쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 왼쪽 종아리를 그리는 함수
*/
void DrawL_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.18);//왼쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	if (key == YUNA) gluCylinder(cyl_6_10, 0.05, 0.03, 0.2, 50, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 오른쪽 허벅지를 그리는 함수
*/
void DrawR_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.1, 0.0, 0.42);//오른쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 오른쪽 종아리를 그리는 함수
*/
void DrawR_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성

	glTranslatef(0.0, 0.0, 0.18);//오른쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전

	Change_Wire_Or_Solid(flag_6_10);
	if (key == YUNA) gluCylinder(cyl_6_10, 0.05, 0.03, 0.2, 15, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 15, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 목을 그리는 함수
*/
void Drawneck()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);//색 지정(흰색)
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.0, 0.0, -0.045); // 목 시작점
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.2, 0.2, 0.025, 100, 1);// 실린더 그림
	glPopMatrix();
}
/*
땅을 그리는 함수
땅은 커다란 구로 설정하였다.
땅은 시간에 따라 회전하여서 마치 로봇이
앞으로 뛰어가는 느낌이 들도록 설계하였다.
*/
void DrawGround()
{
	Draw_Color(flag_6_10);//색깔 설정
	glTranslatef(0.0, -2.73, 0.0);//땅 시작점
	glRotatef(45.0, 0, 1, 0);//45도만큼 y축 방향으로 회전
	glRotatef(0.0 + time4_6_10 - 15, 0.0, 0.0, 1);// z축 기준으로 time4만큼 땅이 회전 
	Change_Wire_Or_Solid(flag_6_10);
	gluSphere(cyl_6_10, 2.5, 30, 90);
}
/*
로봇 머리를 그리는 함수
로봇의 머리에 달려있는 뿔과
로봇의 눈을 설정하였다.
*/
void DrawHead()
{
	glTranslatef(0.0, 0.02, 0.0);//머리 시작점
	glPushMatrix();// 처음 저장 좌표 다시 저장
	cyl_6_10 = gluNewQuadric();
	Change_Wire_Or_Solid(flag_6_10);
	Draw_Color(key);//색깔 설정
	gluSphere(cyl_6_10, 0.20, 30, 10);//머리 그리기
	/*왼쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.16, 0.0, -0.22);//왼쪽 뿔 시작점
	glRotatef(35.0, 0.0, 1.0, 0.0);//35도 y축 기준 회전
	gluCylinder(cyl_6_10, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	/*오른쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.16, 0.0, -0.22);//오른쪽 뿔 시작점
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35도 y축 기준 회전
	gluCylinder(cyl_6_10, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.	
	glPushMatrix();// 처음 저장 좌표 다시 저장

	/*왼쪽 눈 그리기*/
	glTranslatef(-0.1, 0.1, 0.13);//왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0);// 눈 컬러 설정(흑색)
	gluSphere(cyl_6_10, 0.03, 10, 10);

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	/*오른쪽 눈 그리기*/
	glTranslatef(0.1, 0.1, 0.13);//오른쪽 눈 시작점
	gluSphere(cyl_6_10, 0.03, 10, 10);
	glPopMatrix();// 처음 저장 좌표 다시 저장
}
/*
안드로이드 전체 모습을 그리는 함수
*/
void DrawAndroid()
{
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x_6_10, 1, 0, 0);//우측팔뚝
	if (key == ROCKET) DrawR_HandRocket(); // 로켓모드일때 우측로켓호출
	else DrawR_Hand(R_Arm_y_6_10, 1, 0, 0);  //우측팔호출
	DrawL_Arm(L_Arm_x_6_10, 1, 0, 0);   //좌측팔뚝
	if (key == ROCKET) DrawL_HandRocket(); // 로켓모드일때 우측로켓호출
	else DrawL_Hand(L_Arm_y_6_10, 1, 0, 0);//좌측손호출
	DrawL_Legs(L_Leg_x_6_10, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y_6_10, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x_6_10, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y_6_10, 1, 0, 0);  //우측발	
}

/*
로봇이 달리는 것을 표현한 함수.
로봇의 관절이 움직이는 것을 표현했고,
로봇이 달리면서 상,하,좌,우로 움직이는 모습을 표현했다.
*/
void Run()
{
	glLoadIdentity();//CTM 초기화
	/*
	기본적인 로봇의 움직임의 가속도는 sin() 함수를 통해 표현하였다
	또한 관절의 제한범위를 생각하여 abs() 함수를 통해 관절의 움직임을 제한하였다.
	*/
	L_Arm_x_6_10 = sin(time_6_10) * 80;           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = -L_Arm_x_6_10;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
	R_Arm_y_6_10 = -abs(sin(time_6_10) * 60 + 50);  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
	L_Arm_y_6_10 = -abs(-sin(time_6_10) * 60 + 50); //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

	R_Leg_y_6_10 = abs(-sin(time_6_10) * 30 - 30);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time_6_10) * 30 - 30);   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time_6_10) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawGround();    //지면 호출
	glLoadIdentity();//CTM 초기화

	/*
	로봇이 달리면서 앞,뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
	*/
	glRotatef(-230.0, 0, 1, 0);//y축으로 기울임
	glRotatef(abs(sin(time_6_10) * 16), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	glRotatef(sin(time_6_10) * 16, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	/*
	로봇이 달리면서 상,하로 움직이는 것을 표현
	*/
	float i = 0;
	i = abs(sin(time_6_10) * 0.08); //i변수값 설정
	glPushMatrix();// 처음 저장 좌표 다시 저장
	glTranslatef(0.0, i, 0); //변수 i만큼 로봇의 몸체가 Y축기준으로 움직임.

	glTranslatef(0.0, 0.5, 0.0);//최초 로봇의 위치 
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

/*
로봇이 잽을 날리는 것을 표현한 함수
*/
void Jap()
{
	glLoadIdentity();//CTM 초기화
	/*
	로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
	*/
	L_Arm_x_6_10 = (-40) + sin(time2_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;      //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time2_6_10) * 80);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time2_6_10) * 80); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time2_6_10) * 30 - 20);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time2_6_10) * 30 - 20);   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time2_6_10) * 30;          //우측다리는 30도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 30도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawGround(); //지면 호출
	glLoadIdentity(); //CTM 초기화

	glRotatef(-230.0, 0, 1, 0); //y축기준으로 회전

	glRotatef(sin(time2_6_10) * 10, 0, 0, 1);//로봇의 좌,우 반동 표현(좌우로 10도 만큼 주기적인 움직임 설정)

	/*
	로봇이 잽을 날리면서 상,하로 움직이는 것을 표현
	*/
	float j = 0;
	j = abs(sin(time2_6_10) * 0.085);// j값 설정
	glPushMatrix();// 처음 저장 좌표 다시 저장
	glTranslatef(0.0, j, 0); //변수 j만큼 로봇의 몸체가 Y축기준으로 움직임.
	glTranslatef(0.0, 0.5, 0.0);//최초 위치 
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

/*
로봇이 퇴장할때 크기 변환을 표현한 함수
*/
void ex()
{
	glLoadIdentity(); //CTM 초기화
	/*
	로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
	*/
	L_Arm_x_6_10 = (-40) + sin(time6_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;      //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time6_6_10) * 10);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time6_6_10) * 10);  //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time6_6_10) * 30 - 30);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time6_6_10) * 30 - 30);  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time6_6_10) * 60;           //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	glLoadIdentity(); //CTM 초기화
	glRotatef(-180, 0, 1, 0); //y축 기준으로 회전
	glRotatef(time6_6_10, 0, 0, 1); //time6 변수만큼 z축기준으로 회전

	glScalef(0.4 / (sin(time3_6_10)), 0.4 / (sin(time3_6_10)), 0.4 / (sin(time3_6_10))); //0.4의 크기에서 sin()를 통한 크기조절을 주기적으로 가함에따라 

	glPushMatrix();// 처음 저장 좌표 다시 저장															  //멀어지고 가까워지는듯한 느낌을 표현
	glTranslatef(0.0, 0.5, 0.0);//최초 위치 
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}
/*
김연아 선수의 모션을 취하는 함수
*/
void Show()
{
	glLoadIdentity(); //CTM 초기화

	/*
	로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
	*/
	L_Arm_x_6_10 = (-40) + sin(time2_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;       //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time2_6_10) * 10);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time2_6_10) * 10); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time2_6_10) * 30 - 30); //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time2_6_10) * 30 - 30);  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time2_6_10) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;             //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawGround(); //지면 호출
	glLoadIdentity(); //CTM 초기화
	glRotatef(-230.0, 0, 1, 0); //y축기준으로 회전

	/*
	로봇이 피겨동작시 몸이 틀어지는 것을 표현
	*/
	glRotatef(sin(time2_6_10) * 7, 0, 0, 1); //z축기준으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)
	glRotatef(sin(time2_6_10) * 7, 0, 1, 0); //y축으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)

	//로봇 몸체 각도 조절
	glTranslatef(0.0, 0.18, 0.0); //y축으로 이동
	glRotatef(80, 1, 0, 0);        //x축 기준으로 회전

	glTranslatef(0.0, 0.5, 0.0);//최초 위치 

	glPushMatrix(); // 처음 저장 위치

	DrawBody(0, 0, 0, 0); // 몸통 함수 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	Drawneck(); // 목함수 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//머리 위치 설정
	glRotatef(-75, 1, 0, 0); //x축기준으로 회전(머리를 위쪽으로 돌리기)
	glTranslatef(0.0, -0.02, 0.0); //y축으로 이동 (머리 시작점)

	DrawHead(); // 머리 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//우측전체팔 위치 설정


	DrawR_Arm((R_Arm_y_6_10 + 30), 1, 0, 0);  //우측팔호출
	DrawR_Hand(-(R_Arm_y_6_10 - 15), 1, 0, 0); //우측팔뚝

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//좌측전체팔 위치 설정
	glTranslatef(0.0, -0.16, -0.04);//y축,z축으로 이동(좌측팔 시작점)
	glRotatef(40, 0, 0, 1);     //z축 기준으로 회전

	DrawL_Arm((L_Arm_y_6_10 + 30), 1, 0, 0);   //좌측팔호출	
	DrawL_Hand(-(L_Arm_y_6_10 - 15), 1, 0, 0);  //좌측팔뚝

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//좌측전체 다리 위치 설정
	glTranslatef(0.0, -0.45, -0.25);//y축,z축으로 이동(좌측다리 시작점)
	glRotatef(-90, 1, 0, 0);  //x축 기준으로 회전

	DrawL_Legs(-30, 1, 0, 0);  //좌측다리
	DrawL_foot(10, 1, 0, 0);  //좌측종아리		 

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//우측전체 다리 위치 설정
	glTranslatef(0.0, -0.5, -0.5);//y축,z축으로 이동(우측다리 시작점)
	glRotatef(-90, 1, 0, 0); //x축 기준으로 회전

	DrawR_Legs(160, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y_6_10, 1, 0, 0);  //우측종아리		

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.

	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}
/*
로봇이 로켓을 날리는 모습을 표현한 함수
*/
void Rocket()
{
	glLoadIdentity(); //CTM 초기화

	/*90도 각도로 팔을 앞으로 내민다*/
	L_Arm_x_6_10 = -90;
	R_Arm_x_6_10 = -90;

	R_6_10 = 2 * abs(-sin(time2_6_10) * 0.2 - 0.2) + 0.2;//우측 로켓 움직임 설정
	//abs절대값으로 로켓이 앞쪽으로 나가게 설정.
	//+0.2를 통해 로켓의 처음위치 조절. 2*를 통해 로켓이 나가는 거리조절.
	//sin()함수를 통해 주기적인 움직임 설정.

	R2_6_10 = 2 * abs(sin(time2_6_10) * 0.2 - 0.2) + 0.2;//좌측 로켓 움직임 설정 
	//abs절대값으로 로켓이 앞쪽으로 나가게 설정.
	//+0.2를 통해 로켓의 처음위치 조절. 2*를 통해 로켓이 나가는 거리조절.
	//sin()함수를 통해 주기적인 움직임 설정.

	R_Leg_y_6_10 = abs(-sin(time2_6_10) * 30 - 30);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time2_6_10) * 30 - 30);   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time2_6_10) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawGround(); //지면 호출

	glLoadIdentity(); //CTM 초기화
	glPushMatrix();// 처음 저장 좌표 다시 저장
	glRotatef(-230.0, 0, 1, 0); //y축 기준으로 회전

	/*
	로봇이 로켓을 쏠 때 상,하,좌,우로 몸을 트는 모습을 설정
	*/
	glRotatef(-abs(sin(time2_6_10) * 8), 1, 0, 0); //x축으로 8도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	glRotatef(sin(time2_6_10) * 7, 0, 0, 1);       //z축으로 7도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	/*
	로봇이 로켓을 날리며 몸을 튕기는 모습을 표현
	*/
	float i = 0;
	i = abs(sin(time2_6_10) * 0.08); //i값 설정 
	glTranslatef(0.0, i, 0); //변수 i만큼 이동
	glTranslatef(0.0, 0.5, 0.0);//최초 위치 
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_6_10()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면 지우기

	GLfloat CurrentTime = glfwGetTime();
	GLfloat DeltaTime = CurrentTime - LastTime_6_10;

	time_6_10 = time_6_10 + 2.5f * DeltaTime;//달릴때 쓰인 타이머 변수
	time2_6_10 = time2_6_10 + 12.5f * DeltaTime;//잽을 날릴때 쓰인 타이머 변수
	time3_6_10 = time3_6_10 + 0.25f * DeltaTime;//로켓을 날릴때 쓰인 타이머 번수, 종료시 로봇이 뱅글뱅글 돌아가게 하기 위해 쓰인 타이머 변수
	time4_6_10 = time4_6_10 + 25.f * DeltaTime;//김연아 선수 모션을 취할때 쓰인 타이머 변수

	LastTime_6_10 = CurrentTime;

	if (key == RUN)
	{
		Run();
		glPopMatrix();
	}
	else if (key == JAP)
	{
		Jap();
		glPopMatrix();
	}
	else if (key == ROCKET)
	{
		Rocket();
		glPopMatrix();
	}
	else if (key == YUNA)
	{
		Show();
		glPopMatrix();
	}
	else if (key == EXIT)
	{
		ex();
		glPopMatrix();
	}
}

void UTOutputWindow::Code_6_10_End()
{
	ResetAll();
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	sndPlaySound(NULL, SND_ASYNC);
}

/*
키보드 콜백 설정 함수
w를 누르면 wire 모드로, s를 누르면 solid 모드로
*/
void UTOutputWindow::Code_6_10_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action == GLFW_PRESS)
	{
		switch (Key)
		{
		case GLFW_KEY_1:
			key = 1;
			break;
		case GLFW_KEY_2:
			key = 2;
			break;
		case GLFW_KEY_3:
			key = 3;
			break;
		case GLFW_KEY_4:
			key = 4;
			break;
		case GLFW_KEY_5:
			key = 5;
			break;
		case GLFW_KEY_W:
			flag_6_10 = 1;
			break;
		case GLFW_KEY_S:
			flag_6_10 = 0;
			break;
		case GLFW_KEY_Q:
			key = 6;
			break;
		}
	}
}