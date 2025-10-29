// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <Windows.h>
#include <glad/glad.h>
#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void UpdateManager()
{
	RESOURCE_MANAGER->Update();
}

int main(int, char**)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	IMGUI_CHECKVERSION();

	WINDOW_MANAGER->CreateMainWindow();
	WINDOW_MANAGER->CreateOutputWindow();

	glfwMakeContextCurrent(MAIN_WINDOW->GetGLFWWindow());
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		return -1;
	}


	ImGui::SetCurrentContext(MAIN_WINDOW->GetGuiContext());
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui_ImplGlfw_InitForOpenGL(MAIN_WINDOW->GetGLFWWindow(), true);
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
	while (MAIN_WINDOW->ShouldClose() == false)
	{
		UpdateManager();
		glfwPollEvents();
		
		MAIN_WINDOW->NewFrame();
		MAIN_WINDOW->RenderUI();
		MAIN_WINDOW->RenderDrawData();
	
		if (OUTPUT_WINDOW)
		{
			if (OUTPUT_WINDOW->ShouldClose() == false)
			{
				OUTPUT_WINDOW->NewFrame();
				OUTPUT_WINDOW->RenderDrawData();
			}
			else
			{
				WINDOW_MANAGER->HideOutputWindow();
			}
		}
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	
	WINDOW_MANAGER->DestroyMainWindow();
	WINDOW_MANAGER->DestroyOutputWindow();

	return 0;
}

bool FileExists(const std::string& path) {
	std::ifstream f(path.c_str());
	return f.good();
}

bool LoadObjWithMaterial(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<MaterialInfo>& out_materials)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;
	std::string base_dir = path.substr(0, path.find_last_of("/\\"));

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), base_dir.c_str());
	if (!ret) return false;

	// 머티리얼 정보 저장
	out_materials.clear();
	for (auto& m : materials) {
		MaterialInfo mat;
		mat.name = m.name;
		mat.diffuse = glm::vec3(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
		mat.ambient = glm::vec3(m.ambient[0], m.ambient[1], m.ambient[2]);
		mat.specular = glm::vec3(m.specular[0], m.specular[1], m.specular[2]);
		mat.shininess = m.shininess;

		auto fixPath = [](std::string path) {
			std::replace(path.begin(), path.end(), '\\', '/');
			return path;
			};

		std::string texPath;
		if (!m.diffuse_texname.empty()) {
			texPath = base_dir + "/" + fixPath(m.diffuse_texname);
			if (!FileExists(texPath)) {
				texPath.clear();
			}
		}

		if (texPath.empty() && !m.specular_texname.empty()) {
			std::string specPath = base_dir + "/" + fixPath(m.specular_texname);
			if (FileExists(specPath)) {
				texPath = specPath;
			}
		}

		if (!texPath.empty()) {
			mat.diffuseTex = texPath;
			mat.textureId = LoadTexture2D(texPath);
		}

		out_materials.push_back(mat);
	}

	// 정점/인덱스 생성
	std::unordered_map<std::string, unsigned int> uniqueMap;
	out_vertices.clear();
	out_indices.clear();

	for (size_t s = 0; s < shapes.size(); ++s) {
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			for (int v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				// 키 생성
				std::string key = std::to_string(idx.vertex_index) + "/" +
					std::to_string(idx.normal_index) + "/" +
					std::to_string(idx.texcoord_index);

				auto it = uniqueMap.find(key);
				if (it != uniqueMap.end()) {
					out_indices.push_back(it->second);
				}
				else {
					Vertex vert;
					// 위치
					vert.pos = glm::vec3(
						attrib.vertices[3 * idx.vertex_index + 0],
						attrib.vertices[3 * idx.vertex_index + 1],
						attrib.vertices[3 * idx.vertex_index + 2]
					);
					// 법선
					if (idx.normal_index >= 0) {
						vert.normal = glm::vec3(
							attrib.normals[3 * idx.normal_index + 0],
							attrib.normals[3 * idx.normal_index + 1],
							attrib.normals[3 * idx.normal_index + 2]
						);
					}
					else {
						vert.normal = glm::vec3(0, 1, 0); // fallback
					}
					// 텍스처 좌표
					if (idx.texcoord_index >= 0) {
						vert.texcoord = glm::vec2(
							attrib.texcoords[2 * idx.texcoord_index + 0],
							attrib.texcoords[2 * idx.texcoord_index + 1]
						);
					}
					else {
						vert.texcoord = glm::vec2(0, 0);
					}

					unsigned int newIndex = static_cast<unsigned int>(out_vertices.size());
					uniqueMap[key] = newIndex;
					out_vertices.push_back(vert);
					out_indices.push_back(newIndex);
				}
			}
			index_offset += fv;
		}
	}

	return true;
}

GLuint LoadTexture2D(const std::string& filename, bool flipY)
{
	if (flipY)
		stbi_set_flip_vertically_on_load(false);

	int w = 0, h = 0, channels = 0;
	unsigned char* data = stbi_load(filename.c_str(), &w, &h, &channels, 0);
	if (!data) {
		std::cerr << "Failed to load texture: " << filename << std::endl;
		return 0;
	}

	GLenum format = GL_RGB;
	if (channels == 4)      format = GL_RGBA;
	else if (channels == 3) format = GL_RGB;
	else if (channels == 1) format = GL_RED;

	std::cout << "Loaded " << filename << " size: " << w << "x" << h << " channels: " << channels << std::endl;

	GLuint texId = 0;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLint texW = 0, texH = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texW);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texH);
	std::cout << "GPU texture size: " << texW << "x" << texH << std::endl;


	stbi_image_free(data);
	return texId;
}
