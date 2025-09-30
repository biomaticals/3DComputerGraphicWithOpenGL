// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <windows.h>
#include "CoreMinimal.h"
#include "Common.h"
#include <string>
#include "Windows/UTMainWindow.h"
#include "Windows/UTOutputWindow.h"

void UpdateManager();

int main(int, char**);
static void glfw_error_callback(int error, const char* description);


// math, helper, utilities below
#include <GL/glu.h>
#include <array>

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

#include "tiny_obj_loader.h"

std::vector<float> Tiny_VertexBuffer;
std::vector<float> Tiny_NormalBuffer;
std::vector<float> Tiny_TexcoordBuffer;

void LoadOBJ(const std::string& filename) 
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());
	if (!ret) {
		throw std::runtime_error(warn + err);
	}

	// 정점/노멀/UV를 하나의 배열로 풀어내기
	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			// 정점
			Tiny_VertexBuffer.push_back(attrib.vertices[3 * index.vertex_index + 0]);
			Tiny_VertexBuffer.push_back(attrib.vertices[3 * index.vertex_index + 1]);
			Tiny_VertexBuffer.push_back(attrib.vertices[3 * index.vertex_index + 2]);

			// 노멀
			if (index.normal_index >= 0) {
				Tiny_NormalBuffer.push_back(attrib.normals[3 * index.normal_index + 0]);
				Tiny_NormalBuffer.push_back(attrib.normals[3 * index.normal_index + 1]);
				Tiny_NormalBuffer.push_back(attrib.normals[3 * index.normal_index + 2]);
			}

			// 텍스처 좌표
			if (index.texcoord_index >= 0) {
				Tiny_TexcoordBuffer.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
				Tiny_TexcoordBuffer.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
			}
		}
	}
}
