// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "CoreMinimal.h"

void UTOutputWindow::Code_15_2_Start()
{
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 1.f, 1.f, 1.f);

	glEnable(GL_AUTO_NORMAL);

	GLfloat light0_diffuse[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat light0_ambient[] = { 0.8, 0.0, 0.0, 1.0 };
	GLfloat light0_position[] = { 0.8, -0.5, 2.3, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	char* vertex_source = nullptr;
	char* frag_source = nullptr;

	h_vertex_15_2 = glCreateShader(GL_VERTEX_SHADER);
	h_frag_15_2 = glCreateShader(GL_FRAGMENT_SHADER);

	char VertexSourcePath[] = "Source/Windows/OutputCode/glsl_example.vert";
	char FragmentSourcePath[] = "Source/Windows/OutputCode/glsl_example.frag";
	
	vertex_source = ReadShaderSource(VertexSourcePath);
	frag_source = ReadShaderSource(FragmentSourcePath);
	
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
	ResetAll();
	glfwMakeContextCurrent(GetGLFWWindow());
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

	MAIN_WINDOW->ExplanationContext = L"";
}

char* UTOutputWindow::ReadShaderSource(char* fileName)
{
	FILE* p_Sourcefile = NULL;
	char* contents = NULL;
	int length = 0;
	if (fileName != NULL)
	{
		int tempfile = _open(fileName, _A_RDONLY);
		length = _lseek(tempfile, 0, SEEK_END);
		_close(tempfile);

		p_Sourcefile = fopen(fileName, "rt");
		if (p_Sourcefile != NULL) 
		{
			if (0 < length) 
			{
				contents = (char*)malloc(sizeof(char) * (length + 1));
				length = fread(contents, sizeof(char), length, p_Sourcefile);
				contents[length] = '\0';
			}
			fclose(p_Sourcefile);
		}
	}
	return contents;
}