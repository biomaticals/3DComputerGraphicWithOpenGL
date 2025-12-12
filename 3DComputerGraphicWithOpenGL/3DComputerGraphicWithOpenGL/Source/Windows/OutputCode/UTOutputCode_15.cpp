// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "CoreMinimal.h"
#include <fcntl.h>

void UTOutputWindow::Code_15_2_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glEnable(GL_AUTO_NORMAL);

	GLfloat light0_diffuse[] = { 0.f, 0.2f, 0.2f, 1.f };
	GLfloat light0_ambient[] = { 0.8f, 0.f, 0.f, 1.f };
	GLfloat light0_position[] = { 0.8f, -0.5f, 2.3f, 1.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	char* vertex_source = nullptr;
	char* frag_source = nullptr;

	h_vertex_15_2 = glCreateShader(GL_VERTEX_SHADER);
	h_frag_15_2 = glCreateShader(GL_FRAGMENT_SHADER);

	const char* VertexSourcePath = "Source/Windows/OutputCode/glsl_example.vert";
	char* VertexSourcePath_Safe = const_cast<char*>(RESOURCE_MANAGER->GetSafeFilePath(VertexSourcePath).c_str());

	const char* FragmentSourcePath = "Source/Windows/OutputCode/glsl_example.frag";
	char* FragmentSourcePath_Safe = const_cast<char*>(RESOURCE_MANAGER->GetSafeFilePath(FragmentSourcePath).c_str());
	
	vertex_source = ReadShaderSource(VertexSourcePath_Safe);
	frag_source = ReadShaderSource(FragmentSourcePath_Safe);
	
	const char* p_vertex_source = vertex_source;
	const char* p_frag_source = frag_source;
	
	glShaderSource(h_vertex_15_2, 1, &p_vertex_source, NULL);
	glShaderSource(h_frag_15_2, 1, &p_frag_source, NULL);
	
	free(vertex_source);
	free(frag_source);

	glCompileShader(h_vertex_15_2);

	GLint compiled = GL_FALSE;
	glGetShaderiv(h_vertex_15_2, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint length;
		glGetShaderiv(h_vertex_15_2, GL_INFO_LOG_LENGTH, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetShaderInfoLog(h_vertex_15_2, length, NULL, log);
			printf("Shader compile error:\n%s\n", log);
			free(log);
		}
	}

	glCompileShader(h_frag_15_2);
	glGetShaderiv(h_frag_15_2, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint length;
		glGetShaderiv(h_frag_15_2, GL_INFO_LOG_LENGTH, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetProgramInfoLog(h_frag_15_2, length, NULL, log);
			printf("Shader compile error:\n%s\n", log);
			free(log);
		}
	}
		
	h_program_15_2 = glCreateProgram();
	glAttachShader(h_program_15_2, h_vertex_15_2);
	glAttachShader(h_program_15_2, h_frag_15_2);
	glLinkProgram(h_program_15_2);

	GLint linked;
	glGetProgramiv(h_program_15_2, GL_LINK_STATUS, &linked);

	if (!linked) 
	{
		GLint length;
		glGetProgramiv(h_program_15_2, GL_INFO_LOG_LENGTH, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetProgramInfoLog(h_program_15_2, length, NULL, log);
			printf("Program link error:\n%s\n", log);
			free(log);
		}
	}

	glUseProgram(h_program_15_2);

	MAIN_WINDOW->ExplanationContext = L"GLSL을 사용해 간단한 정점 및 프래그먼트 셰이더를 작성하고 적용하는 예제입니다.\n";
}

void UTOutputWindow::Code_15_2()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 1.f, 1.f);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();

	glfwSwapBuffers(GetGLFWWindow());
	glFlush();
}

void UTOutputWindow::Code_15_2_End()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	glPopAttrib();
	glUseProgram(0);

	if (h_program_15_2)
	{
		glDeleteProgram(h_program_15_2);
		h_program_15_2 = 0;
	}

	if (h_vertex_15_2)
	{
		glDeleteShader(h_vertex_15_2);
		h_vertex_15_2 = 0;
	}

	if (h_frag_15_2)
	{
		glDeleteShader(h_frag_15_2);
		h_frag_15_2 = 0;
	}

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_AUTO_NORMAL);

	glPopAttrib();

	MAIN_WINDOW->ExplanationContext = L"";
}

char* UTOutputWindow::ReadShaderSource(char* fileName)
{
	FILE* p_Sourcefile = nullptr;
	char* contents = nullptr;
	int length = 0;

	if (fileName != nullptr)
	{
		// --- 파일 길이 구하기 (_sopen_s 사용) ---
		int tempfile = -1;
		if (_sopen_s(&tempfile, fileName, _O_RDONLY, _SH_DENYNO, 0) == 0)
		{
			length = _lseek(tempfile, 0, SEEK_END);
			_close(tempfile);
		}

		// --- 파일 열기 (fopen_s 사용) ---
		if (length > 0)
		{
			if (fopen_s(&p_Sourcefile, fileName, "rt") == 0 && p_Sourcefile != nullptr)
			{
				contents = (char*)malloc(sizeof(char) * (length + 1));
				if (contents != nullptr)
				{
					int readLen = (int)fread(contents, sizeof(char), length, p_Sourcefile);
					contents[readLen] = '\0';
				}
				fclose(p_Sourcefile);
			}
		}
	}

	return contents;
}