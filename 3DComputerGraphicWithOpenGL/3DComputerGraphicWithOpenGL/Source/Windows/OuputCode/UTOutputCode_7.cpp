// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_7_1_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	const std::string basepath = "Resource/Object/Chaynik/";
	const std::string texbasepath = "Resource/Object/Chaynik/textures";
	const std::string objpath = basepath + "Chaynik.obj";
	LoadObjWithMaterial(objpath, vertices_7_1, indices_7_1, materials_7_1);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glClearColor(0.f, 0.f, 0.f, 1.f);
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

void UTOutputWindow::Code_7_1()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glViewport(0, 0, display_w / 2, display_h / 2);
	glPushMatrix();
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		Code_7_1_DrawScene();
		glPopMatrix();
	glPopMatrix();
	
 	glViewport(display_w / 2, 0, display_w / 2, display_h / 2);
 	glPushMatrix();
 		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 		Code_7_1_DrawScene();
 	glPopMatrix();
 	
 	glViewport(0, display_h / 2, display_w / 2, display_h / 2);
 	glPushMatrix();
 		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
 		Code_7_1_DrawScene();
 	glPopMatrix();
 	
 	glViewport(display_w / 2, display_h / 2, display_w / 2, display_h / 2);
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 		glLoadIdentity();
 		gluPerspective(30, 1.0, 0.001, 10.0);
 		glMatrixMode(GL_MODELVIEW);
 		glPushMatrix();
 			gluLookAt(1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 			Code_7_1_DrawScene();
 		glPopMatrix();
 		glMatrixMode(GL_PROJECTION);
 	glPopMatrix();

	glfwSwapBuffers(GetGLFWWindow());
	//glFlush();
}

void UTOutputWindow::Code_7_1_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
}

void UTOutputWindow::Code_7_1_DrawScene()
{
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
		//glTranslatef(0.0, -1.0, 0.0);
		glBegin(GL_QUADS);
			glVertex3f(2.0, 0.0, 2.0);
			glVertex3f(2.0, 0.0, -2.0);
			glVertex3f(-2.0, 0.0, -2.0);
			glVertex3f(-2.0, 0.0, 2.0);
		glEnd();
	glPopMatrix();

// 	glColor3f(0.3, 0.3, 0.7);
	glPushMatrix();
		//glTranslatef(0.0, 0.0, -0.5);
		glBegin(GL_TRIANGLES);
		for(GLint i = 0; i < indices_7_1.size(); i++)
		{
			const Vertex& v = vertices_7_1[indices_7_1[i]];
			glTexCoord2f(v.texcoord.x, v.texcoord.y);
			glNormal3f(v.normal.x, v.normal.y, v.normal.z);
			glVertex3f(v.pos.x, v.pos.y, v.pos.z);
		}
		glEnd();
	glPopMatrix();
}