// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_9_10_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	ResetAll();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
}