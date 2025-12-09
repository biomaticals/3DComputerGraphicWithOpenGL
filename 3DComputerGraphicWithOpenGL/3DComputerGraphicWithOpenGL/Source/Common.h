// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct FExampleCode;

enum ETitleType
{
	TitleType_None = 0,
	TitleType_Part,
	TitleType_Chapter,
	TitleType_Section,
	TitleType_ExampleCode,
	TitleType_End,
};

struct FSection
{
	FSection();
	FSection(const std::wstring& InTitle);
    const FSection& operator=(const FSection& Other);
	bool IsValid() const;

	std::wstring Title;
	std::vector<FExampleCode> ExampleCodes;
};

struct FChapter
{
	FChapter();
	FChapter(const std::wstring& InTitle);
	const FChapter& operator=(const FChapter& Other);
	bool IsValid() const;

	std::wstring Title;
	std::vector<FSection> Sections;
};

struct FPart
{
	FPart();
	FPart(const std::wstring& InTitle);
	const FPart& operator=(const FPart& Other);
	bool IsValid() const;

	std::wstring Title;
	std::vector<FChapter> Chapters;
};

struct FBook
{
	FBook();

	std::vector<FPart> Parts;
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

struct MaterialInfo
{
	std::string name;
	glm::vec3 diffuse;		//Kd
	glm::vec3 ambient;		//Ka
	glm::vec3 specular;		//Ks
	float shininess;		//Ns
	std::string diffuseTex; //map_Kd
	unsigned int textureId = 0;
};

bool FileExists(const std::string& path);

bool LoadObjWithMaterial(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<MaterialInfo>& out_materials);

GLuint LoadTexture2D(const std::string& filename, bool flipY = false);