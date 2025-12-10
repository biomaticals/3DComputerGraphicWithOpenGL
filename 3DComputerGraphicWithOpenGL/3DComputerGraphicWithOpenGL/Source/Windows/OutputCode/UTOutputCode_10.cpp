// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

//#include <GL/freeglut_std.h>

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"

void UTOutputWindow::Code_10_11_Start()
{
    ResetAll();
    glfwMakeContextCurrent(GetGLFWWindow()); 
    glfwSetKeyCallback(GetGLFWWindow(), UTOutputWindow::Code_10_11_Key);

    MAIN_WINDOW->ExplanationContext = L"두 개의 광원을 사용한 조명 효과 예제입니다";
}

void UTOutputWindow::Code_10_11()
{
    glfwMakeContextCurrent(GetGLFWWindow());
    int display_w, display_h;
    glfwGetWindowSize(GetGLFWWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat LightPosition0[] = {0.0, 0.0, 2.0, 1.0};
    GLfloat LightPosition1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat LightDirection1[] = {-0.5, -1.0, -1.0};
    GLfloat SpotAngle1[] = {20.0};
    
    GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.f};

    GLfloat light0_ambient[] = {0.5f, 0.4f, 0.3f, 1.f};
    GLfloat light0_diffuse[] = {0.5f, 0.4f, 0.3f, 1.f};
    GLfloat light0_specular[] = {1.f, 1.f, 1.f, 1.f};

    GLfloat light1_ambient[] = {0.f, 0.f, 0.f, 1.f};
    GLfloat light1_diffuse[] = {0.5f, 0.2f, 0.3f, 1.f};
    GLfloat light1_specular[] = {0.f, 0.f, 0.f, 1.f};

    GLfloat material_ambient[] = {0.3f, 0.3f, 0.3f, 1.f};
    GLfloat material_diffuse[] = {0.8f, 0.8f, 0.8f, 1.f};
    GLfloat material_specular[] = {0.f, 0.f, 1.f, 1.f};
    GLfloat material_shininess[] = {25.f};

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);        
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);        
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
    
    if (bEnableLight0_10_11)
    {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    }
    else
    {
        glDisable(GL_LIGHT0);
    }
    
    if (bEnableLight1_10_11)
    {
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    }
    else
    {
        glDisable(GL_LIGHT1);
    }
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.5f, 0.5f, 0.5f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
    glTranslatef(0.3f, 0.3f, 0.f);
    
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

    float innerRadius = 0.3f;
    float outerRadius = 0.6f;
    int nsides = 800;
    int rings = 800;

    for (int i = 0; i < rings; i++) {
        float phi = (float)i * 2.f * M_PI / (float)rings;
        float nextPhi = (float)(i + 1) * 2.0f * M_PI / (float)rings;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= nsides; j++) {
            float theta = (float)j * 2.0f * M_PI / nsides;

            // 첫 번째 원
            float x1 = (outerRadius + innerRadius * cos(theta)) * cos(phi);
            float y1 = (outerRadius + innerRadius * cos(theta)) * sin(phi);
            float z1 = innerRadius * sin(theta);

            // 두 번째 원 (nextPhi)
            float x2 = (outerRadius + innerRadius * cos(theta)) * cos(nextPhi);
            float y2 = (outerRadius + innerRadius * cos(theta)) * sin(nextPhi);
            float z2 = innerRadius * sin(theta);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    
    std::wstringstream wss{};
    wss << L"1 : 0번 조명 켜기/끄기  (" << (bEnableLight0_10_11 ? L"켜짐)\n" : L"꺼짐)\n")  << L"2 : 1번 조명 켜기/끄기  (" << (bEnableLight1_10_11 ? L"켜짐)\n" : L"꺼짐)\n");
    MAIN_WINDOW->DebugContext = wss.str(); 
    
    glfwSwapBuffers(GetGLFWWindow());
    glFlush();
}

void UTOutputWindow::Code_10_11_End()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
	glfwSetKeyCallback(GetGLFWWindow(), nullptr);

	MAIN_WINDOW->DebugContext = L"";
}

void UTOutputWindow::Code_10_11_Key(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    
    glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());

    if (Action == GLFW_PRESS)
    {
        switch (Key)
        {
        case GLFW_KEY_1:
            {
                OUTPUT_WINDOW->bEnableLight0_10_11 = !OUTPUT_WINDOW->bEnableLight0_10_11;
                break;
            }
        case GLFW_KEY_2:
            {
                OUTPUT_WINDOW->bEnableLight1_10_11 = !OUTPUT_WINDOW->bEnableLight1_10_11;
                break;
            }
        }
    }
}

void UTOutputWindow::Code_10_12_Start()
{
    ResetAll();
    
    Time_10_12 = (GLfloat)glfwGetTime();
    ElapsedTime_10_12 = 0.f;
    LightSpinAngle_10_12 = 0.f;

	MAIN_WINDOW->ExplanationContext = L"광원의 위치를 회전시켜가며 구의 조명 효과를 구현하는 예제입니다";
}

void UTOutputWindow::Code_10_12()
{
    int display_w{}, display_h{};
    glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ElapsedTime_10_12 = (GLfloat)glfwGetTime() - (GLfloat)Time_10_12;
    Time_10_12 = (GLfloat)glfwGetTime();
    
    LightSpinAngle_10_12 += ElapsedTime_10_12 * 20.f;
    
    GLfloat LightPosition[] = {0.f, 0.f, 1.5f, 1.f};
    
    GLfloat light0_ambient[] = {0.5f, 0.4f, 0.3f, 1.f};
    GLfloat light0_diffuse[] = {0.8f, 0.7f, 0.6f, 1.f};
    GLfloat light0_specular[] = {1.f, 1.f, 1.f, 1.f};
    
    GLfloat material_ambient[] = {0.4f, 0.4f, 0.4f, 1.f};
    GLfloat material_diffuse[] = {0.9f, 0.9f, 0.9f, 1.f};
    GLfloat material_specular[] = {1.f, 1.f, 1.f, 1.f};
    GLfloat material_shininess[] = {25.f};
    
	GLfloat LightPosition2[] = { 0.f, 0.f, 1.5f, 1.f };
    
	GLfloat light0_ambient2[] = { 0.5f, 0.4f, 0.3f, 1.f };
	GLfloat light0_diffuse2[] = { 0.8f, 0.7f, 0.6f, 1.f };
	GLfloat light0_specular2[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat ConstantAttenuation2;
	GLfloat LinearAttenuation2;
	GLfloat QuadraticAttenuation2;
    
	GLfloat material_ambient2[] = { 0.4f, 0.4f, 0.4f, 1.f };
	GLfloat material_diffuse2[] = { 0.9f, 0.9f, 0.9f, 1.f };
	GLfloat material_specular2[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat material_shininess2[] = { 25.f };
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
	//glGetLightfv(GL_LIGHT0, GL_POSITION, LightPosition2);
	//glGetLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient2);
	//glGetLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse2);
	//glGetLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular2);
    //glGetLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &ConstantAttenuation2);
	//glGetLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &LinearAttenuation2);
	//glGetLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &QuadraticAttenuation2);
    //
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,   0.f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.1f);
    //
	//glGetMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient2);
	//glGetMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse2);
	//glGetMaterialfv(GL_FRONT, GL_SPECULAR, material_specular2);
	//glGetMaterialfv(GL_FRONT, GL_SHININESS, material_shininess2);
    //
    glMaterialfv(GL_FRONT, GL_AMBIENT,  material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.f, (GLfloat)display_w / (GLfloat)display_h, 0.1f, 100.f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
    glPushMatrix();
        glTranslatef(0.f, 0.f, -5.f);
        glPushMatrix();
            glRotatef(LightSpinAngle_10_12, 1.f, 0.f, 0.f);
            glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
        glPopMatrix();
        
        glColor3f(0.9f, 0.9f, 0.9f);
        for (int i = 0; i < Stacks_10_12; ++i)
        {
            float phi0 = M_PI * float(i) / Stacks_10_12;
            float phi1 = M_PI * float(i + 1) / Stacks_10_12;
    
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= Slices_10_12; ++j)
            {
                float theta = 2.0f * M_PI * float(j) / Slices_10_12;
                auto emit = [&](float phi)
                {
                    float y = std::cos(phi), rxy = std::sin(phi);
                    float x = rxy * std::cos(theta), z = rxy * std::sin(theta);
                    glNormal3f(x, y, z);
                    glTexCoord2f(theta / (2.0f * M_PI), phi / M_PI);
                    glVertex3f(x, y, z);
                };
                emit(phi0);
                emit(phi1);
            }
            glEnd();
        }
    glPopMatrix();
    
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    glfwSwapBuffers(GetGLFWWindow());
    glFlush();
}

void UTOutputWindow::Code_10_12_End()
{
    ResetAll();

	MAIN_WINDOW->DebugContext = L"";
}