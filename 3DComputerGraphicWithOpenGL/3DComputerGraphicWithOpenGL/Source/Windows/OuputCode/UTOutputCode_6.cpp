// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

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
	for(int i = 0 ; i < 360 ; i += 30)
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
	for(int i = 0 ; i < 360 ; i += 30)
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
	for(int i = 0 ; i < 360 ; i += 30)
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
	glOrtho(0.f, 100.f, -7.5f, 100.f, -10.f, 10.f);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	BoundcingBall_physics Physics{};
	Physics.Gravity = Gravity_6_9; // 중력 가속도
	Physics.Elastic = Elastic_6_9; // 탄성 계수
	Physics.IniitlaiHeight = InitialHeight_6_9; // 초기 높이
	Physics.InitialVerticalVelocity = InitialVerticalVelocity_6_9; // 초기 수직 속도
	Physics.HorizonalVelocity = HorizonalVelocity_6_9; // 수평 속도

	GLfloat currentTime = glfwGetTime();
	GLfloat deltaTime = (currentTime - Time_6_9);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, materials_6_9[0].textureId);

	std::array<GLfloat, 2> BallPosition = GetBallState_6_9(Physics, deltaTime);
	glBegin(GL_TRIANGLES);
	for(size_t i = 0 ; i < indices_6_9.size() ; i++)
	{
		const Vertex& v = vertices_6_9[indices_6_9[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x + BallPosition[0], v.pos.y + BallPosition[1], v.pos.z);
	}
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_6_9_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.f, 1.f, 1.f);
	Time_6_9 = 0.f;
}

void UTOutputWindow::Code_6_9_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{
		if (Action != GLFW_PRESS)
			return;

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
	}
}

std::array<GLfloat, 2> 	UTOutputWindow::GetBallState_6_9(const BoundcingBall_physics Physics, const GLfloat Time)
{
	std::array<GLfloat, 2> Position{};
	Position[0] = Physics.HorizonalVelocity* Time;
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
	if(U0 < eps)
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
		if(time < T + dt_after)
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

void UTOutputWindow::Code_6_10_Start()
{
	ResetAll();
}

void UTOutputWindow::Code_6_10()
{

}

void UTOutputWindow::Code_6_10_End()
{

}