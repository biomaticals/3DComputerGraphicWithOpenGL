// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "CoreMinimal.h"
#include "Common.h"
#include "stdio.h"
#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "Manager/ResourceManager.h"
#include<windows.h>
#include<MMSystem.h>
#include<GL/glu.h>
#include<math.h>
#include<cmath>

void UTOutputWindow::Code_6_3_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	MAIN_WINDOW->ExplanationContext = L"행렬 변환의 순서에 따른 결과 차이를 확인하는 예제입니다.\n"
		"원점을 기준으로 45도 회전한 후, x축으로 0.6만큼 이동한 사각형과\n"
		"x축으로 0.6만큼 이동한 후, 45도 회전한 사각형을 비교합니다.\n\n"
		"빨간색 사각형: 먼저 45도 회전 후, x축으로 0.6만큼 이동\n"
		"초록색 사각형: 먼저 x축으로 0.6만큼 이동 후, 45도 회전";
}

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
	glPopAttrib();

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_6_6_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glfwSetKeyCallback(GetGLFWWindow(), Code_6_6_Key);

	MAIN_WINDOW->ExplanationContext = L"행렬 스택을 활용하여 태양,지구,달의 계층적 변환을 구현합니다. glPushMatrix / glPopMatrix를 사용해 각 천체의 공전과 자전을 독립적으로 구성하면서도 부모 변환을 자연스럽게 계승합니다.\n";
	MAIN_WINDOW->DebugContext = L"1: 지구 자전 및 달 공전\n";
	MAIN_WINDOW->DebugContext += L"2: 지구 공전\n";
	MAIN_WINDOW->DebugContext += L"R: 초기화\n";
	MAIN_WINDOW->DebugContext += L"Q: 종료";
}

void UTOutputWindow::Code_6_6()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.f, 0.f, 0.f, 0.f);
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
	glfwMakeContextCurrent(GetGLFWWindow());
	glPopAttrib();

	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
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
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glfwMakeContextCurrent(GetGLFWWindow());

	const std::string basepath = "Resource/Object/Chaynik/";
	const std::string texbasepath = "Resource/Object/Chaynik/textures";
	const std::string objpath = basepath + "Chaynik.obj";
	RESOURCE_MANAGER->LoadObjWithMaterial(objpath, vertices_6_8, indices_6_8, materials_6_8);

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

	MAIN_WINDOW->ExplanationContext = L"조명과 재질 속성을 사용하여 3D 모델을 렌더링하는 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext += L"모델의 표면이 조명에 반응하여 현실감 있는 모습을 보여줍니다.";
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
	glPopAttrib();

	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_6_9_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glfwSetKeyCallback(GetGLFWWindow(), UTOutputWindow::Code_6_9_Key);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	Gravity_6_9 = 9.8f;
	Elastic_6_9 = 0.75f;
	InitialHeight_6_9 = 30.f;
	InitialVerticalVelocity_6_9 = 0.f;
	HorizonalVelocity_6_9 = 5.f;
	Time_6_9 = glfwGetTime();

	GLfloat LightConstantAttenuation_6_9;
	GLfloat LightLinearAttenuation_6_9;
	GLfloat LightQuadraticAttenuation_6_9;

	glGetLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &LightConstantAttenuation_6_9);
	glGetLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &LightLinearAttenuation_6_9);
	glGetLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &LightQuadraticAttenuation_6_9);

	const std::string basepath = "Resource/Object/Soccer_ball/";
	const std::string texbasepath = "Resource/Object/Soccer_ball/textures";
	const std::string objpath = basepath + "10536_soccerball_V1_iterations-2.obj";
	RESOURCE_MANAGER->LoadObjWithMaterial(objpath, vertices_6_9, indices_6_9, materials_6_9);

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

	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glColor3f(1.f, 1.f, 1.f);

	MAIN_WINDOW->ExplanationContext = L"중력과 탄성 계수를 적용한 1차원 탄성 충돌 물리 모델을 사용한 바운싱 볼 시뮬레이션 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext = L"사용자는 중력 가속도, 탄성 계수, 초기 높이, 초기 수직 속도를 조절하여 공의 운동을 실시간으로 관찰할 수 있습니다.\n";
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
	glfwMakeContextCurrent(GetGLFWWindow());
	glPopAttrib();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	
	Time_6_9 = 0.f;

	MAIN_WINDOW->DebugContext = L"";
	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_6_9_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action != GLFW_PRESS)
		return;

	switch (Key)
	{
	case GLFW_KEY_1:
	{
		OUTPUT_WINDOW->Gravity_6_9 += 1.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_2:
	{
		OUTPUT_WINDOW->Gravity_6_9 = OUTPUT_WINDOW->Gravity_6_9 - 1.f > 0.f ? OUTPUT_WINDOW->Gravity_6_9 -1.f : 0.f; 
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_3:
	{
		OUTPUT_WINDOW->Elastic_6_9 = OUTPUT_WINDOW->Elastic_6_9 + 0.05f > 1.f ? 1.f : OUTPUT_WINDOW->Elastic_6_9 + 0.05f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_4:
	{
		OUTPUT_WINDOW->Elastic_6_9 = OUTPUT_WINDOW->Elastic_6_9 - 0.05f > 0.f ? OUTPUT_WINDOW->Elastic_6_9 - 0.05f : 0.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_5:
	{
		OUTPUT_WINDOW->InitialHeight_6_9 += 1.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_6:
	{
		OUTPUT_WINDOW->InitialHeight_6_9 = OUTPUT_WINDOW->InitialHeight_6_9 - 1.f > 0.f ? OUTPUT_WINDOW->InitialHeight_6_9 - 1.f : 0.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_7:
	{
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 += 1.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_8:
	{
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 -= 1.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
		break;
	}
	case GLFW_KEY_R:
	{
		OUTPUT_WINDOW->Gravity_6_9 = 9.8f;
		OUTPUT_WINDOW->Elastic_6_9 = 0.75f;
		OUTPUT_WINDOW->InitialHeight_6_9 = 30.f;
		OUTPUT_WINDOW->InitialVerticalVelocity_6_9 = 0.f;
		OUTPUT_WINDOW->Time_6_9 = glfwGetTime();
	}
	default:
	{
		break;
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

	GLfloat U0 = sqrt(V0 * V0 + 2.f * G * Y0 > 0.f ? V0 * V0 + 2.f * G * Y0 : 0.f);
	if (U0 < eps)
		return 0.f;

	GLfloat t_first_bounce = (V0 + U0) / G;
	if (time < t_first_bounce)
	{
		return Y0 + V0 * time - 0.5f * G * time * time > 0.f ? Y0 + V0 * time - 0.5f * G * time * time : 0.f;
	}

	GLfloat T = t_first_bounce;
	GLfloat U_n = E * U0;
	if (E <= 0.f)
	{
		GLfloat dt_after = 2.f * U_n / G;
		if (time < T + dt_after)
		{
			GLfloat t_in_bounce = time - T;
			return 0.f, t_in_bounce * (U_n * t_in_bounce - 0.5f * G * t_in_bounce) > 0.f ? t_in_bounce * (U_n * t_in_bounce - 0.5f * G * t_in_bounce) : 0.f;
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
			return t_in_bounce * (U_n - 0.5f * G * t_in_bounce) > 0.f ? t_in_bounce * (U_n - 0.5f * G * t_in_bounce) : 0.f;
		}

		T += dt_n;
		U_n *= E;
		if (U_n < eps)
			break;
		n++;
	}
	return 0.f;
}

void UTOutputWindow::Code_6_10_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glfwSetKeyCallback(GetGLFWWindow(), Code_6_10_Key);
	std::wstring MusicPath = RESOURCE_MANAGER->GetSoundPath() + L"\\funny-comedy-cartoon-background-music.mp3";
	if (std::filesystem::exists(MusicPath))
	{
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

	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0,300.0,-700.0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	
	glColor3f(1.f, 1.f, 1.f);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	Time_6_10 = glfwGetTime();
	LastTime_6_10 = Time_6_10;

	MAIN_WINDOW->DebugContext = L"1: 달리기 / 2: 잽 / 3: 로켓 펀치 / 4: 피겨 / 5: 퇴장\n";
	MAIN_WINDOW->DebugContext += L"W: 와이어프레임 드로잉 / S : 솔리드 렌더링 / P : 중지\n";
	MAIN_WINDOW->ExplanationContext = L"고정 파이프라인과 GLU 쿼드릭을 이용해 관절 기반 로봇 캐릭터를 계층적 트랜스폼으로 구성하고,\n";
	MAIN_WINDOW->ExplanationContext += L"키 입력에 따라 서로 다른 애니메이션 동작을 재생하는 시스템입니다.\n";
	MAIN_WINDOW->ExplanationContext += L"각 신체 부위는 실린더·구(Sphere)로 구성되며, glPushMatrix / glPopMatrix를 사용해 부모 - 자식 관계를 유지한 채 회전·이동 변환을 누적하여 자연스러운 관절 움직임을 구현합니다.\n";
	MAIN_WINDOW->ExplanationContext += L"애니메이션은 sin(), cos() 기반의 주기 함수로 관절 각도를 계산하여 달리기, 잽, 로켓펀치, 피겨 동작 등 다양한 모션을 표현합니다.\n";
	MAIN_WINDOW->ExplanationContext += L"또한 Wireframe / Solid 모드 전환, 음악 재생, 조명 설정 등 렌더링 환경 제어 기능도 포함되어 있습니다.\n";
}

void UTOutputWindow::Draw_Color(int i)
{
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

void UTOutputWindow::Change_Wire_Or_Solid(int i)
{ 
	if (flag_6_10 == 1)
		gluQuadricDrawStyle(cyl_6_10, GLU_LINE);
}

void UTOutputWindow::DrawL_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glRotatef(x, a, b, c);
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0);   // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

void UTOutputWindow::DrawL_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();   // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c);        // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	if (key_6_10 == YUNA) gluCylinder(cyl_6_10, 0.05, 0.02, 0.2, 15, 1); // 깔때기 모양 실린더를 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 15, 1);           // 실린더를 그림
	glPopMatrix();
}

void UTOutputWindow::DrawL_HandRocket()
{
	glPushMatrix();
	Draw_Color(key_6_10);     // 색 설정
	cyl_6_10 = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R_6_10); // 왼쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

void UTOutputWindow::DrawR_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);     // 색 설정
	cyl_6_10 = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축을 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); //우측 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); //우측 어깨 -15도 y축기준 회전
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림

}

void UTOutputWindow::DrawR_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.22);//오른쪽 손 시작점
	glRotatef(y, a, b, c);// 파라미터값 만큼 회전
	Change_Wire_Or_Solid(flag_6_10);
	if (key_6_10 == YUNA) gluCylinder(cyl_6_10, 0.05, 0.02, 0.2, 50, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}

void UTOutputWindow::DrawR_HandRocket()
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glTranslatef(0, 0, R2_6_10);//오른주먹 위치 파라미터만큼 이동
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

void UTOutputWindow::DrawBody(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.2, 0.2, 0.45, 50, 1);
	glPopMatrix();
}

void UTOutputWindow::DrawL_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.1, 0.0, 0.42);//왼쪽 허벅지 시작점
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.15, 50, 1);

}

void UTOutputWindow::DrawL_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);//왼쪽 종아리 시작점
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag_6_10);
	if (key_6_10 == YUNA) gluCylinder(cyl_6_10, 0.05, 0.03, 0.2, 50, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

void UTOutputWindow::DrawR_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.1, 0.0, 0.42);//오른쪽 허벅지 시작점
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.05, 0.05, 0.15, 50, 1);

}

void UTOutputWindow::DrawR_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key_6_10);
	cyl_6_10 = gluNewQuadric();

	glTranslatef(0.0, 0.0, 0.18);//오른쪽 종아리 시작점
	glRotatef(y, a, b, c);

	Change_Wire_Or_Solid(flag_6_10);
	if (key_6_10 == YUNA) gluCylinder(cyl_6_10, 0.05, 0.03, 0.2, 15, 1);// 깔때기 모양 실린더 그림
	else gluCylinder(cyl_6_10, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

void UTOutputWindow::Drawneck()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	cyl_6_10 = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.0, 0.0, -0.045); // 목 시작점
	Change_Wire_Or_Solid(flag_6_10);
	gluCylinder(cyl_6_10, 0.2, 0.2, 0.025, 100, 1);
	glPopMatrix();
}

void UTOutputWindow::DrawGround()
{
	Draw_Color(flag_6_10);//색깔 설정
	glTranslatef(0.0, -2.73, 0.0);//땅 시작점
	glRotatef(45.0, 0, 1, 0);//45도만큼 y축 방향으로 회전
	glRotatef(0.0 + time4_6_10 - 15, 0.0, 0.0, 1);// z축 기준으로 time4만큼 땅이 회전 
	Change_Wire_Or_Solid(flag_6_10);
	gluSphere(cyl_6_10, 2.5, 30, 90);
}

void UTOutputWindow::DrawHead()
{
	glTranslatef(0.0, 0.02, 0.0);//머리 시작점
	glPushMatrix();// 처음 저장 좌표 다시 저장
	cyl_6_10 = gluNewQuadric();
	Change_Wire_Or_Solid(flag_6_10);
	Draw_Color(key_6_10);//색깔 설정
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

void UTOutputWindow::DrawAndroid()
{
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x_6_10, 1, 0, 0);//우측팔뚝
	if (key_6_10 == ROCKET) DrawR_HandRocket(); // 로켓모드일때 우측로켓호출
	else DrawR_Hand(R_Arm_y_6_10, 1, 0, 0);  //우측팔호출
	DrawL_Arm(L_Arm_x_6_10, 1, 0, 0);   //좌측팔뚝
	if (key_6_10 == ROCKET) DrawL_HandRocket(); // 로켓모드일때 우측로켓호출
	else DrawL_Hand(L_Arm_y_6_10, 1, 0, 0);//좌측손호출
	DrawL_Legs(L_Leg_x_6_10, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y_6_10, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x_6_10, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y_6_10, 1, 0, 0);  //우측발	
}

void UTOutputWindow::Run()
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

	DrawGround();
	glLoadIdentity();

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
	glPushMatrix();
	glTranslatef(0.0, i, 0); //변수 i만큼 로봇의 몸체가 Y축기준으로 움직임.

	glTranslatef(0.0, 0.5, 0.0);//최초 로봇의 위치 
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Jap()
{
	glLoadIdentity();
	L_Arm_x_6_10 = (-40) + sin(time2_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;      //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time2_6_10) * 80);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time2_6_10) * 80); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time2_6_10) * 30 - 20);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time2_6_10) * 30 - 20);   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time2_6_10) * 30;          //우측다리는 30도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 30도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////
	cyl_6_10 = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();

	glRotatef(-230.0, 0, 1, 0);

	glRotatef(sin(time2_6_10) * 10, 0, 0, 1);//로봇의 좌,우 반동 표현(좌우로 10도 만큼 주기적인 움직임 설정)

	float j = 0;
	j = abs(sin(time2_6_10) * 0.085);
	glPushMatrix();
	glTranslatef(0.0, j, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::ex()
{
	glLoadIdentity();
	L_Arm_x_6_10 = (-40) + sin(time6_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;      //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time6_6_10) * 10);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time6_6_10) * 10);  //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time6_6_10) * 30 - 30);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time6_6_10) * 30 - 30);  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time6_6_10) * 60;           //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////
	cyl_6_10 = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(-180, 0, 1, 0);
	glRotatef(time6_6_10, 0, 0, 1);

	glScalef(0.4 / (sin(time3_6_10)), 0.4 / (sin(time3_6_10)), 0.4 / (sin(time3_6_10))); //0.4의 크기에서 sin()를 통한 크기조절을 주기적으로 가함에따라 

	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Show()
{
	glLoadIdentity();

	L_Arm_x_6_10 = (-40) + sin(time2_6_10) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x_6_10 = (-80) - L_Arm_x_6_10;       //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y_6_10 = -abs(cos(time2_6_10) * 10);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y_6_10 = -abs(-cos(time2_6_10) * 10); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y_6_10 = abs(-sin(time2_6_10) * 30 - 30); //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y_6_10 = abs(sin(time2_6_10) * 30 - 30);  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x_6_10 = sin(time2_6_10) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x_6_10 = -R_Leg_x_6_10;             //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl_6_10 = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glRotatef(-230.0, 0, 1, 0);

	glRotatef(sin(time2_6_10) * 7, 0, 0, 1); //z축기준으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)
	glRotatef(sin(time2_6_10) * 7, 0, 1, 0); //y축으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)

	glTranslatef(0.0, 0.18, 0.0);
	glRotatef(80, 1, 0, 0);

	glTranslatef(0.0, 0.5, 0.0);

	glPushMatrix();

	DrawBody(0, 0, 0, 0);

	glPopMatrix();
	glPushMatrix();

	Drawneck();

	glPopMatrix();
	glPushMatrix();

	glRotatef(-75, 1, 0, 0); //x축기준으로 회전(머리를 위쪽으로 돌리기)
	glTranslatef(0.0, -0.02, 0.0); //y축으로 이동 (머리 시작점)

	DrawHead();

	glPopMatrix();
	glPushMatrix();

	DrawR_Arm((R_Arm_y_6_10 + 30), 1, 0, 0);  //우측팔호출
	DrawR_Hand(-(R_Arm_y_6_10 - 15), 1, 0, 0); //우측팔뚝

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.16, -0.04);//y축,z축으로 이동(좌측팔 시작점)
	glRotatef(40, 0, 0, 1);     //z축 기준으로 회전

	DrawL_Arm((L_Arm_y_6_10 + 30), 1, 0, 0);   //좌측팔호출	
	DrawL_Hand(-(L_Arm_y_6_10 - 15), 1, 0, 0);  //좌측팔뚝

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.45, -0.25);//y축,z축으로 이동(좌측다리 시작점)
	glRotatef(-90, 1, 0, 0);  //x축 기준으로 회전

	DrawL_Legs(-30, 1, 0, 0);  //좌측다리
	DrawL_foot(10, 1, 0, 0);  //좌측종아리		 

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.5, -0.5);//y축,z축으로 이동(우측다리 시작점)
	glRotatef(-90, 1, 0, 0); //x축 기준으로 회전

	DrawR_Legs(160, 1, 0, 0);
	DrawR_foot(R_Leg_y_6_10, 1, 0, 0);

	glPopMatrix();

	glfwSwapBuffers(OUTPUT_WINDOW->GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Rocket()
{
	glLoadIdentity();

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

	DrawGround();

	glLoadIdentity();
	glPushMatrix();
	glRotatef(-230.0, 0, 1, 0);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat CurrentTime = glfwGetTime();
	GLfloat DeltaTime = CurrentTime - LastTime_6_10;

	time_6_10 = time_6_10 + 2.5f * DeltaTime;
	time2_6_10 = time2_6_10 + 12.5f * DeltaTime;
	time3_6_10 = time3_6_10 + 0.25f * DeltaTime;
	time4_6_10 = time4_6_10 + 25.f * DeltaTime;

	LastTime_6_10 = CurrentTime;

	if (key_6_10 == RUN)
	{
		Run();
		glPopMatrix();
	}
	else if (key_6_10 == JAP)
	{
		Jap();
		glPopMatrix();
	}
	else if (key_6_10 == ROCKET)
	{
		Rocket();
		glPopMatrix();
	}
	else if (key_6_10 == YUNA)
	{
		Show();
		glPopMatrix();
	}
	else if (key_6_10 == EXIT)
	{
		ex();
		glPopMatrix();
	}
	glFlush();
}

void UTOutputWindow::Code_6_10_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPopAttrib();
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	mciSendStringW(L"close bgm", NULL, 0, NULL);

	Time_6_10 = glfwGetTime();
	LastTime_6_10 = Time_6_10;


	MAIN_WINDOW->DebugContext = L"";
	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_6_10_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action == GLFW_PRESS)
	{
		switch (Key)
		{
		case GLFW_KEY_1:
			OUTPUT_WINDOW->key_6_10 = 1;
			break;
		case GLFW_KEY_2:
			OUTPUT_WINDOW->key_6_10 = 2;
			break;
		case GLFW_KEY_3:
			OUTPUT_WINDOW->key_6_10 = 3;
			break;
		case GLFW_KEY_4:
			OUTPUT_WINDOW->key_6_10 = 4;
			break;
		case GLFW_KEY_5:
			OUTPUT_WINDOW->key_6_10 = 5;
			break;
		case GLFW_KEY_W:
			OUTPUT_WINDOW->flag_6_10 = 1;
			break;
		case GLFW_KEY_S:
			OUTPUT_WINDOW->flag_6_10 = 0;
			break;
		case GLFW_KEY_P:
			OUTPUT_WINDOW->key_6_10 = 6;
			break;
		}
	}
}