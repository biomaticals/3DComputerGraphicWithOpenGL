// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_14_1_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), UTOutputWindow::Code_14_1_Key);

	QuardricObj_14_1 = gluNewQuadric();

	GLfloat mat_diffuse[] = { 1.f, 1.f, 0.9f, 1.f };
	GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat light_position[] = { 2.5f, 2.5f, -15.f, 1.f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	MAIN_WINDOW->ExplanationContext = L"GLU 쿼드릭 객체를 사용해 구, 원판, 부분원판, 원기둥등의 2차 곡면을 그리는 예제입니다.\n";
	MAIN_WINDOW->DebugContext = L"1: 구, 2: 원판, 3: 부분원판, 4: 원기둥\n5: 그리기 스타일 변경(점->선->채우기)";
}

void UTOutputWindow::Code_14_1()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.f, (GLfloat)display_w / (GLfloat)display_h, 1.f, 10.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, -1.f);

	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(QuardricObj_14_1, GLU_SMOOTH);

	if (bDrawStyle_14_1 == 1 << 0)
		gluQuadricDrawStyle(QuardricObj_14_1, GLU_POINT);
	else if (bDrawStyle_14_1 == 1 << 1)
		gluQuadricDrawStyle(QuardricObj_14_1, GLU_LINE);
	else if (bDrawStyle_14_1 == 1 << 2)
		gluQuadricDrawStyle(QuardricObj_14_1, GLU_FILL);

	if (bDrawingShape_14_1 == 1 << 0)
	{
		gluSphere(QuardricObj_14_1, 1.f, 20, 20);
		gluQuadricOrientation(QuardricObj_14_1, GLU_OUTSIDE);
	}
	else if (bDrawingShape_14_1 == 1 << 1)
	{
		gluDisk(QuardricObj_14_1, 0.5f, 1.f, 20, 4);
		gluQuadricOrientation(QuardricObj_14_1, GLU_INSIDE);
	}

	else if (bDrawingShape_14_1 == 1 << 2)
	{
		gluPartialDisk(QuardricObj_14_1, 0.5f, 1.f, 20, 4, 0.f, 270.f);
		gluQuadricOrientation(QuardricObj_14_1, GLU_INSIDE);
	}
	else if (bDrawingShape_14_1 == 1 << 3)
	{
		gluCylinder(QuardricObj_14_1, 0.5f, 0.2f, 2.f, 20, 4);
		gluQuadricOrientation(QuardricObj_14_1, GLU_OUTSIDE);
	}
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_14_1_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);

	gluDeleteQuadric(QuardricObj_14_1);

	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_14_1_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action != GLFW_PRESS)
		return;

	switch (Key)
	{
	case GLFW_KEY_1:
	{
		OUTPUT_WINDOW->bDrawingShape_14_1 = 1 << 0;
		break;
	}
	case GLFW_KEY_2:
	{
		OUTPUT_WINDOW->bDrawingShape_14_1 = 1 << 1;
		break;

	}
	case GLFW_KEY_3:
	{
		OUTPUT_WINDOW->bDrawingShape_14_1 = 1 << 2;
		break;
	}
	case GLFW_KEY_4:
	{
		OUTPUT_WINDOW->bDrawingShape_14_1 = 1 << 3;
		break;
	}
	case GLFW_KEY_5:
	{
		OUTPUT_WINDOW->bDrawStyle_14_1 = OUTPUT_WINDOW->bDrawStyle_14_1 << 1;
		if (OUTPUT_WINDOW->bDrawStyle_14_1 > (1 << 2))
			OUTPUT_WINDOW->bDrawStyle_14_1 = 1 << 0;
		break;
	}
	default:
		break;
	}
}

void UTOutputWindow::Code_14_2_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	GLfloat light0_position[] = { 3.f, 1.f, 1.f, 1.f };
	GLfloat light1_position[] = { -3.f, 1.f, 1.f, 1.f };
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.f);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_AUTO_NORMAL);
		
	Time_14_2 = glfwGetTime();

	MAIN_WINDOW->ExplanationContext = L"GLU NURBS 렌더러를 사용해 3차원 NURBS 곡면을 그리는 예제입니다.\n제어점의 일부를 시간에 따라 이동시켜 곡면이 변형되는 모습을 보여줍니다.";
}

void UTOutputWindow::Code_14_2()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Nurbs_14_2 = gluNewNurbsRenderer();
	int s, t;
	for (s = 0; s < 4; s++) {           //x, y, z 방향으로 -3에서 +3까지
		for (t = 0; t < 4; t++) {
			ctlpointsCoordi_14_2[s][t][0] = 2.f * ((GLfloat)s - 1.5f);
			ctlpointsCoordi_14_2[s][t][2] = 2.f * ((GLfloat)t - 1.5f);
			if ((s == 1 || s == 2) && (t == 1 || t == 2))
				ctlpointsCoordi_14_2[s][t][1] = 3.f;
			else
				ctlpointsCoordi_14_2[s][t][1] = -3.f;
			for (int k = 0; k < 3; k++)
				ctlpoints_14_2[s][t][k] = weight_14_2[s][t] * ctlpointsCoordi_14_2[s][t][k];    //제어점 정보 초기화
			ctlpoints_14_2[s][t][3] = weight_14_2[s][t];
		}
	}
	
	ElapsedTime_14_2 = (GLfloat)(glfwGetTime() - Time_14_2);
	ElapsedTime_14_2 = fmod(ElapsedTime_14_2, 11.f);
	ctlpoints_14_2[1][1][1] = 1.f + std::clamp(ElapsedTime_14_2, 0.f, 11.f);
	ctlpoints_14_2[1][2][1] = 1.f + std::clamp(ElapsedTime_14_2, 0.f, 11.f);
	ctlpointsCoordi_14_2[1][1][1] = 1.f + std::clamp(ElapsedTime_14_2, 0.f, 11.f);
	ctlpointsCoordi_14_2[1][2][1] = 1.f + std::clamp(ElapsedTime_14_2, 0.f, 11.f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.f, 5.f, -10.f, 10.f, -20.f, 20.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.f, 0.f, -15.f);
	glPushMatrix();
	glRotatef(45.f, 1.f, 0.f, 0.f);
	for (int i = 0; i < 4; i++) 
	{               
		for (int j = 0; j < 4; j++) 
		{
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, point_mat_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, point_mat_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, point_mat_emission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, point_mat_shininess);
			glPointSize(5.f);
			glBegin(GL_POINTS);
			glVertex3f(ctlpointsCoordi_14_2[i][j][0],
				ctlpointsCoordi_14_2[i][j][1],
				ctlpointsCoordi_14_2[i][j][2]);
			glEnd();
			glPopMatrix();
		}
	}
	glPushMatrix();
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			glBegin(GL_LINES);
			glVertex3f(ctlpointsCoordi_14_2[i][j][0],
				ctlpointsCoordi_14_2[i][j][1],
				ctlpointsCoordi_14_2[i][j][2]);
			glVertex3f(ctlpointsCoordi_14_2[i][j + 1][0],
				ctlpointsCoordi_14_2[i][j + 1][1],
				ctlpointsCoordi_14_2[i][j + 1][2]);
			glEnd();
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			glBegin(GL_LINES);
			glVertex3f(ctlpointsCoordi_14_2[i][j][0],
				ctlpointsCoordi_14_2[i][j][1],
				ctlpointsCoordi_14_2[i][j][2]);
			glVertex3f(ctlpointsCoordi_14_2[i + 1][j][0],
				ctlpointsCoordi_14_2[i + 1][j][1],
				ctlpointsCoordi_14_2[i + 1][j][2]);
			glEnd();
		}
	}

	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, surface_mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, surface_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, surface_mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, surface_mat_shininess);
	gluBeginSurface(Nurbs_14_2);
	gluNurbsSurface(Nurbs_14_2, 8, knots, 8, knots, 4 * 4, 4,
		&ctlpoints_14_2[0][0][0], 4, 4, GL_MAP2_VERTEX_4);
	gluEndSurface(Nurbs_14_2);
	glPopMatrix();
	glPopMatrix();
	gluDeleteNurbsRenderer(Nurbs_14_2);
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_14_2_End()
{
	ResetAll();

	MAIN_WINDOW->ExplanationContext = L"";
}
