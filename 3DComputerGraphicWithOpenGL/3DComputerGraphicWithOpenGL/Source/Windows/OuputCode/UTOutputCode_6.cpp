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
	glColor3f(1.f, 1.f, 1.f);
	// 원점

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