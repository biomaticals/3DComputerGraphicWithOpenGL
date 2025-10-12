// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <windows.h>
#include "CoreMinimal.h"
#include "Common.h"
#include <string>
#include "Windows/UTMainWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>
// math, helper, utilities below
#include <GL/glu.h>
#include <array>

void UpdateManager();

int main(int, char**);

struct Vertex 
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

struct MaterialInfo 
{
	std::string name;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	float shininess;
	std::string diffuseTex;
};

inline static std::string make_key(int vi, int ni) 
{
	return std::to_string(vi) + "_" + std::to_string(ni);
}

bool LoadObjWithMaterial(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<MaterialInfo>& out_materials);

inline std::string WStringToUtf8(const std::wstring& wstr) 
{
	if (wstr.empty()) 
	return {};
	
	int size_needed = WideCharToMultiByte(CP_UTF8, 0,
		wstr.data(), (int)wstr.size(),
		nullptr, 0, nullptr, nullptr);
	std::string strTo(size_needed, 0);
	
	WideCharToMultiByte(CP_UTF8, 0,
		wstr.data(), (int)wstr.size(),
		strTo.data(), size_needed,
		nullptr, nullptr);
	return strTo;
}

struct OrthoBounds
{
	float _left, _right;
	float _bottom, _top;
	float _near, _far;
};

//|  2 / (r - l)     0               0              - (r + l) / (r - l) |
//|  0               2 / (t - b)     0              - (t + b) / (t - b) |
//|  0               0               - 2 / (f - n)  - (f + n) / (f - n) |
//|  0               0               0                        1         |

inline OrthoBounds GetOrthoBoundsFromProjectionMatrix()
{
	GLfloat m[16];
	glGetFloatv(GL_PROJECTION_MATRIX, m);

	// OpenGL은 column-major 방식
	float a = m[0];  // 2 / (r - l)
	float b = m[12]; // -(r + l) / (r - l)

	float c = m[5];  // 2 / (t - b)
	float d = m[13]; // -(t + b) / (t - b)

	float e = m[10]; // -2 / (f - n)
	float f = m[14]; // -(f + n) / (f - n)

	OrthoBounds bounds;

	bounds._left = b / a - 1.f;
	bounds._right = b / a + 1.f;

	bounds._bottom = d / c - 1.f;
	bounds._top = d / c + 1.f;

	bounds._near = -(f / e + 1.f);
	bounds._far = -(f / e - 1.f);

	return bounds;
}

inline std::array<double, 2> CursorPosToOrthoCoords(GLFWwindow* Window, const std::array<double, 2>& CursorCoords)
{
	OrthoBounds OrthoBound = GetOrthoBoundsFromProjectionMatrix();

	int width, height;
	glfwGetFramebufferSize(Window, &width, &height);


	double orthoX = CursorCoords[0] / (double)width * (OrthoBound._right - OrthoBound._left) + OrthoBound._left;
	double orthoY = -CursorCoords[1] / (double)height * (OrthoBound._top - OrthoBound._bottom) + OrthoBound._top;
	return { orthoX, orthoY};
}