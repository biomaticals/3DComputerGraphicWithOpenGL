// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <Windows.h>
#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


void UpdateManager()
{
	RESOURCE_MANAGER->Update();
}

int main(int, char**)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	IMGUI_CHECKVERSION();

	WINDOW_MANAGER->CreateMainWindow();
	WINDOW_MANAGER->CreateOutputWindow();

	glfwMakeContextCurrent(MAIN_WINDOW->GetGLFWWindow());
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

// OBJ 로드(텍스처 무시)
bool LoadObjSimple(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;
	std::string base_dir = path.substr(0, path.find_last_of("/\\"));

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), base_dir.c_str());
	if (!ret) return false;

	// 임시 법선 저장: attrib.normals 사용; 없으면 계산
	bool hasNormals = !attrib.normals.empty();

	// 임시: 면법선 누적용
	std::vector<glm::vec3> vertex_normals(attrib.vertices.size() / 3, glm::vec3(0.0f));

	// 고유 정점 매핑
	std::unordered_map<std::string, unsigned int> uniqueMap;
	out_vertices.clear();
	out_indices.clear();

	for (size_t s = 0; s < shapes.size(); ++s) {
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			// 면의 정점 인덱스 번호 모으기 (삼각형이 아닌 경우도 처리)
			std::vector<int> face_vi;
			std::vector<int> face_ni;
			for (int v = 0; v < fv; ++v) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				face_vi.push_back(idx.vertex_index);
				face_ni.push_back(idx.normal_index);
			}
			// 면법선 계산(삼각형 분해)
			if (!hasNormals && fv >= 3) {
				glm::vec3 v0{
				  attrib.vertices[3 * face_vi[0] + 0],
				  attrib.vertices[3 * face_vi[0] + 1],
				  attrib.vertices[3 * face_vi[0] + 2]
				};
				glm::vec3 v1{
				  attrib.vertices[3 * face_vi[1] + 0],
				  attrib.vertices[3 * face_vi[1] + 1],
				  attrib.vertices[3 * face_vi[1] + 2]
				};
				glm::vec3 v2{
				  attrib.vertices[3 * face_vi[2] + 0],
				  attrib.vertices[3 * face_vi[2] + 1],
				  attrib.vertices[3 * face_vi[2] + 2]
				};
				glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));
				for (int v = 0; v < fv; ++v) {
					vertex_normals[face_vi[v]] += n;
				}
			}
			// 인덱스/정점 생성 (각 면 정점마다)
			for (int v = 0; v < fv; ++v) {
				int vi = face_vi[v];
				int ni = face_ni[v];
				std::string key = make_key(vi, ni >= 0 ? ni : -1);
				auto it = uniqueMap.find(key);
				if (it != uniqueMap.end()) {
					out_indices.push_back(it->second);
				}
				else {
					Vertex vert;
					vert.pos = glm::vec3(
						attrib.vertices[3 * vi + 0],
						attrib.vertices[3 * vi + 1],
						attrib.vertices[3 * vi + 2]
					);
					if (hasNormals && ni >= 0) {
						vert.normal = glm::vec3(
							attrib.normals[3 * ni + 0],
							attrib.normals[3 * ni + 1],
							attrib.normals[3 * ni + 2]
						);
					}
					else {
						vert.normal = vertex_normals[vi]; // 나중에 정규화
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

	// 법선 정규화(계산된 경우)
	for (auto& v : out_vertices) {
		if (glm::length(v.normal) > 0.0f)
			v.normal = glm::normalize(v.normal);
		else
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f); // 안전값
	}

	return true;
}