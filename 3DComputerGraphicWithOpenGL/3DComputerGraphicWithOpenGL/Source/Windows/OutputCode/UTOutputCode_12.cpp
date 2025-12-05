// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "CoreMinimal.h"
#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
//#include "glad/glad.h"

void UTOutputWindow::Code_12_8_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), UTOutputWindow::Code_12_8_Key);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.1f, 0.1f, 0.2f, 0.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, 1.f, 0.f, 1.f,-1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);

	StartX_12_8 = display_w / 8, StartY_12_8 = display_h / 8;
	EndX_12_8 = display_w / 4 + display_w / 8, EndY_12_8 = display_h / 4 + display_h / 8;

	MAIN_WINDOW->DebugContext = L"화살표 키로 시저 박스 이동";
}

void UTOutputWindow::Code_12_8()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 시저 테스트 전 장면
	glEnable(GL_BLEND);
	glViewport(0, 0, display_w, display_h / 2);
	glPushMatrix();
	DrawScene_12_8();
	glPopMatrix();

	// 시저 박스 그리기
	glColor4f(0.8f, 0.8f, 0.8f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f((GLfloat)StartX_12_8 / (GLfloat)display_w, (GLfloat)StartY_12_8 / (GLfloat)display_h * 2.f, 1.f);
	glVertex3f((GLfloat)StartX_12_8 / (GLfloat)display_w, (GLfloat)EndY_12_8 / (GLfloat)display_h * 2.f, 1.f);
	glVertex3f((GLfloat)EndX_12_8 / (GLfloat)display_w, (GLfloat)EndY_12_8 / (GLfloat)display_h * 2.f, 1.f);
	glVertex3f((GLfloat)EndX_12_8 / (GLfloat)display_w, (GLfloat)StartY_12_8 / (GLfloat)display_h * 2.f, 1.f);
	glEnd();
	glDisable(GL_BLEND);
	
	// 시저 테스트 이후 장면
	glEnable(GL_SCISSOR_TEST);
	int scissorX = StartX_12_8;
	int scissorY = StartY_12_8 + display_h / 2;
	int scissorW = EndX_12_8 - StartX_12_8;
	int scissorH = EndY_12_8 - StartY_12_8;
	glScissor(scissorX, scissorY, scissorW, scissorH);
	glViewport(0, display_h / 2, display_w, display_h / 2);
	glPushMatrix();
	DrawScene_12_8(); 
	glPopMatrix();
	glDisable(GL_SCISSOR_TEST);
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_12_8_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	ResetAll();
	glBindVertexArray(0);

	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_12_8_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if(Action != GLFW_PRESS)
		return;

	int display_w{}, display_h{};
	glfwGetWindowSize(OUTPUT_WINDOW->GetGLFWWindow(), &display_w, &display_h);

	switch (Key)
	{
	case GLFW_KEY_RIGHT:
		if (OUTPUT_WINDOW->EndX_12_8 + 10 <= display_w)
		{
			OUTPUT_WINDOW->StartX_12_8 += 10; OUTPUT_WINDOW->EndX_12_8 += 10;
		}
		break;
	case GLFW_KEY_LEFT:
		if (OUTPUT_WINDOW->StartX_12_8 - 10 > 0)
		{
			OUTPUT_WINDOW->StartX_12_8 -= 10; OUTPUT_WINDOW->EndX_12_8 -= 10;
		}
		break;
	case GLFW_KEY_UP:
		if (OUTPUT_WINDOW->EndY_12_8 + 10 < display_h / 2)
		{
			OUTPUT_WINDOW->StartY_12_8 += 10; OUTPUT_WINDOW->EndY_12_8 += 10;
		}
		break;
	case GLFW_KEY_DOWN:
		if (OUTPUT_WINDOW->StartY_12_8 - 10 > 0)
		{
			OUTPUT_WINDOW->StartY_12_8 -= 10; OUTPUT_WINDOW->EndY_12_8 -= 10;
		}
		break;
	}
}

void UTOutputWindow::DrawScene_12_8()
{
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 1.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.25f, 0.5f, 0.f);
	glVertex3f(0.5f, 0.f, 0.f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.f, 0.f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(0.5f, 0.3f, 0.f);
	glVertex3f(0.7f, 0.85f, 0.f);
	glVertex3f(0.9f, 0.85f, 0.f);
	glVertex3f(0.7f, 0.3f, 0.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.1f);
	glTranslatef(0.75f, 0.15f, 0.f);
	
	glBegin(GL_TRIANGLE_FAN);
	constexpr int circle_segments = 100;
	glVertex3f(0.f, 0.f, 0.f);
	for (int i = 0; i <= circle_segments; ++i)
	{
		const float angle = i * 2.0f * 3.1415926f / circle_segments;
		const float x = 0.1f * cosf(angle);
		const float y = 0.1f * sinf(angle);
		glVertex3f(x, y, 0.f);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 0.6f, 0.f);
	glVertex3f(0.25f, 0.9f, 0.f);
	glVertex3f(0.25f, 0.6f, 0.f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.1f, 0.7f, 0.9f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3f, 0.6f, 0.f);
	glVertex3f(0.3f, 0.9f, 0.f);
	glVertex3f(0.55f, 0.6f, 0.f);
	glEnd();
	glPopMatrix();
}