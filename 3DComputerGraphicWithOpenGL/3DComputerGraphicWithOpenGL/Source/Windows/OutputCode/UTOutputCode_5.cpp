// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "InsideStaticMath.h"

void UTOutputWindow::Code_5_2_Start()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"색 버퍼를 초기화한 뒤, 직접 정의한 정점들을 이용해 화면 중앙에 2D 폴리곤을 렌더링 하는 기초 예제입니다.";
}

void UTOutputWindow::Code_5_2()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_5_2_End()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_4_Start()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"색 버퍼를 초기화 한 뒤, 투영 행렬을 직교 투영 행렬로 설정합니다. 그리고 직접 정의한 정점들을 이용해 화면 중앙에 2D 폴리곤을 렌더링합니다.";
}

void UTOutputWindow::Code_5_4()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
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
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_5_4_End()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_5_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &Width_5_6, &Height_5_6);
	glfwSetFramebufferSizeCallback(GetGLFWWindow(), Code_5_5_Reshape);

	MAIN_WINDOW->ExplanationContext = L"색 버퍼를 초기화 한 뒤, 창의 크기가 변경될 때마다 호출되는 콜백 함수를 등록합니다. 그리고 직접 정의한 정점들을 이용해 화면 중앙에 2D 폴리곤을 렌더링합니다.";
}

void UTOutputWindow::Code_5_5()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f , 1.f, -1.f, 1.f, -1.f, 1.f);

	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_5_5_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetFramebufferSizeCallback(GetGLFWWindow(), NULL);

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_5_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	glViewport(0, 0, NewWidth, NewHeight);
	
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)(OUTPUT_WINDOW->Width_5_6);
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)(OUTPUT_WINDOW->Height_5_6);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f * WidthFactor, 1.f * WidthFactor, -1.f * HeightFactor, 1.f * HeightFactor, -1.f, 1.f);
}

void UTOutputWindow::Code_5_6_Start()
{
	ResetAll();
	glfwSetKeyCallback(GetGLFWWindow(), Code_5_6_Key);

	MAIN_WINDOW->ExplanationContext = L"색 버퍼를 초기화 한 뒤, 키보드 입력을 처리하는 콜백 함수를 등록합니다. 그리고 직접 정의한 정점들을 이용해 화면 중앙에 2D 폴리곤을 렌더링합니다. 'Q' 키를 누르면 프로그램이 종료됩니다.";
}

void UTOutputWindow::Code_5_6()
{
	glfwMakeContextCurrent(GetGLFWWindow());
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
	
	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_5_6_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), NULL);

	MAIN_WINDOW->ExplanationContext = L"";
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
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetMouseButtonCallback(GetGLFWWindow(), Code_5_7_MouseButton);
	glfwSetCursorPosCallback(GetGLFWWindow(), Code_5_7_CursorPosition);

	TopLeftX_5_7 = -0.85;
	TopLeftY_5_7 = 0.85;
	BottomRightX_5_7 = 0.85;
	BottomRightY_5_7 = -0.85;

	MAIN_WINDOW->ExplanationContext = L"색 버퍼를 초기화 한 뒤, 마우스 입력을 처리하는 콜백 함수를 등록합니다. 마우스 왼쪽 버튼을 클릭한 위치를 사각형의 왼쪽 위 꼭지점으로, 마우스를 이동한 위치를 사각형의 오른쪽 아래 꼭지점으로 설정하여 사각형을 렌더링합니다.";
}

void UTOutputWindow::Code_5_7()
{
	glfwMakeContextCurrent(GetGLFWWindow());
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
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetMouseButtonCallback(GetGLFWWindow(), NULL);
	glfwSetCursorPosCallback(GetGLFWWindow(), NULL);

	TopLeftX_5_7 = -0.85;
	TopLeftY_5_7 = -0.85;
	BottomRightX_5_7 = 0.85;
	BottomRightY_5_7 = 0.85;

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_7_MouseButton(GLFWwindow* Window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
		double xpos, ypos;
		glfwGetCursorPos(Window, &xpos, &ypos);

		GLfloat _Matrix[16];
		glGetFloatv(GL_PROJECTION_MATRIX, _Matrix);
		const InsideStaticMath::OrthoBounds OutOrthoBound = InsideStaticMath::GetOrthoBoundsFromProjectionMatrix(_Matrix);

		int display_w, display_h;
		glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &display_w, &display_h);
		std::array<double, 2> CursorCoords = InsideStaticMath::CursorPosFromOrthoCoords(display_w, display_h, OutOrthoBound, std::array<double, 2>{xpos, ypos});
		
		OUTPUT_WINDOW->TopLeftX_5_7 = CursorCoords[0];
		OUTPUT_WINDOW->TopLeftY_5_7 = CursorCoords[1];
	}
}

void UTOutputWindow::Code_5_7_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	GLfloat _Matrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, _Matrix);
	const InsideStaticMath::OrthoBounds OutOrthoBound = InsideStaticMath::GetOrthoBoundsFromProjectionMatrix(_Matrix);

	int display_w, display_h;
	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &display_w, &display_h);
	std::array<double, 2> CursorCoords = InsideStaticMath::CursorPosFromOrthoCoords(display_w, display_h, OutOrthoBound, std::array<double, 2>{xpos, ypos});

	OUTPUT_WINDOW->BottomRightX_5_7 = CursorCoords[0];
	OUTPUT_WINDOW->BottomRightY_5_7 = CursorCoords[1];
}

void UTOutputWindow::Code_5_13_Start()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"정점 배열과 색상 배열, 인덱스 배열을 사용하여 3D 큐브를 렌더링하는 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext += L"폴리곤의 와인딩 순서를 반시계(CCW)로 설정하여 앞면을 정의하고,\n";
	MAIN_WINDOW->ExplanationContext += L"백페이스 컬링을 활성화하여 카메라에서 보이지 않는 뒷면을 제거합니다.";
}

void UTOutputWindow::Code_5_13()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.f, 1.f, 0.f, 1.1);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, Colors_5_13);
	glVertexPointer(3, GL_FLOAT, 0, Vertices_5_13);

	for (GLint i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &VertexList_5_13[4 * i]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glLoadIdentity();
	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_13_End()
{
	ResetAll();
	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_14_Start()
{
	ResetAll();
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	MyListID_5_14 = glGenLists(1);
	glNewList(MyListID_5_14, GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f); 
	glEnd();

	glEndList();

	MAIN_WINDOW->ExplanationContext = L"디스플레이 리스트를 사용하여 정적 지오메트리를 사전에 컴파일하고, \n";
	MAIN_WINDOW->ExplanationContext += L"렌더링 단계에서는 glCallList를 통해 미리 기록된 명령을 즉시 실행하는 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext += L"정사각형을 하나의 리스트로 생성한 뒤, 매 프레임마다 해당 리스트를 호출하여 효율적으로 동일한 도형을 렌더링합니다.";
}

void UTOutputWindow::Code_5_14()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	
	glCallList(MyListID_5_14);

	glFlush();
	glfwSwapBuffers(GetGLFWWindow());
}

void UTOutputWindow::Code_5_14_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glDeleteLists(MyListID_5_14, 1);

	MAIN_WINDOW->ExplanationContext = L"";
}

void UTOutputWindow::Code_5_15_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetCursorPosCallback(GetGLFWWindow(), Code_5_15_CursorPosition);
	glfwSetKeyCallback(GetGLFWWindow(), Code_5_15_Key);
	const std::string basepath = "Resource/Object/Wood_Table/";
	const std::string texbasepath = "Resource/Object/Wood_Table/textures";
	const std::string objpath = basepath + "Wood_Table.obj";
	RESOURCE_MANAGER->LoadObjWithMaterial(objpath, vertices_5_15, indices_5_15, materials_5_15);

	glClearColor(0.4f, 0.4f, 0.4f, 1.f);
	GLfloat mat_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat mat_ambient[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat mat_shininess[] = { 15.f };
	GLfloat light_specular[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
	GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.f };
	light_position_5_15[0] = 5.f;
	light_position_5_15[1] = 5.f;
	light_position_5_15[2] = 0.f;
	light_position_5_15[3] = 1.f;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

	FlatShadeMode_5_15 = false;
	WireframeMode_5_15 = false;

	MAIN_WINDOW->ExplanationContext = L"OBJ 모델과 머티리얼 정보를 로드하여 텍스처, 노멀, 조명 계산을 포함한 전통적인 OpenGL 고정 파이프라인 방식으로 3D 오브젝트를 렌더링하는 예제입니다.\n";
	MAIN_WINDOW->ExplanationContext += L"마우스 입력을 통해 카메라의 위치를 구면 좌표계로 변환하여 모델 주위를 회전하며 관찰할 수 있으며,\n";
	MAIN_WINDOW->ExplanationContext += L"광원 위치, 확산광·정반사광·환경광 등의 머티리얼 속성을 설정하여 실제와 유사한 조명 효과를 구현합니다.\n";
	MAIN_WINDOW->ExplanationContext += L"렌더링 시에는 텍스처 좌표, 노멀 벡터, 정점 위치를 기반으로 삼각형 단위로 모델을 그리며,\n";
	MAIN_WINDOW->ExplanationContext += L"쉐이딩 모드와 폴리곤 모드는 런타임에서 토글할 수 있도록 구성되어 있습니다.";
}

void UTOutputWindow::Code_5_15()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);

	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 	glm::vec3 eye{};
 	float theta_w = (cursor_xpos_5_15 / display_w) * 2.f * glm::pi<float>();
 	float theta_h = (cursor_ypos_5_15 / display_h) * glm::pi<float>();
 	eye.x = std::sin(theta_w) * 5.f;
 	eye.y = std::cos(theta_h) * 5.f;
 	eye.z = std::cos(theta_w) * 5.f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float)display_w / (float)display_h,
		0.1f,
		10000.0f
	);
	glLoadMatrixf(&projection[0][0]);
	// 뷰 행렬 설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::mat4 view = glm::lookAt(
		eye,
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	glLoadMatrixf(&view[0][0]);

	// 조명 위치는 여기서 다시 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_5_15);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGetError();
	if (!materials_5_15.empty() && materials_5_15[0].textureId != 0)
	{
		glBindTexture(GL_TEXTURE_2D, materials_5_15[0].textureId);
	}

	if (FlatShadeMode_5_15)
	{
		glShadeModel(GL_SMOOTH);
	}
	else
	{
		glShadeModel(GL_FLAT);
	}

	if (WireframeMode_5_15)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

 	glBegin(GL_TRIANGLES);
 	for (size_t i = 0; i < indices_5_15.size(); i++)
 	{
 		const Vertex& v = vertices_5_15[indices_5_15[i]];
 		glTexCoord2f(v.texcoord.x, v.texcoord.y);
 		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
 		glVertex3f(v.pos.x, v.pos.y, v.pos.z);
 	}
 	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();

	MAIN_WINDOW->DebugContext = L"Q : 종료\n";
	MAIN_WINDOW->DebugContext  = L"1 : 쉐이드 모드 전환 (현재: ";
	MAIN_WINDOW->DebugContext += (FlatShadeMode_5_15 ? L"플랫 쉐이딩)" : L"스무스 쉐이딩)\n");
	MAIN_WINDOW->DebugContext += L"2 : 폴리곤 모드 전환 (현재: ";
	MAIN_WINDOW->DebugContext += (WireframeMode_5_15 ? L"와이어프레임)" : L"채워진 폴리곤)\n");
}

void UTOutputWindow::Code_5_15_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	glfwSetMouseButtonCallback(GetGLFWWindow(), nullptr);
	glfwSetCursorPosCallback(GetGLFWWindow(), nullptr);
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);

	OUTPUT_WINDOW->WireframeMode_5_15 = true;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	OUTPUT_WINDOW->FlatShadeMode_5_15 = true;
	glShadeModel(GL_SMOOTH);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	for (auto& material : materials_5_15)
	{
		if (material.textureId != 0)
		{
			glDeleteTextures(1, &material.textureId);
			material.textureId = 0;
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glFlush();
	glGetError();

	MAIN_WINDOW->ExplanationContext = L"";
	MAIN_WINDOW->DebugContext = L"";
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
	if (Action != GLFW_PRESS)
		return;

	switch (Key)
	{
	case GLFW_KEY_Q:
	{
		exit(0);
		break;
	}
	case GLFW_KEY_1:
	{
		if (OUTPUT_WINDOW->FlatShadeMode_5_15)
		{
			OUTPUT_WINDOW->FlatShadeMode_5_15 = false;
		}
		else
		{
			OUTPUT_WINDOW->FlatShadeMode_5_15 = true;
		}
		break;
	}
	case GLFW_KEY_2:
	{
		if (OUTPUT_WINDOW->WireframeMode_5_15)
		{
			OUTPUT_WINDOW->WireframeMode_5_15 = false;
		}
		else
		{
			OUTPUT_WINDOW->WireframeMode_5_15 = true;
		}
	}
	}
}

void UTOutputWindow::Code_5_15_CursorPosition(GLFWwindow* Window, double xpos, double ypos)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	GLfloat _Matrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, _Matrix);
	const InsideStaticMath::OrthoBounds OutOrthoBound = InsideStaticMath::GetOrthoBoundsFromProjectionMatrix(_Matrix);

	int display_w, display_h;
	glfwGetFramebufferSize(OUTPUT_WINDOW->GetGLFWWindow(), &display_w, &display_h);
	std::array<double, 2> CursorCoords = InsideStaticMath::CursorPosFromOrthoCoords(display_w, display_h, OutOrthoBound, std::array<double, 2>{xpos, ypos});

	OUTPUT_WINDOW->cursor_xpos_5_15 = xpos;
	OUTPUT_WINDOW->cursor_ypos_5_15 = ypos;
}