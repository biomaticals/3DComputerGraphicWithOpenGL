// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_8_3_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	const std::string basepath = "Resource/Object/Chaynik/";
	const std::string texbasepath = "Resource/Object/Chaynik/textures";
	const std::string objpath = basepath + "Chaynik.obj";
	RESOURCE_MANAGER->LoadObjWithMaterial(objpath, vertices_8_3, indices_8_3, materials_8_3);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

	MAIN_WINDOW->ExplanationContext = L"후면 제거 및 깊이버퍼 테스트로 인한 은면의 효과를 비교하는 예제입니다.\n";
	MAIN_WINDOW->DebugContext = L"좌하단: 후면, 은면 모두 존재\n";
	MAIN_WINDOW->DebugContext += L"우하단 : 후면 제거\n";
	MAIN_WINDOW->DebugContext += L"좌상단 : 후면, 은면 제거\n";
	MAIN_WINDOW->DebugContext += L"우상단 : 은면 제거\n";
}

void UTOutputWindow::Code_8_3()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// 좌하단 - 후면, 은면 모두 존재
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, display_w / 2, display_h / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < indices_8_3.size(); i++)
	{
		const Vertex& v = vertices_8_3[indices_8_3[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();
	glPopMatrix();
	glFlush();

	// 우하단 - 후면 제거
	glClear(GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glViewport(display_w / 2, 0, display_w / 2, display_h / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < indices_8_3.size(); i++)
	{
		const Vertex& v = vertices_8_3[indices_8_3[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();
	glPopMatrix();

	// 좌상단, 후면, 은면 제거
	glClear(GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, display_h / 2, display_w / 2, display_h / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < indices_8_3.size(); i++)
	{
		const Vertex& v = vertices_8_3[indices_8_3[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();
	glPopMatrix();

	// 은면 제거
	glClear(GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(display_w / 2, display_h / 2, display_w / 2, display_h / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < indices_8_3.size(); i++)
	{
		const Vertex& v = vertices_8_3[indices_8_3[i]];
		glTexCoord2f(v.texcoord.x, v.texcoord.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_8_3_End()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_8_6_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

	MAIN_WINDOW->ExplanationContext = L"배경과 물체를 그려내기 위해 깊이 버퍼와 색깔 버퍼를 분리해서 처리하는 방법을 보여줍니다.\n";
}

void UTOutputWindow::Code_8_6()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 깊이 테스트는 켜지만 버퍼에는 기록하지 않음
 	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glColor3f(0.62f, 0.45f, 0.35f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.9f, -0.9f, 0.1f);
	glVertex3f(0.9f, -0.9f, 0.1f);
	glVertex3f(0.9f, 0.9f, 0.1f);
	glVertex3f(-0.9f, 0.9f, 0.1f);
	glEnd();
	glColor3f(0.92f, 0.63f, 0.45f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.f, 0.5f, 0.5f);
	glEnd();

	// 깊이 버퍼에 기록은 하지만 색깔 버퍼에는 기록하지 않음
	glDepthMask(GL_TRUE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.9f, -0.9f, 0.1f);
	glVertex3f(0.9f, -0.9f, 0.1f);
	glVertex3f(0.9f, 0.9f, 0.1f);
	glVertex3f(-0.9f, 0.9f, 0.1f);
	glEnd();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_8_6_End()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"";
}