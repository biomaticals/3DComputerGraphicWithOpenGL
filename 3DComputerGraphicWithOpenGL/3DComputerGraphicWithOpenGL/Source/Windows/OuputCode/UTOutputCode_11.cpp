// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "glaux/glaux.h"

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

void UTOutputWindow::Code_11_11_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), Code_11_11_Key);


	Time_11_11 = glfwGetTime();
}

void UTOutputWindow::Code_11_11()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	if (terrain_11_11 == nullptr && skybox_11_11 == nullptr && camera_11_11 == nullptr)
	{
		terrain_11_11 = new Terrain("Resource/Object/space/terrain1.raw", "Resource/Object/space/snow512.bmp", 257, 257);
		skybox_11_11 = new Skybox();
		camera_11_11 = new Camera();

// 		camera_11_11->set(4.f, 4.f, 4.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
// 		camera_11_11->setShape(60.f, 64.f / 48.f, 0.5f, 1000.f);
// 
// 		camera_11_11->slide(0, 100, 0);
// 		camera_11_11->roll(0);
// 		camera_11_11->yaw(180);
// 		camera_11_11->pitch(45);

		camera_11_11->set(0.f, 1.f, 0.f, 0.f, 1.f, -1.f, 0.f, 1.f, 0.f);
		camera_11_11->setShape(90.f, (float)display_h / (float)display_w, 0.5f, 1000.f);

		camera_11_11->slide(0.f, 100.f, 0.f);
		camera_11_11->roll(0.f);
		camera_11_11->yaw(0.f);
		camera_11_11->pitch(0.f);
	}

	ElapsedTime_11_11 = Time_11_11 - glfwGetTime();
	Time_11_11 = glfwGetTime();
	
	switch (Action_11_11)
	{
	case EKeyInputAction::LEFT:
		camera_11_11->slide(-0.2f, 0.f, 0.f);
		break;
	case EKeyInputAction::RIGHT:
		camera_11_11->slide(0.2f, 0.f, 0.f);
		break;
	case EKeyInputAction::UP:
		camera_11_11->slide(0.f, 0.f, -0.2f);
		break;
	case EKeyInputAction::DOWN:
		camera_11_11->slide(0.f, 0.f, 0.2f);
		break;
	case EKeyInputAction::PITCH_UP:
		camera_11_11->pitch(0.5f);
		break;
	case EKeyInputAction::PITCH_DOWN:
		camera_11_11->pitch(-0.5f);
		break;
	case EKeyInputAction::YAW_LEFT:
		camera_11_11->yaw(-0.5f);
		break;
	case EKeyInputAction::YAW_RIGHT:
		camera_11_11->yaw(0.5f);
		break;
	case EKeyInputAction::ROLL_LEFT:
		camera_11_11->roll(0.5f);
		break;
	case EKeyInputAction::ROLL_RIGHT:
		camera_11_11->roll(-0.5f);
		break;
	default:
		break;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(camera_11_11->eye.x, camera_11_11->eye.y, camera_11_11->eye.z);
	skybox_11_11->draw();
	glPopMatrix();



	//glScalef(1.0f, 0.2f, 1.0f);
	//glPushMatrix();
	//terrain_11_11->RenderTerrain(camera_11_11->eye.x, camera_11_11->eye.z);//지형을 그린다.좌표를 보내주는 이유는 카메라가 위치한 타일블럭의 좌표를 계산하기 위해 ppt참조
	//glPopMatrix();
	//fog(); // 수면아래 안개효과
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_11_11_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	ResetAll();

	dispose();
}

void UTOutputWindow::dispose()
{
	delete terrain_11_11;
	delete skybox_11_11;
	delete camera_11_11;
}

void UTOutputWindow::fog()
{
	//GL_FOG를 활성화 한다.
	glEnable(GL_FOG);
	//안개의 농도차이를 결정하는 인자 (GL_LINEAR, GL_EXP, GL_EXP2)
	glFogi(GL_FOG_MODE, GL_EXP2);
	//Viewer의 Y가 waterLevel보다 작으면, 즉 물속에 있다면
	GLfloat waterFogColor[4] = { 0.0,0.6,0.6,5.0 };
	GLfloat fogColor[4] = { 0.75,0.75,0.75,0.0 };
	if (camera_11_11->eye.y < (terrain_11_11->waterLevel - 75)) {
		//안개 색상을 waterFogColor(0.0,0.6,0.6,1.0)으로 변경하고
		glFogfv(GL_FOG_COLOR, waterFogColor);
		//안개 거리를 waterFogDensity(0.075)로 변경해서 물속이라는 느낌을 주게 한다.
		glFogf(GL_FOG_DENSITY, 0.075);
	}
	else {//아니면 
		//안개 색상을 fogColor(0.7,0.7.0.7,1) 변경하고
		glFogfv(GL_FOG_COLOR, fogColor);
		//안개 거리를 fogDensity(0.002) 변경해서 물밖이라는 느낌을 주게 한다.
		glFogf(GL_FOG_DENSITY, 0.001);
	}
}

void UTOutputWindow::Code_11_11_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if(Action == GLFW_PRESS)
	{
		switch (Key)
		{
		case GLFW_KEY_1:
			glPolygonMode(GL_FRONT, GL_LINE);
			break;
		case GLFW_KEY_2:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		case GLFW_KEY_D:
			OUTPUT_WINDOW->camera_11_11->slide(0.2f, 0.f, 0.f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::RIGHT;
			break;
		case GLFW_KEY_A:
			OUTPUT_WINDOW->camera_11_11->slide(-0.2f, 0.f, 0.f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::LEFT;
			break;
		case GLFW_KEY_S:
			OUTPUT_WINDOW->camera_11_11->slide(0.f, 0.f, 1.f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::UP;
			break;
		case GLFW_KEY_W:
			OUTPUT_WINDOW->camera_11_11->slide(0.f, 0.f, -1.f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::DOWN;
			break;
		case GLFW_KEY_K:
			OUTPUT_WINDOW->camera_11_11->pitch(-0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::PITCH_DOWN;
			break;
		case GLFW_KEY_I:
			OUTPUT_WINDOW->camera_11_11->pitch(0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::PITCH_UP;
			break;
		case GLFW_KEY_Q:
			OUTPUT_WINDOW->camera_11_11->yaw(-0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::YAW_LEFT;
			break;
		case GLFW_KEY_E:
			OUTPUT_WINDOW->camera_11_11->yaw(0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::YAW_RIGHT;
			break;
		case GLFW_KEY_J:
			OUTPUT_WINDOW->camera_11_11->roll(0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::ROLL_LEFT;
			break;
		case GLFW_KEY_L:
			OUTPUT_WINDOW->camera_11_11->roll(-0.5f);
			OUTPUT_WINDOW->Action_11_11 = EKeyInputAction::ROLL_RIGHT;
			break;
		}
	}
}