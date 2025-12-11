// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "glaux/glaux.h"

void UTOutputWindow::Code_11_7_Start()
{
	ResetAll();

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

	MAIN_WINDOW->ExplanationContext = L"텍스처 좌표를 수동으로 매핑한 뒤 래핑 방법을 정의하는 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext = L"여기에서는(0~1) 범위를 벗어난 텍스처에 대해 S 방향은 CLAMP, T 방향은 REPEAT 방법으로 래핑합니다.";
}

void UTOutputWindow::Code_11_7()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width_11_7, Height_11_7, 0, GL_RGB, GL_UNSIGNED_BYTE, &Texture_11_7);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, -1.f, 0.f);
	glTexCoord2f(0.f, 3.f); glVertex3f(-1.f, 1.f, 0.f);
	glTexCoord2f(3.f, 3.f); glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2f(3.f, 0.f); glVertex3f(1.f, -1.f, 0.f);
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_11_7_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glDisable(GL_TEXTURE_2D);

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_11_9_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	GLfloat mat_diffuse[] = { 0.25, 0.25, 1., 0. };
	GLfloat mat_specular[] = { 1., 1., 1., 0. };
	GLfloat light_position[] = { 10., 10., 20., 1. };
	GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0. };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.f);
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

	MAIN_WINDOW->ExplanationContext = L"1D 스트라이프 텍스처를 생성하고, Object Linear 방식의 텍스처 좌표 자동 생성을 사용해 구 표면에 반복되는 줄무늬 패턴을 입히는 예제입니다.\n";
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
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	
	glBindTexture(GL_TEXTURE_1D, 0);
	gluDeleteQuadric(QuardricObj_11_7);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_1D);

	glNormal3f(0.f, 0.f, 1.f);

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_11_11_Start()
{
	std::wstring MusicPath = RESOURCE_MANAGER->GetSoundPath() + L"/weightless-flight-short-instrumental.mp3";
	bool Result = 0;
	if (std::filesystem::exists(MusicPath))
	{
		MCIERROR err = mciSendStringW((L"open \"" + MusicPath + L"\" type mpegvideo alias bgm").c_str(), NULL, 0, NULL);
		if (err != 0)
		{
			wchar_t errorText[256];
			mciGetErrorStringW(err, errorText, 256);
			std::wstring errorMessage = L"MCI Error: " + std::wstring(errorText);
			MAIN_WINDOW->DebugContext = errorMessage;
		}
		else
		{
			mciSendStringW(L"play bgm repeat", NULL, 0, NULL);
		}
	}

	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), Code_11_11_Key);

	Time_11_11 = (GLfloat)glfwGetTime();

	MAIN_WINDOW->ExplanationContext = L"스카이 박스와 지형을 렌더링하고, 키보드 입력에 따라 카메라를 이동 및 회전시키는 예제입니다.\n";
	MAIN_WINDOW->DebugContext = L"W : 앞 / A : 왼쪽 / D : 오른쪽 / S : 뒤\nQ : -롤 회전  E : +롤 회전 /J : -요 회전 / L : +요 회전 / I : +피치 회전 / K : -피치 회전\nR : 위 / F : 아래";
}

void UTOutputWindow::Code_11_11()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w{}, display_h{};
	glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	
	if (Terrain_11_11 == nullptr && Skybox_11_11 == nullptr && Camera_11_11 == nullptr)
	{
		Terrain_11_11 = new Terrain("Resource/Object/space/terrain1.raw", "Resource/Object/space/snow512.bmp", 257, 257);
		Skybox_11_11 = new Skybox();
		Camera_11_11 = new Camera();
	
		Camera_11_11->set(0.f, 1.f, 0.f, 0.f, 1.f, -1.f, 0.f, 1.f, 0.f);
		Camera_11_11->setShape(60.f, (float)display_h / (float)display_w, 0.5f, 1000.f);
	
		Camera_11_11->slide(0.f, 30.f, 0.f);
		Camera_11_11->roll(0.f);
		Camera_11_11->yaw(0.f);
		Camera_11_11->pitch(0.f);
	}
	
	ElapsedTime_11_11 = (GLfloat)glfwGetTime() - Time_11_11;
	Time_11_11 = (GLfloat)glfwGetTime();
	
	if (Actions[LEFT])
		Camera_11_11->slide(-10.f * ElapsedTime_11_11, 0.f, 0.f);
	
	if (Actions[RIGHT])
		Camera_11_11->slide(10.f * ElapsedTime_11_11, 0.f, 0.f);
	
	if(Actions[FORWARD])
		Camera_11_11->slide(0.f, 0.f, 10.f * ElapsedTime_11_11);
	
	if (Actions[BACKWARD])
		Camera_11_11->slide(0.f, 0.f, -10.f * ElapsedTime_11_11);
	
	if(Actions[UP])
		Camera_11_11->slide(0.f, 10.f * ElapsedTime_11_11, 0.f);
	
	if (Actions[DOWN])
		Camera_11_11->slide(0.f, -10.f * ElapsedTime_11_11, 0.f);
	
	if(Actions[PITCH_UP])
		Camera_11_11->pitch(25.f * ElapsedTime_11_11);
	
	if (Actions[PITCH_DOWN])
		Camera_11_11->pitch(-25.f * ElapsedTime_11_11);
	
	if (Actions[YAW_LEFT])
		Camera_11_11->yaw(-25.f * ElapsedTime_11_11);
	
	if (Actions[YAW_RIGHT])
		Camera_11_11->yaw(25.f * ElapsedTime_11_11);
	
	if(Actions[ROLL_LEFT])
		Camera_11_11->roll(25.f * ElapsedTime_11_11);
	
	if (Actions[ROLL_RIGHT])
		Camera_11_11->roll(-25.f * ElapsedTime_11_11);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(Camera_11_11->eye.x, Camera_11_11->eye.y, Camera_11_11->eye.z);
	Skybox_11_11->draw();
	glPopMatrix();
	
	glPushMatrix();
	glScalef(1.f, 0.2f, 1.f);
	Terrain_11_11->RenderTerrain(Camera_11_11->eye.x, Camera_11_11->eye.z);//지형을 그린다.좌표를 보내주는 이유는 카메라가 위치한 타일블럭의 좌표를 계산하기 위해 ppt참조
	Terrain_11_11->RenderWater();
	glPopMatrix();
	fog(); // 수면아래 안개효과
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_11_11_End()
{
	mciSendStringW(L"close bgm", NULL, 0, NULL);

	glfwMakeContextCurrent(GetGLFWWindow());
	glDisable(GL_FOG);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	ResetAll();

	dispose();

	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::dispose()
{
	delete Terrain_11_11;
	delete Skybox_11_11;
	delete Camera_11_11;

	Terrain_11_11 = nullptr;
	Skybox_11_11 = nullptr;
	Camera_11_11 = nullptr;
}

void UTOutputWindow::fog()
{
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);

	GLfloat waterFogColor[4] = { 0.f,0.6f,0.6f,5.f };
	GLfloat fogColor[4] = { 0.75f,0.75f,0.75f,0.f };

	if (Camera_11_11->eye.y < (Terrain_11_11->waterLevel * 0.2f))
	{
		glFogfv(GL_FOG_COLOR, waterFogColor);
		glFogf(GL_FOG_DENSITY, 0.75f);
	}
	else
	{
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.01f);
	}
}

void UTOutputWindow::Code_11_11_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{

	case GLFW_KEY_1:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->LINE_MODE_11_11 = !OUTPUT_WINDOW->LINE_MODE_11_11;
		break;
	}

	case GLFW_KEY_2:
	{
		if(Action == GLFW_PRESS)
			OUTPUT_WINDOW->FILL_MODE_11_11 = !OUTPUT_WINDOW->FILL_MODE_11_11;
		break;
	}

	case GLFW_KEY_D:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[RIGHT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[RIGHT] = false;
		break;
	}

	case GLFW_KEY_A:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[LEFT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[LEFT] = false;
		break;
	}

	case GLFW_KEY_S:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[FORWARD] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[FORWARD] = false;
		break;
	}

	case GLFW_KEY_W:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[BACKWARD] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[BACKWARD] = false;
		break;
	}

	case GLFW_KEY_SPACE:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[UP] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[UP] = false;
		break;
	}

	case GLFW_KEY_LEFT_SHIFT:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[DOWN] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[DOWN] = false;
		break;
	}

	case GLFW_KEY_K:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[PITCH_UP] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[PITCH_UP] = false;
		break;
	}

	case GLFW_KEY_I:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[PITCH_DOWN] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[PITCH_DOWN] = false;
		break;
	}

	case GLFW_KEY_J:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[YAW_LEFT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[YAW_LEFT] = false;
		break;
	}

	case GLFW_KEY_L:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[YAW_RIGHT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[YAW_RIGHT] = false;
		break;
	}

	case GLFW_KEY_Q:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[ROLL_LEFT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[ROLL_LEFT] = false;
		break;
	}

	case GLFW_KEY_E:
	{
		if (Action == GLFW_PRESS)
			OUTPUT_WINDOW->Actions[ROLL_RIGHT] = true;
		else if (Action == GLFW_RELEASE)
			OUTPUT_WINDOW->Actions[ROLL_RIGHT] = false;
		break;
	}
	}
}