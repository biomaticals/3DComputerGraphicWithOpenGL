// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_5_2()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_4()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.f, 1.f, 1.f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_5_Start()
{
	glfwSetFramebufferSizeCallback(GetGLFWWindow(), Code_5_5_Reshape);
}

void UTOutputWindow::Code_5_5()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_5_End()
{
	glfwSetFramebufferSizeCallback(GetGLFWWindow(), NULL);
}

void UTOutputWindow::Code_5_5_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight)
{
	int display_w, display_h;
	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)display_w;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)display_h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f * WidthFactor, 1.f * WidthFactor, -1.f * HeightFactor, 1.f * HeightFactor, -1.f, 1.f);
}

void UTOutputWindow::Code_5_6_Start()
{
	glfwSetKeyCallback(GetGLFWWindow(), Code_5_6_Key);
}

void UTOutputWindow::Code_5_6()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_6_End()
{
	glfwSetKeyCallback(GetGLFWWindow(), NULL);
}

void UTOutputWindow::Code_5_6_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{
	case GLFW_KEY_Q:
	{
		if (Action == GLFW_PRESS)
		{
			exit(0);
			break;
		}
		break;
	}
	}
}

void UTOutputWindow::Code_5_7_Start()
{
	glfwSetMouseButtonCallback(GetGLFWWindow(), Code_5_7_MouseButton);
	glfwSetCursorPosCallback(GetGLFWWindow(), Code_5_7_CursorPosition);
}

void UTOutputWindow::Code_5_7()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f((float)TopLeftX_5_7/display_w, (float)(display_h - TopLeftY_5_7)/display_h, 0.f);
	glVertex3f((float)TopLeftX_5_7/display_w, (float)(display_h - BottomRightY_5_7)/display_h, 0.f);
	glVertex3f((float)BottomRightX_5_7/display_w, (float)(display_h - BottomRightY_5_7)/display_h, 0.f);
	glVertex3f((float)BottomRightX_5_7/display_w, (float)(display_h - TopLeftY_5_7)/display_h, 0.f);
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_7_End()
{
	glfwSetMouseButtonCallback(GetGLFWWindow(), NULL);
	glfwSetCursorPosCallback(GetGLFWWindow(), NULL);
	TopLeftX_5_7 = -1;
	TopLeftY_5_7 = -1;
	BottomRightX_5_7 = 0;
	BottomRightY_5_7 = 0;
}

void UTOutputWindow::Code_5_7_MouseButton(GLFWwindow* Window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(Window, &xpos, &ypos);
		OUTPUT_WINDOW->TopLeftX_5_7 = static_cast<GLint>(xpos);
		OUTPUT_WINDOW->TopLeftY_5_7 = static_cast<GLint>(ypos);
	}
}

void UTOutputWindow::Code_5_7_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
	OUTPUT_WINDOW->BottomRightX_5_7 = static_cast<GLint>(xpos);
	OUTPUT_WINDOW->BottomRightY_5_7 = static_cast<GLint>(ypos);
}