// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Skybox.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "Manager/WindowManager.h"

#define TEX_SIZE 3
#define GL_CLAMP_TO_EDGE 0x812F

const char* texFiles[6] = 
{
	"Resource/Object/space/front.bmp",
	"Resource/Object/space/back.bmp",
	"Resource/Object/space/left.bmp",
	"Resource/Object/space/right.bmp",
	"Resource/Object/space/up.bmp",
	"Resource/Object/space/down.bmp"
};

Skybox::Skybox(void)
{
	for (int i = 0; i < 6; i++)
		textures[i] = _loadTexture(texFiles[i]);
}

Skybox::~Skybox(void) 
{
}

void Skybox::draw() 
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glColor3f(0, 0, 0);

	// front
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(-TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glEnd();

	// front (V 좌표 반전)
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	glEnd();

	//// back
	//glBindTexture(GL_TEXTURE_2D, textures[1]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(-TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glEnd();
	//
	//// left
	//glBindTexture(GL_TEXTURE_2D, textures[2]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glEnd();
	//
	//// right
	//glBindTexture(GL_TEXTURE_2D, textures[3]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(-TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(-TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glEnd();
	//
	//// up
	//glBindTexture(GL_TEXTURE_2D, textures[4]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(-TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(TEX_SIZE, TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(-TEX_SIZE, TEX_SIZE, TEX_SIZE);
	//glEnd();
	//
	//// down
	//glBindTexture(GL_TEXTURE_2D, textures[5]);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 0.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 0.0); glVertex3f(TEX_SIZE, -TEX_SIZE, TEX_SIZE);
	//glTexCoord2f(1.0, 1.0); glVertex3f(TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glTexCoord2f(0.0, 1.0); glVertex3f(-TEX_SIZE, -TEX_SIZE, -TEX_SIZE);
	//glEnd();

	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

Skybox::uint Skybox::_loadTexture(pcStr filename) 
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	int w, h, channels;
	unsigned char* data = stbi_load(filename, &w, &h, &channels, 0);
	if (!data) 
	{
		printf("Failed to load texture: %s\n", filename);
	}

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
		channels == 4 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	stbi_image_free(data);
	return texId;
}
