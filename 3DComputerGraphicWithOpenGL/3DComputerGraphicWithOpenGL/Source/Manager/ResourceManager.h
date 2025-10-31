// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "Common.h"
#include "CoreMinimal.h"
#include <fstream>
#include <list>
#include <filesystem>

#define RESOURCE_MANAGER ResourceManager::GetResourceManager()

class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();

public:
	static ResourceManager* GetResourceManager();
	static void Destroy();
	
private:
	static ResourceManager* Instance;
	std::wstring ProgramBasePath;
	std::wstring Modified;

public:
	void Update();

#pragma region Load & Unload
public:
	bool LoadResources();
	void UnloadResources();	
#pragma endregion

#pragma region Title
public:
	bool LoadTitleContext();
	FBook GetBook() const;

	const std::wstring FindTitleContext(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);
	
private:
	FBook Book;
	std::wstring TableOfContentsPath = L"Resource\\TableOfContents.txt";
#pragma endregion

#pragma region Input & Description
public:
	bool FindInputAndDescriptionContext(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex, std::wstring& OutInputContext, std::wstring& OutDescriptionContext);

private:
	std::wstring InputAndDescriptionPathBase = L"Resource\\InputAndDescription";
#pragma endregion

#pragma region Sound
public:
	std::wstring GetSoundPath();

private:
	std::wstring SoundPath = L"Resource\\Sound";
#pragma 
};