// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_11_7_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	for (int i = 0; i < Width_11_7; i++)
	{
		for (int j = 0; j < Height_11_7; j++)
		{
			GLubyte BlackWhite = ((i + j) % 2) * 255;
			Texture_11_7[i][j][0] = BlackWhite;
			Texture_11_7[i][j][1] = BlackWhite;
			Texture_11_7[i][j][2] = BlackWhite;
		}
	}
}

void UTOutputWindow::Code_11_7()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width_11_7, Height_11_7, 0, GL_RGB, GL_UNSIGNED_BYTE, &Texture_11_7);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_11_7_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	ResetAll();
}