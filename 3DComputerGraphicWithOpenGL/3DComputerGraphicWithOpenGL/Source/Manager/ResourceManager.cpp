// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"
#include "Windows/UTOutputWindow.h"
#include "format"
#include <regex>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#if defined(_WIN64)
#define PLATFORM L"Win64"
#elif defined(_WIN32)
#define PLATFORM L"Win32"
#else
#define PLATFORM L"UnknownPlatform"
#endif

#if defined(_DEBUG)
#define CONFIGURATION L"Debug"
#else
#define CONFIGURATION L"Release"
#endif

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{
	hDll = nullptr;
	if (LoadDynamicLibraries())
	{
		std::cerr << "Dynamic Libraries Loaded Successfully.\n";
	}
}

ResourceManager::~ResourceManager()
{

	Destroy();
}

ResourceManager* ResourceManager::GetResourceManager()
{
	if (Instance == nullptr)
	{
		Instance = new ResourceManager();
	}

	return Instance;
}

void ResourceManager::Destroy()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void ResourceManager::Update()
{
}

#pragma region Load & Unload
bool ResourceManager::LoadResources()
{
	return true;
}

void ResourceManager::UnloadResources()
{

}

bool ResourceManager::LoadDynamicLibraries()
{
	std::wstring dllPath = L"../../../InsideDynamicMathLibrary/Binaries/" + std::wstring(PLATFORM) + L"/" + std::wstring(CONFIGURATION) + L"/InsideDynamicMathLibrary.dll";
	 hDll = LoadLibrary(dllPath.c_str());
	if (!hDll)
	{
		std::cerr << "Failed to load InsideDynaicMath.dll";
	}

	Execute_OpenFileToWStream = (OpenFileToWStream)GetProcAddress(hDll, "OpenFileToWStream");

	if (!Execute_OpenFileToWStream)
		return false;

	return true;
}

void ResourceManager::UnloadDynamicLibraries()
{
	if(hDll)
		FreeLibrary(hDll);
}

bool ResourceManager::FileExists(const std::string& path) {
	std::ifstream f(path.c_str());
	return f.good();
}

bool ResourceManager::LoadObjWithMaterial(const std::string& path,
	std::vector<Vertex>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<MaterialInfo>& out_materials)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;
	std::string base_dir = path.substr(0, path.find_last_of("/\\"));

	bool Result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), base_dir.c_str());
	if (Result == false)
	{
		std::string exepath = "../../../3DComputerGraphicWithOpenGL/" + path;
		base_dir = exepath.substr(0, exepath.find_last_of("/\\"));
		Result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, exepath.c_str(), base_dir.c_str());

		if(Result == false)
		{
			std::cerr << "Failed to load/parse .obj file: " << path << std::endl;
			std::cerr << warn << std::endl;
			std::cerr << err << std::endl;
			return false;
		}
	}

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

GLuint ResourceManager::LoadTexture2D(const std::string& filename, bool flipY)
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
#pragma endregion

#pragma region Title
bool ResourceManager::LoadTitleContext()
{
	Book.Parts.clear();

	std::wifstream ContextStream(TableOfContentsPath, std::ios::in);
	if(ContextStream.fail())
	{
		TableOfContentsPath = L"..\\..\\..\\3DComputerGraphicWithOpenGL\\Resource\\TableOfContents.txt";
		ContextStream.open(TableOfContentsPath, std::ios::in);
	}

	ContextStream.imbue(std::locale("en_US.UTF-8"));

	unsigned int PartIndex = 0;
	unsigned int ChapterIndex = 0;
	unsigned int SectionIndex = 0;
	unsigned int CodeIndex = 0;
	size_t StartPosition = 0;
	size_t EndPosition = 0;
	std::wstring NumberStr{};
	std::wstring Line{};
	std::wstring Prefix{};
	std::wstring Delimeter{ L": " };
	while (std::getline(ContextStream, Line))
	{
		
		if (Line.find(L"Part ") != -1)
		{
			Prefix = L"Part ";
			Delimeter = L": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::wstring::npos)
				continue;
			std::wstring PartTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::wstring::npos)
				break;
			
			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			PartIndex = std::stoi(NumberStr);
			if (Book.Parts.size() <= PartIndex)
			{
				Book.Parts.resize(PartIndex + 1);
			}
			
			Book.Parts[PartIndex] = FPart(PartTitle);
		}
		else if (Line.find(L"Chapter ") != -1)
		{
			Prefix = L"Chapter ";
			Delimeter = L": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::wstring::npos)
				break;
			std::wstring ChapterTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::wstring::npos)
				break;

			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			ChapterIndex = std::stoi(NumberStr);
			if (Book.Parts[PartIndex].Chapters.size() <= ChapterIndex)
			{
				Book.Parts[PartIndex].Chapters.resize(ChapterIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex] = FChapter(ChapterTitle);
		}
		else if (Line.find(L"Section ") != -1)
		{
			Prefix = L"Section ";
			Delimeter = L": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::wstring::npos)
				break;
			std::wstring SectionTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::wstring::npos)
				break;

			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			SectionIndex = std::stoi(NumberStr);

			if (Book.Parts[PartIndex].Chapters[ChapterIndex].Sections.size() <= SectionIndex)
			{
				Book.Parts[PartIndex].Chapters[ChapterIndex].Sections.resize(SectionIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex] = FSection(SectionTitle);
		}
		else if(Line.find(L"Code ") != -1)
		{
			Prefix = L"Code ";
			Delimeter = L": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::wstring::npos)
				break;
			std::wstring CodeTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::wstring::npos)
				break;

			std::wstring IntermediateStr = Line.substr(StartPosition, EndPosition - StartPosition);
			StartPosition = Line.find(L"-");
			if (StartPosition == std::wstring::npos)
				break;

			StartPosition += 1;
			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			CodeIndex = std::stoi(NumberStr);

			if (Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes.size() <= CodeIndex)
			{
				Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes.resize(CodeIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes[CodeIndex] = FExampleCode(CodeTitle);
 		}
	}
	ContextStream.close();

	if (Book.Parts.size() > 0)
		return true;

	return false;
}

FBook ResourceManager::GetBook() const
{
	return Book;
}

const std::wstring ResourceManager::FindTitleContext(unsigned int InPart, unsigned int InChapter,unsigned int InSection, unsigned int InCodeIndex)
{
	std::wifstream _ContextStream(TableOfContentsPath, std::ios::in);
	if (_ContextStream.fail())
	{
		TableOfContentsPath = L"..\\..\\..\\3DComputerGraphicWithOpenGL\\Resource\\TableOfContents.txt";
		_ContextStream.open(TableOfContentsPath, std::ios::in);
	}

	_ContextStream.imbue(std::locale("en_US.UTF-8"));

	std::wstring Line{};
	std::wstring Found{};
	std::wstring Keyword = std::format(L"Part {:02}", InPart);
	if (InPart != 0)
	{
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::wstring::npos)
			{
				Found = std::wstring(Line).substr(Position);
				break;
			}
		}
	}

	if (InChapter != 0)
	{
		Keyword = std::format(L"Chapter {:02}", InChapter);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::wstring::npos)
			{
				Found = std::wstring(Line).substr(Position);
				break;
			}
		}
	}

	if (InSection != 0)
	{
		Keyword = std::format(L"Section {:02}", InSection);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::wstring::npos)
			{
				Found = std::wstring(Line).substr(Position);
				break;
			}
		}
	}

	if (InCodeIndex != 0)
	{
		Keyword = std::format(L"Code {}-{}", InChapter, InCodeIndex);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::wstring::npos)
			{
				Found = std::wstring(Line).substr(Position);
				break;
			}
		}
	}

	return Found;
}
#pragma endregion

#pragma region Input & Description
bool ResourceManager::FindInputAndDescriptionContext(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex, std::wstring& OutInputContext, std::wstring& OutDescriptionContext)
{
	std::wstring InputAndDescriptionPath = InputAndDescriptionPathBase + std::format(L"_Part{}.txt", InPart);

	std::wifstream ContextStream(std::filesystem::path(InputAndDescriptionPath), std::ios::in);
	if (ContextStream.fail())
	{
		InputAndDescriptionPathBase =  L"..\\..\\..\\3DComputerGraphicWithOpenGL\\Resource\\InputAndDescription";
		InputAndDescriptionPath = InputAndDescriptionPathBase + std::format(L"_Part{}.txt", InPart);
		ContextStream.open(InputAndDescriptionPath, std::ios::in);
	}

	ContextStream.imbue(std::locale("en_US.UTF-8"));
	if (!ContextStream)
	{
		std::wcerr << std::format(L"failed to open {}\n", InputAndDescriptionPath);
		return {};
	}

	std::wstring Line{};
	std::wstring TargetCode = std::format(L"Code {}-{}", InChapter, InCodeIndex);
	std::wstring KeywordInput = L"Input:";
	std::wstring KeywordDescription = L"Description:";
	std::wregex Delimeter(LR"(Code \d+-\d+)");
	bool bFoundTarget = false;
	bool bFoundInput = false;
	bool bFoundDescription = false;
	while (std::getline(ContextStream, Line))
	{
		if (Line == TargetCode)
		{
			bFoundTarget = true;
		}

		if(!bFoundTarget)
			continue;

		if (!bFoundInput)
		{
			if (auto Position = Line.find(KeywordInput); Position != std::wstring::npos)
			{
				OutInputContext = std::wstring(Line).substr(Position + KeywordInput.length());
				bFoundInput = true;
				continue;
			}
		}
		else if (!bFoundDescription)
		{
			if (auto Position = Line.find(KeywordDescription); Position != std::wstring::npos)
			{
				OutDescriptionContext = std::wstring(Line).substr(Position + KeywordDescription.length());
				bFoundDescription = true;
				continue;
			}
		}
		else if (bFoundInput && bFoundDescription)
		{
			if (std::regex_match(std::wstring(Line.begin(), Line.end()), Delimeter))
			{
				break;
			}
		}

		if (bFoundInput && !bFoundDescription)
		{
			OutInputContext += OutInputContext.empty() ? Line : L"\n" + Line;
		}
		else if (bFoundInput && bFoundDescription)
		{
			OutDescriptionContext += OutDescriptionContext.empty() ? Line : L"\n" + Line;
		}
	}

	ContextStream.close();

	return !(OutInputContext.empty() && OutDescriptionContext.empty());
}
#pragma endregion

#pragma region Sound
std::wstring ResourceManager::GetSoundPath()
{
	if (std::filesystem::exists(SoundPath))
	{
		return SoundPath;
	}
	else 
	{
		SoundPath = L"..\\..\\..\\3DComputerGraphicWithOpenGL\\Resource\\Sound";
	}

	return SoundPath;
}
#pragma endregion