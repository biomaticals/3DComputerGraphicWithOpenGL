// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_9_10_Start()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"지엘에서 점, 선을 그리고 선분과 다각형을 보간에 의해 채우는 것을 보여줍니다.\n";
}

void UTOutputWindow::Code_9_10()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

	// 좌측 상단
	glViewport(0, display_h / 2, display_w / 2, display_h / 2);
	GLfloat Angle{};
	GLfloat Size[2]{};
	glGetFloatv(GL_POINT_SIZE_RANGE, Size);
	glPointSize(Size[0] * 10.f);
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_POINTS);
	for(Angle = 0.f; Angle <= 2.f * 3.14f ; Angle += 3.14f / 20.f)
	{
		glVertex2f(0.5f * cosf(Angle), 0.5f * sinf(Angle));
	}
	glEnd();

	// 우측 상단
	glViewport(display_w / 2, display_h / 2, display_w / 2, display_h / 2);
	GLint ScaleFactor = 1;
	GLushort Pattern = 0x00ff;
	GLfloat Height;
	glColor3f(0.f, 1.f, 0.f);
	glLineWidth(3.f);
	glEnable(GL_LINE_STIPPLE);
	for (Height = -0.9f; Height <= 0.9f; Height += 0.4)
	{
		glLineStipple(ScaleFactor, Pattern);
		glBegin(GL_LINES);
		glVertex3f(-1.f, Height, 0.f);
		glVertex3f(1.f, Height, 0.f);
		glEnd();
		ScaleFactor *= 2;
	}
	glDisable(GL_LINE_STIPPLE);

	// 좌측 하단
	glViewport(0, 0, display_w / 2, display_h / 2);
	glLineWidth(10.f);
	glBegin(GL_LINES);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(-1.f, 0.f, 0.f);
	glColor3f(0.f, 0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);
	glEnd();

	// 우측 하단
	glViewport(display_w / 2, 0, display_w / 2, display_h / 2);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-0.5f, -0.5f, 0.f);
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.5f, -0.5f, 0.f);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 0.5f, 0.f);
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_9_10_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	glPointSize(1.f);
	glLineWidth(1.f);

	MAIN_WINDOW->ExplanationContext = L"";
	glNormal3f(0.f, 0.f, 1.f);
}

void UTOutputWindow::Code_9_15_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), Code_9_15_Key);

	Time_9_15 = (GLfloat)glfwGetTime();

	MAIN_WINDOW->ExplanationContext = L"Smooth, Blend 기능을 활용하여 점과 선분을 안티에일리어싱하는 예제입니다.\n";
}

void UTOutputWindow::Code_9_15()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

	if(bChangePalette)
	{
		GLfloat Delta = glfwGetTime() - Time_9_15;
		ElapsedTime_9_15 += Delta;

		if (ElapsedTime_9_15 > 2.f)
		{
			if (++Index_9_15 > 15)
				Index_9_15 = 0;

			Time_9_15 = glfwGetTime();
			ElapsedTime_9_15 = 0.f;
		}
	}

	GLint Red = PALETTE[Index_9_15][0];
	GLint Green = PALETTE[Index_9_15][2];
	GLint Blue = PALETTE[Index_9_15][1];
	glColor3f(Red, Green, Blue);
	
	if (bSmooth_9_15)
	{
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}
	
	if (bBlend_9_15)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glPointSize(12.f);
	glBegin(GL_POINTS);
	glVertex3f(-0.9f, 0.15f, 0.f);
	glVertex3f(-0.9f, 0.25f, 0.f);
	glVertex3f(-0.9f, 0.35f, 0.f);
	glVertex3f(-0.9f, 0.45f, 0.f);
	glEnd();

	for (GLfloat i = 0.f ; i < 1.f ; i += 0.1f)
	{
		glBegin(GL_LINES);
		glVertex3f(-1.f + i, 1.0f, 0.f);
		glVertex3f(1.f - i, -1.f, 0.f);
		glVertex3f(-1.f, -1.f + i, 0.f);
		glVertex3f(1.f, 1.f - i, 0.f);
		glEnd();
	}

	if (bSmooth_9_15)
	{
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
	}

	if(bBlend_9_15)
		glDisable(GL_BLEND);

	std::wstringstream wss{};
	wss << L"1 : Smooth 켜기/끄기 (" << (bSmooth_9_15 ? L"켜짐" : L"꺼짐") << L")\n2 : Blend 켜기/끄기 (" << (bBlend_9_15 ? L"켜짐" : L"꺼짐") << L")\n3 : 색깔 바꾸기 (" << (bChangePalette ? L"켜짐" : L"꺼짐") << ")";
	MAIN_WINDOW->DebugContext = wss.str();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_9_15_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext =  L"";

	glPointSize(1.f);
	glLineWidth(1.f);
}

void UTOutputWindow::Code_9_15_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());

	if (Action == GLFW_PRESS)
	{
		switch (Key)
		{
		case GLFW_KEY_1:
		{
			OUTPUT_WINDOW->bSmooth_9_15 = !OUTPUT_WINDOW->bSmooth_9_15;
			break;
		}
		case GLFW_KEY_2:
		{
			OUTPUT_WINDOW->bBlend_9_15 = !OUTPUT_WINDOW->bBlend_9_15;
			break;
		}
		case GLFW_KEY_3:
		{
			OUTPUT_WINDOW->bChangePalette = !OUTPUT_WINDOW->bChangePalette;
			break;
		}
		}
	}
}