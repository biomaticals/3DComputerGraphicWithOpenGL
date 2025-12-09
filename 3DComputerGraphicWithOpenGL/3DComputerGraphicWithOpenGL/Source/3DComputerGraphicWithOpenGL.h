// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <windows.h>

#include "CoreMinimal.h"
#include "Common.h"
#include <vector>
#include <GL/glu.h>
#include <array>

inline ImFont* DefaultFont = nullptr;
inline ImFont* MediumFont = nullptr;
inline ImFont* BigFont = nullptr;
inline ImFont* MonospaceFont = nullptr;

void UpdateManager();

int main(int, char**);

inline static std::string make_key(int vi, int ni) 
{
	return std::to_string(vi) + "_" + std::to_string(ni);
}

bool LoadObjWithMaterial(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<MaterialInfo>& out_materials);

GLuint LoadTexture2D(const std::string& filename, bool flipY = false);


