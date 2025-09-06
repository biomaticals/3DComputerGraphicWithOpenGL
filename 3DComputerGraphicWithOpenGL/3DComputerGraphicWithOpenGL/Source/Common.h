// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>

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

extern std::wstring ReadFileToString(const std::filesystem::path& FilePath);
extern std::wstring LeftTrim(const std::wstring& Str, size_t& OutOffset);
extern std::wstring RightTrim(const std::wstring& Str, size_t& OutOffset);