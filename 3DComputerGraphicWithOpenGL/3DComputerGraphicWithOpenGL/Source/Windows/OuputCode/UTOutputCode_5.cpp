// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_5_2()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(-0.5f, -0.5f, 0.f);
// 	glVertex3f(0.5f, -0.5, 0.f);
// 	glVertex3f(0.5f, 0.5f, 0.f);
// 	glVertex3f(-0.5f, 0.5f, 0.f);
// 	glEnd();
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_4()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(1.f, 1.f, 1.f);
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(-0.5f, -0.5f, 0.f);
// 	glVertex3f(0.5f, -0.5, 0.f);
// 	glVertex3f(0.5f, 0.5f, 0.f);
// 	glVertex3f(-0.5f, 0.5f, 0.f);
// 	glEnd();
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_5_Start()
{
// 	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &Width_5_6, &Height_5_6);
// 	glfwSetFramebufferSizeCallback(GetGLFWWindow(), Code_5_5_Reshape);
}

void UTOutputWindow::Code_5_5()
{
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(0.5f, 0.5f, 0.5f);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(-0.5f, -0.5f, 0.f);
// 	glVertex3f(0.5f, -0.5f, 0.f);
// 	glVertex3f(0.5f, 0.5f, 0.f);
// 	glVertex3f(-0.5f, 0.5f, 0.f);
// 	glEnd();
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_5_End()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	glfwSetFramebufferSizeCallback(GetGLFWWindow(), NULL);
}

void UTOutputWindow::Code_5_5_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight)
{
// 	glViewport(0, 0, NewWidth, NewHeight);
// 	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)(OUTPUT_WINDOW->Width_5_6);
// 	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)(OUTPUT_WINDOW->Height_5_6);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f * WidthFactor, 1.f * WidthFactor, -1.f * HeightFactor, 1.f * HeightFactor, -1.f, 1.f);
}

void UTOutputWindow::Code_5_6_Start()
{
/*	glfwSetKeyCallback(GetGLFWWindow(), Code_5_6_Key);*/
}

void UTOutputWindow::Code_5_6()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(0.5f, 0.5f, 0.5f);
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(-0.5f, -0.5f, 0.f);
// 	glVertex3f(0.5f, -0.5, 0.f);
// 	glVertex3f(0.5f, 0.5f, 0.f);
// 	glVertex3f(-0.5f, 0.5f, 0.f);
// 	glEnd();
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_6_End()
{
	/*glfwSetKeyCallback(GetGLFWWindow(), NULL);*/
}

void UTOutputWindow::Code_5_6_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
// 	switch (Key)
// 	{
// 	case GLFW_KEY_Q:
// 	{
// 		if (Action == GLFW_PRESS)
// 		{
// 			exit(0);
// 			break;
// 		}
// 		break;
// 	}
// 	}
}

void UTOutputWindow::Code_5_7_Start()
{
// 	glfwSetMouseButtonCallback(GetGLFWWindow(), Code_5_7_MouseButton);
// 	glfwSetCursorPosCallback(GetGLFWWindow(), Code_5_7_CursorPosition);
}

void UTOutputWindow::Code_5_7()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(0.5f, 0.5f, 0.5f);
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(TopLeftX_5_7, TopLeftY_5_7, 0.f);
// 	glVertex3f(BottomRightX_5_7, TopLeftY_5_7, 0.f);
// 	glVertex3f(BottomRightX_5_7, BottomRightY_5_7, 0.f);
// 	glVertex3f(TopLeftX_5_7, BottomRightY_5_7, 0.f);
// 	glEnd();
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_7_End()
{
// 	glfwSetMouseButtonCallback(GetGLFWWindow(), NULL);
// 	glfwSetCursorPosCallback(GetGLFWWindow(), NULL);
// 	TopLeftX_5_7 = -1;
// 	TopLeftY_5_7 = -1;
// 	BottomRightX_5_7 = 0;
// 	BottomRightY_5_7 = 0;
}

void UTOutputWindow::Code_5_7_MouseButton(GLFWwindow* Window, int button, int action, int mods)
{
// 	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
// 	{
// 		double xpos, ypos;
// 		glfwGetCursorPos(Window, &xpos, &ypos);
// 
// 		std::array<double, 2> OrthoCoords = CursorPosToOrthoCoords(Window, std::array<double, 2>{xpos, ypos});
// 
// 		OUTPUT_WINDOW->TopLeftX_5_7 = OrthoCoords[0];
// 		OUTPUT_WINDOW->TopLeftY_5_7 = OrthoCoords[1];
// 	}
}

void UTOutputWindow::Code_5_7_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
// 	std::array<double, 2> OrthoCoords = CursorPosToOrthoCoords(Window, std::array<double, 2>{xpos, ypos});
// 
// 	OUTPUT_WINDOW->BottomRightX_5_7 = OrthoCoords[0];
// 	OUTPUT_WINDOW->BottomRightY_5_7 = OrthoCoords[1];
}

void UTOutputWindow::Code_5_13()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
// 	
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	glRotatef(30.0, 1.f, 1.f, 1.1);
// 	glFrontFace(GL_CCW);
// 	glEnable(GL_CULL_FACE);
// 
// 	glEnableClientState(GL_COLOR_ARRAY);
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glColorPointer(3, GL_FLOAT, 0, Colors_5_13);
// 	glVertexPointer(3, GL_FLOAT, 0, Vertices_5_13);
// 
// 	for (GLint i = 0; i < 6; i++)
// 		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &VertexList_5_13[4 * i]);
// 
// 	glDisableClientState(GL_COLOR_ARRAY);
// 	glDisableClientState(GL_VERTEX_ARRAY);
// 
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
// 	glRotatef(-30.f, 1.f, 1.f, 1.f);
}

void UTOutputWindow::Code_5_14_Start()
{
// 	//glfwMakeContextCurrent(GetGLFWWindow());
// 	glClearColor(0.f, 0.f, 0.f, 1.f);
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 	MyListID_5_14 = glGenLists(1);
// 	glNewList(MyListID_5_14, GL_COMPILE);
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	
// 	glBegin(GL_POLYGON);
// 	glColor3f(0.5f, 0.5f, 0.5f);
// 	glVertex3f(-0.5f, -0.5f, 0.0f);
// 	glVertex3f(0.5f, -0.5f, 0.0f);
// 	glVertex3f(0.5f, 0.5f, 0.0f);
// 	glVertex3f(-0.5f, 0.5f, 0.0f); 
// 	glEnd();
// 
// 	glEndList();
}

void UTOutputWindow::Code_5_14()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 	glViewport(0, 0, display_w, display_h);
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
// 	
// 	glCallList(MyListID_5_14);
// 
// 	glFlush();
// 	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_14_End()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	glDeleteLists(MyListID_5_14, 1);
}

void UTOutputWindow::Code_5_15_Start()
{
	//glfwMakeContextCurrent(GetGLFWWindow());
// 	glfwSetMouseButtonCallback(GetGLFWWindow(), Code_5_15_MouseButton);
// 	glfwSetCursorPosCallback(GetGLFWWindow(), Code_5_15_CursorPosition);
// 	glfwSetKeyCallback(GetGLFWWindow(), Code_5_15_Key);
// 	const std::string basepath = "Resource/Object/Wood_Table/";
// 	const std::string texbasepath = "Resource/Object/Wood_Table/textures";
// 	const std::string objpath = basepath + "Wood_Table.obj";
// 	LoadObjWithMaterial(objpath, vertices_5_15, indices_5_15, materials_5_15);
// 
// 	glClearColor(0.4f, 0.4f, 0.4f, 1.f);
// 	GLfloat mat_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.f };
// 	GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
// 	GLfloat mat_ambient[] = { 0.5f, 0.4f, 0.3f, 1.f };
// 	GLfloat mat_shininess[] = { 15.f };
// 	GLfloat light_specular[] = { 1.f, 1.f, 1.f, 1.f };
// 	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
// 	GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.f };
// 	light_position_5_15[0] = 5.f;
// 	light_position_5_15[1] = 5.f;
// 	light_position_5_15[2] = 0.f;
// 	light_position_5_15[3] = 1.f;
// 	glShadeModel(GL_SMOOTH);
// 	glEnable(GL_DEPTH_TEST);
// 	glEnable(GL_LIGHTING);
// 	glEnable(GL_LIGHT0);
// 	glEnable(GL_NORMALIZE);
// 	glDisable(GL_COLOR_MATERIAL);
// 	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
// 	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
// 	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
// 
// 	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
// 	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
// 	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
// 	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
// 	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
// 	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
// 	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
// 	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
}

void UTOutputWindow::Code_5_15()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 	int display_w, display_h;
// 	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
// 
// 	glViewport(0, 0, display_w, display_h);
// 
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
//  	glm::vec3 eye{};
//  	float theta_w = (cursor_xpos_5_15 / display_w) * 2.f * glm::pi<float>();
//  	float theta_h = (cursor_ypos_5_15 / display_h) * glm::pi<float>();
//  	eye.x = std::sin(theta_w) * 5.f;
//  	eye.y = std::cos(theta_h) * 5.f;
//  	eye.z = std::cos(theta_w) * 5.f;
// 
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glm::mat4 projection = glm::perspective(
// 		glm::radians(45.0f),
// 		(float)display_w / (float)display_h,
// 		0.1f,
// 		10000.0f
// 	);
// 	glLoadMatrixf(&projection[0][0]);
// 
// 	// 뷰 행렬 설정
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	glm::mat4 view = glm::lookAt(
// 		eye,
// 		glm::vec3(0.f, 0.f, 0.f),
// 		glm::vec3(0.0f, 1.0f, 0.0f)
// 	);
// 	glLoadMatrixf(&view[0][0]);
// 
// 	// 조명 위치는 여기서 다시 설정
// 	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
// 	glEnable(GL_TEXTURE_2D);
// 	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
// 	glGetError();
// 	if (!materials_5_15.empty() && materials_5_15[0].textureId != 0)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, materials_5_15[0].textureId);
// 	}
// 
// 	if (FlatShadeMode_5_15)
// 	{
// 		glShadeModel(GL_SMOOTH);
// 	}
// 	else
// 	{
// 		glShadeModel(GL_FLAT);
// 	}
// 
// 	if (WireframeMode_5_15)
// 	{
// 		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// 	}
// 	else
// 	{
// 		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
// 	}
// 
//  	glBegin(GL_TRIANGLES);
//  	for (size_t i = 0; i < indices_5_15.size(); i++)
//  	{
//  		const Vertex& v = vertices_5_15[indices_5_15[i]];
//  		glTexCoord2f(v.texcoord.x, v.texcoord.y);
//  		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
//  		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
//  	}
//  	glEnd();
// 
// 	glfwSwapBuffers(GetGLFWWindow());
// 	glFlush();
}

void UTOutputWindow::Code_5_15_End()
{
// 	glfwMakeContextCurrent(GetGLFWWindow());
// 
// 	glfwSetMouseButtonCallback(GetGLFWWindow(), nullptr);
// 	glfwSetCursorPosCallback(GetGLFWWindow(), nullptr);
// 	glfwSetKeyCallback(GetGLFWWindow(), nullptr);
// 	
// 	OUTPUT_WINDOW->WireframeMode_5_15 = true;
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// 
// 	OUTPUT_WINDOW->FlatShadeMode_5_15 = true;
// 	glShadeModel(GL_SMOOTH);
// 
// 	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
// 	glDisable(GL_DEPTH_TEST);
// 	glDisable(GL_LIGHTING);
// 	glDisable(GL_LIGHT0);
// 	glDisable(GL_NORMALIZE);
// 	glDisable(GL_COLOR_MATERIAL);
// 	glDisable(GL_TEXTURE_2D);
// 	for (auto& material : materials_5_15)
// 	{
// 		if (material.textureId != 0)
// 		{
// 			glDeleteTextures(1, &material.textureId);
// 			material.textureId = 0;
// 		}
// 	}
// 	glFlush();
}

void UTOutputWindow::Code_5_15_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight)
{
// 	glViewport(0, 0, NewWidth, NewHeight);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
}

void UTOutputWindow::Code_5_15_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
// 	switch (Key)
// 	{
// 	case GLFW_KEY_Q:
// 	{
// 		if (Action == GLFW_PRESS)
// 		{
// 			exit(0);
// 			break;
// 		}
// 		break;
// 	}
// 	case GLFW_KEY_1:
// 	{
// 		if (Action == GLFW_PRESS)
// 		{
// 			if (OUTPUT_WINDOW->FlatShadeMode_5_15)
// 			{
// 				OUTPUT_WINDOW->FlatShadeMode_5_15 = false;
// 			}
// 			else
// 			{
// 				OUTPUT_WINDOW->FlatShadeMode_5_15 = true;
// 			}
// 		}
// 		break;
// 	}
// 	case GLFW_KEY_2:
// 	{
// 		if (Action == GLFW_PRESS)
// 		{
// 			if(OUTPUT_WINDOW->WireframeMode_5_15)
// 			{
// 				OUTPUT_WINDOW->WireframeMode_5_15 = false;
// 			}
// 			else
// 			{
// 				OUTPUT_WINDOW->WireframeMode_5_15 = true;
// 			}
// 		}
// 	}
// 	}
}

void UTOutputWindow::Code_5_15_MouseButton(GLFWwindow* Window, int button, int action, int mods)
{

}

void UTOutputWindow::Code_5_15_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
// 	CursorPosToOrthoCoords(OUTPUT_WINDOW->GetGLFWWindow(), std::array<double,2>{xpos, ypos});
// 	OUTPUT_WINDOW->cursor_xpos_5_15 = xpos;
// 	OUTPUT_WINDOW->cursor_ypos_5_15 = ypos;
}