// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_6_3()
{
	printf("ctx=%p",(void*)glfwGetCurrentContext());


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