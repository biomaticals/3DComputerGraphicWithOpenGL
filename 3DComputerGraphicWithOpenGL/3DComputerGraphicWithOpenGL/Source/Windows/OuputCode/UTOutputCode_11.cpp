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

void UTOutputWindow::Code_11_9_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	GLfloat mat_diffuse[] = { 0.25, 0.25, 1., 0. };
	GLfloat mat_specular[] = { 1., 1., 1., 0. };
	GLfloat light_position[] = { 10., 10., 20., 1. };
	GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0. };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	GLubyte stripeImage[4 * 32];
	for (int j = 0; j < 32; j++)
	{
		stripeImage[4 * j] = 255;
		stripeImage[4 * j + 1] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 2] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 3] = 0;
	}

	glGenTextures(1, &TextureObject_11_7);
	glBindTexture(GL_TEXTURE_1D, TextureObject_11_7);
	glTexImage1D(GL_TEXTURE_1D, 0, 4, 32, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
	
	QuardricObj_11_7 = gluNewQuadric();
	gluQuadricDrawStyle(QuardricObj_11_7, GLU_FILL);
}

void UTOutputWindow::Code_11_9()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.f, (GLfloat)display_w / (GLfloat)display_h, 1.f, 10.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, -1.f);

	gluSphere(QuardricObj_11_7, 1.5f, 40, 40);

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_11_9_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	ResetAll();
	
	glBindTexture(GL_TEXTURE_1D, 0);
	gluDeleteQuadric(QuardricObj_11_7);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_1D);
}