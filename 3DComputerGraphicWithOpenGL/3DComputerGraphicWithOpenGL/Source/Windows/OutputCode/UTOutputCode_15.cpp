// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Windows/UTOutputWindow.h"
#include "Manager/WindowManager.h"
#include "CoreMinimal.h"

void UTOutputWindow::Code_15_2_Start()
{
	glfwMakeContextCurrent(GetGLFWWindow());

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_AUTO_NORMAL);
	GLfloat light0_diffuse[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat light0_ambient[] = { 0.8, 0.0, 0.0, 1.0 };
	GLfloat light0_position[] = { 0.8, -0.5, 2.3, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	char* vertex_source, * frag_source;
	h_vertex_15_2 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	h_frag_15_2 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	char VertexSourcePath[] = "Source/Windows/OutputCode/glsl_example.vert";
	char FragmentSourcePath[] = "Source/Windows/OutputCode/glsl_example.frag";
	vertex_source = ReadShaderSource(VertexSourcePath);
	frag_source = ReadShaderSource(FragmentSourcePath);
	const char* p_vertex_source = vertex_source;
	const char* p_frag_source = frag_source;
	glShaderSourceARB(h_vertex_15_2, 1, &p_vertex_source, NULL);
	glShaderSourceARB(h_frag_15_2, 1, &p_frag_source, NULL);
	free(vertex_source);
	free(frag_source);

	glCompileShaderARB(h_vertex_15_2);
	GLint compiled;
	glGetObjectParameterivARB(h_vertex_15_2, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);

	if (!compiled)
	{
		GLint length;
		glGetObjectParameterivARB(h_vertex_15_2, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetInfoLogARB(h_vertex_15_2, length, NULL, log);
			printf("Shader compile error:\n%s\n", log);
			free(log);
		}
	}

	glCompileShaderARB(h_frag_15_2);
	glGetObjectParameterivARB(h_frag_15_2, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);

	if (!compiled)
	{
		GLint length;
		glGetObjectParameterivARB(h_frag_15_2, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetInfoLogARB(h_frag_15_2, length, NULL, log);
			printf("Shader compile error:\n%s\n", log);
			free(log);
		}
	}
		
	h_program_15_2 = glCreateProgramObjectARB();
	glAttachObjectARB(h_program_15_2, h_vertex_15_2);
	glAttachObjectARB(h_program_15_2, h_frag_15_2);
	glLinkProgramARB(h_program_15_2);

	GLint linked;
	glGetObjectParameterivARB(h_program_15_2, GL_OBJECT_LINK_STATUS_ARB, &linked);

	if (!linked) 
	{
		GLint length;
		glGetObjectParameterivARB(h_program_15_2, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

		if (length > 1)
		{
			char* log = (char*)malloc(length);
			glGetInfoLogARB(h_program_15_2, length, NULL, log);
			printf("Program link error:\n%s\n", log);
			free(log);
		}
	}

	glUseProgramObjectARB(h_program_15_2);
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
	glfwMakeContextCurrent(GetGLFWWindow());
	if (h_program_15_2)
	{
		glDeleteObjectARB(h_program_15_2);
		h_program_15_2 = 0;
	}

	if (h_vertex_15_2)
	{
		glDeleteObjectARB(h_vertex_15_2);
		h_vertex_15_2 = 0;
	}

	if (h_frag_15_2)
	{
		glDeleteObjectARB(h_frag_15_2);
		h_frag_15_2 = 0;
	}
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