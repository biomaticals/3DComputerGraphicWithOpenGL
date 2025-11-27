// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Terrain.h"
#include "Manager/WindowManager.h"

Terrain::Terrain(pcStr heightFile, pcStr surfaceTexFile, GLuint width, GLint height)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	_map_width = width;
	_map_height = height;

	imgData = NULL;
	_texId_ground = 0;
	_texId_water = 0;
	_height = 0;

	imgData = stbi_load(surfaceTexFile, &imgWidth, &imgHeight, &imgChannels, 0);
	if (!imgData)
	{
		printf("Failed to load texture: %s\n", surfaceTexFile);
		throw std::exception();
	}
	glGenTextures(1, &_texId_ground);
	glBindTexture(GL_TEXTURE_2D, _texId_ground);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0,
		imgChannels == 4 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	stbi_image_free(imgData);

	const char* waterTexFile = "Resource/Object/space/water.bmp";
	imgData = stbi_load(waterTexFile, &imgWidth, &imgHeight, &imgChannels, 0);
	if (!imgData)
	{
		printf("Failed to load texture: %s\n", waterTexFile);
		throw std::exception();
	}
	glGenTextures(1, &_texId_water);
	glBindTexture(GL_TEXTURE_2D, _texId_water);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0,
		imgChannels == 4 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	stbi_image_free(imgData);

	_height = readRawData(heightFile, width, height);

	if(_height == nullptr)
	{
		printf("Failed to load height data: %s\n", heightFile);
		throw std::exception();
	}

	int i;
	for (i = 0, minHeight = 2^10; i < _map_width * height; i++)
	{
		if (minHeight > _height[i])
		{ 
			minHeight = _height[i];
		}
	}

	waterLevel = (GLfloat)minHeight + 15.f;
	for (int i = 0; i < _map_width * _map_height + 1; i++)
		_height[i] -= minHeight;

	baseTerrain = glGenLists(5);
	glNewList(baseTerrain, GL_COMPILE);
	TileTerrain(1);
	glEndList();
	glNewList(baseTerrain + 1, GL_COMPILE);
	TileTerrain(4);
	glEndList();
	glNewList(baseTerrain + 2, GL_COMPILE);
	TileTerrain(8);
	glEndList();
	glNewList(baseTerrain + 3, GL_COMPILE);
	TileTerrain(16);
	glEndList();
	glNewList(baseTerrain + 4, GL_COMPILE);
	RenderWater();
	glEndList();
}

Terrain::~Terrain()
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	if (_height) 
	{ 
		delete[] _height;
		_height = nullptr;
	}

	if (_texId_ground != 0) 
	{ 
		glDeleteTextures(1, &_texId_ground); 
	}

	if (_texId_water != 0) 
	{ 
		glDeleteTextures(1, &_texId_water); 
	}
}

void Terrain::RenderTerrain(GLfloat x, GLfloat y)
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	
	glPushMatrix();
	/*glScalef(1.0f, 0.2f, 1.0f);*/
	
	int i, j;

	//detail level1 지형
	//카메라가 위치한 곳에 한 블럭만 그린다.
	glPushMatrix();
	glTranslatef(getTileX(x) * (_map_width - 1), 0.0, getTileY(y) * (_map_height - 1));
	glCallList(baseTerrain);
	glPopMatrix();

	//detail level2 지형
	//level1블럭을 제외하고 3x3단위로 그린다.
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			if (!(i == 0 && j == 0))
			{
				glPushMatrix();
				glTranslatef(getTileX(x) * (_map_width - 1) + (i * (_map_width - 1)), 0.0, getTileY(y) * (_map_height - 1) + (j * (_map_height - 1)));
				glCallList(baseTerrain + 1);
				glPopMatrix();
			}
		}
	}
	//detail level3 지형
	//level2블럭을 제외하고 5x5단위로 그린다.
	for (i = -2; i < 3; i++)
	{
		for (j = -2; j < 3; j++)
		{
			if ((i < -1 || i>1) || (j < -1 || j>1))
			{
				glPushMatrix();
				glTranslatef(getTileX(x) * (_map_width - 1) + (i * (_map_width - 1)), 0.0, getTileY(y) * (_map_height - 1) + (j * (_map_height - 1)));
				glCallList(baseTerrain + 2);
				glPopMatrix();
			}
		}
	}
	//detail level4 지형
	//level2블럭을 제외하고 7x7단위로 그린다.
	for (i = -3; i < 4; i++)
	{
		for (j = -3; j < 4; j++)
		{
			if ((i < -2 || i>2) || (j < -2 || j>2))
			{
				glPushMatrix();
				glTranslatef(getTileX(x) * (_map_width - 1) + (i * (_map_width - 1)), 0.0, getTileY(y) * (_map_height - 1) + (j * (_map_height - 1)));
				glCallList(baseTerrain + 3);
				glPopMatrix();
			}
		}
	}
	//물 디스플레이 리스트
	//3x3면적에 그린다
	for (i = -2; i < 3; i++)
	{
		for (j = -2; j < 3; j++)
		{
			glPushMatrix();
			glTranslatef(getTileX(x) * (_map_width - 1) + (i * (_map_width)-1), 0.0, getTileY(y) * (_map_height - 1) + (j * (_map_height - 1)));
			glCallList(baseTerrain + 4);
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void Terrain::TileTerrain(GLint levelOfDetail)
{
	if (_height == nullptr)
	{
		printf("_height is invalid.\n");
		throw std::exception();
		return;
	}

	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _texId_ground);
	float coordX = (float)1.0 / (_map_width - 1);
	float coordZ = (float)1.0 / (_map_height - 1);
	for (int z = 0; z < _map_height; z += levelOfDetail)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < _map_width; x += levelOfDetail)
		{
			glTexCoord2f(coordX * x, coordZ * z);
			glVertex3f(x, _height[z * _map_height + x], z);
			if ((z + levelOfDetail) * _map_height + x <= _map_height * _map_width)
			{
				glTexCoord2f(coordX * x, coordZ * (z + levelOfDetail));
				glVertex3f(x, _height[(z + levelOfDetail) * _map_height + x], z + levelOfDetail);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Terrain::RenderWater()
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.f, 0.4f, 0.5f, 0.7f);

	glBindTexture(GL_TEXTURE_2D, _texId_water);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);		glVertex3f(0.f, waterLevel, 0.f);
	glTexCoord2f(15.f, 0.f);	glVertex3f(0.f, waterLevel, _map_height);
	glTexCoord2f(15.f, 15.f);	glVertex3f(_map_height, waterLevel, _map_height);
	glTexCoord2f(0.f, 15.f);	glVertex3f(_map_height, waterLevel, 0.f);
	glEnd();
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

Terrain::ubyte* Terrain::readRawData(pcStr filename, uint w, uint h)
{
	FILE* f;
	fopen_s(&f, filename, "rb");
	if (!f)
	{
		printf("file not found : %s\n", filename);
		throw std::exception();
	}

	fseek(f, 0, SEEK_END);
	long fileSize = ftell(f);
	rewind(f);
	printf("file size: %ld bytes\n", fileSize);

	ubyte* raw = new ubyte[w * h];// raw의 크기를 잡고
	size_t n = fread(raw, sizeof(ubyte), w * h, f);// 높이데이터읽어오기
	if (n != w * h)
	{ /* 오류 처리: 파일 경로/크기 확인, realloc 또는 초기화 */
		printf("file not found : %s\n", filename);
	}

	fclose(f);
	return raw;
}

GLfloat Terrain::getHeight(GLfloat _x, GLfloat _y)
{
	int x, y;
	if (_x < 0)
		x = _map_width + ((int)_x % _map_width);//텍스쳐이미지범위를 넘어가면 반대편좌표로
	else
		x = ((int)_x % _map_width);
	if (_y < 0)
		y = _map_height + ((int)_y % _map_height);
	else
		y = ((int)_y % _map_height);

	// 좌표값을 텍스쳐크기안에 한정시킴
	// 높이 데이터는 1차원배열에 저장되어 있으므로 행렬처리
	return (_height[y * _map_height + x] / 5 + 10);// 해당위치의 높이값 반환
}

GLint Terrain::getTileX(GLfloat x)
{
	if (x > 0)
		return ((int)x) / (int)_map_width;
	else
		return ((int)x) / (int)_map_width - 1;
}

GLint Terrain::getTileY(GLfloat y)
{
	if (y > 0)
		return ((int)y) / (int)_map_height;
	else
		return ((int)y) / (int)_map_height - 1;
}