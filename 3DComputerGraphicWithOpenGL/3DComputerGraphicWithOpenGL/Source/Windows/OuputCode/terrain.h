// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <exception>
#include <math.h>
#include "stb_image.h"
#include "camera.h"

class Terrain
{
private:
	typedef const char* pcStr;
	typedef unsigned int uint;
	typedef unsigned char ubyte;
	uint _texId_ground, _texId_water;
	int imgWidth, imgHeight, imgChannels;
	unsigned char* imgData;
	ubyte* _height;
	GLint _map_width, _map_height;
	GLuint baseTerrain;
	GLubyte minHeight;
	static ubyte* readRawData(pcStr filename, uint width, uint height);
public:
	Terrain(pcStr heightmap, pcStr surfaceTex, GLuint width, GLint height);
	~Terrain(void);
	void RenderTerrain(GLfloat, GLfloat);
	void TileTerrain(GLint);
	void RenderWater(void);
	GLfloat getHeight(GLfloat, GLfloat);
	GLint getTileX(GLfloat);
	GLint getTileY(GLfloat);
	GLfloat waterLevel;
};
