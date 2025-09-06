// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"
#include "Windows/UTOutputWindow.h"
#include "format"
#include <regex>

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{

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
#pragma endregion

#pragma region Title
bool ResourceManager::LoadTitleContext()
{
	Book.Parts.clear();

	std::wifstream ContextStream(TableOfContentsPath, std::ios::in);
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
		if (PartIndex == 0)
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
		else if (ChapterIndex == 0)
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
		else if (SectionIndex == 0)
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
		else
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
			OutInputContext += L"\n" + Line;
		}
		else if (bFoundInput && bFoundDescription)
		{
			OutDescriptionContext += L"\n" + Line;
		}
		
	}

	ContextStream.close();

	return !(OutInputContext.empty() && OutDescriptionContext.empty());
}
#pragma endregion