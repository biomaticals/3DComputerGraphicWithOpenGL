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
	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &Width_5_6, &Height_5_6);
	glfwSetFramebufferSizeCallback(GetGLFWWindow(), Code_5_5_Reshape);
}

void UTOutputWindow::Code_5_5()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
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
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)(OUTPUT_WINDOW->Width_5_6);
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)(OUTPUT_WINDOW->Height_5_6);
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
	glVertex3f(TopLeftX_5_7, TopLeftY_5_7, 0.f);
	glVertex3f(BottomRightX_5_7, TopLeftY_5_7, 0.f);
	glVertex3f(BottomRightX_5_7, BottomRightY_5_7, 0.f);
	glVertex3f(TopLeftX_5_7, BottomRightY_5_7, 0.f);
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

		std::array<double, 2> OrthoCoords = CursorPosToOrthoCoords(Window, std::array<double, 2>{xpos, ypos});

		OUTPUT_WINDOW->TopLeftX_5_7 = OrthoCoords[0];
		OUTPUT_WINDOW->TopLeftY_5_7 = OrthoCoords[1];
	}
}

void UTOutputWindow::Code_5_7_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
	std::array<double, 2> OrthoCoords = CursorPosToOrthoCoords(Window, std::array<double, 2>{xpos, ypos});

	OUTPUT_WINDOW->BottomRightX_5_7 = OrthoCoords[0];
	OUTPUT_WINDOW->BottomRightY_5_7 = OrthoCoords[1];
}

void UTOutputWindow::Code_5_13()
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
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, Colors_5_13);
	glVertexPointer(3, GL_FLOAT, 0, Vertices_5_13);

	glRotatef(30.0, 1.0, 1.0, 1.0);
	for (GLint i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &VertexList_5_13[4 * i]);
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_14_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	MyListID_5_14 = glGenLists(1);
	glNewList(MyListID_5_14, GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f); 
	glEnd();

	glPopMatrix();
	glEndList();
}

void UTOutputWindow::Code_5_14()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_15_Start()
{
	const std::string path = "Resource/Object/TableAndChairs.obj";
	LoadObjSimple(path, vertices_5_15, indices_5_15);

	glm::vec3 MeanPos;
	glm::vec3 MinPos(FLT_MAX);
	glm::vec3 MaxPos(-FLT_MAX);
	for(int i = 0 ; i < vertices_5_15.size() ; i ++)
	{
		MeanPos += vertices_5_15[i].pos;
		if(vertices_5_15[i].pos.x > MaxPos.x)
			MaxPos.x = vertices_5_15[i].pos.x;
		if (vertices_5_15[i].pos.y > MaxPos.y)
			MaxPos.y = vertices_5_15[i].pos.y;
		if (vertices_5_15[i].pos.z > MaxPos.z)
			MaxPos.z = vertices_5_15[i].pos.z;
		if (vertices_5_15[i].pos.x < MinPos.x)
			MinPos.x = vertices_5_15[i].pos.x;
		if (vertices_5_15[i].pos.y < MinPos.y)
			MinPos.y = vertices_5_15[i].pos.y;
		if (vertices_5_15[i].pos.z < MinPos.z)
			MinPos.z = vertices_5_15[i].pos.z;
	}
	MeanPos /= (float)vertices_5_15.size();
	printf("Mean : (%f, %f, %f), Min : (%f, %f, %f), Max : (%f, %f, %f)", MeanPos.x, MeanPos.y, MeanPos.z, MinPos.x, MinPos.y, MinPos.z, MaxPos.x, MaxPos.y, MaxPos.z);

	glClearColor(0.4f, 0.4f, 0.4f, 0.f);
	GLfloat mat_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat mat_ambient[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat mat_shininess[] = { 15.f };
	GLfloat light_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
	GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.f };
	light_position_5_15[0] = -3.f;
	light_position_5_15[1] = 6.f;
	light_position_5_15[2] = 3.f;
	light_position_5_15[3] = 0.f;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void UTOutputWindow::Code_5_15()
{
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);

	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),                       // 시야각 (fovy)
		(float)display_w / (float)display_h,       // 종횡비
		0.1f,                                      // near plane
		10000.0f                                     // far plane
	);
	glLoadMatrixf(&projection[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 center = glm::vec3(-15.7f, 25.4f, -13.0f);
	glm::vec3 eye = center + glm::normalize(glm::vec3(1.f, 1.f, 1.f));
	glm::mat4 view = glm::lookAt(
		glm::vec3(200.f, 50.f, 200.f),  // eye (카메라 위치)
		glm::vec3(0.f, 0.f, 0.f),   // center (바라보는 지점)
		glm::vec3(0.0f, 1.0f, 0.0f)    // up (업 벡터)
	);
	glLoadMatrixf(&view[0][0]);

	// 조명 위치는 여기서 다시 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);

	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < indices_5_15.size(); i++)
	{
		const Vertex& v = vertices_5_15[indices_5_15[i]];
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
	}
	glEnd();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_15_End()
{

}

void UTOutputWindow::Code_5_15_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
}

void UTOutputWindow::Code_5_15_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
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
	case GLFW_KEY_S:
	{
		if (OUTPUT_WINDOW->FlatShaded)
		{
			OUTPUT_WINDOW->FlatShaded = false;
			glShadeModel(GL_SMOOTH);
		}
		else
		{
			OUTPUT_WINDOW->FlatShaded = true;
			glShadeModel(GL_FLAT);
		}
	}
	}
}

void UTOutputWindow::Code_5_15_MouseButton(GLFWwindow* Window, int button, int action, int mods)
{

}

void UTOutputWindow::Code_5_15_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
	
}