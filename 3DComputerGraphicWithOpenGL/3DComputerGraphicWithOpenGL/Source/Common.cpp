// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Common.h"
#include "Windows/UTOutputWindow.h"

FSection::FSection()
	: Title(L"")
{
}

FSection::FSection(const std::wstring& InTitle)
	: Title(InTitle)
{
}

const FSection& FSection::operator=(const FSection& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		ExampleCodes = Other.ExampleCodes;
	}
	return *this;
}

bool FSection::IsValid() const
{
	return !Title.empty();
}

FChapter::FChapter()
	: Title(L"")
{
}

FChapter::FChapter(const std::wstring& InTitle)
	: Title(InTitle)
{
}

const FChapter& FChapter::operator=(const FChapter& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Sections = Other.Sections;
	}
	return *this;
}

bool FChapter::IsValid() const
{
	return !Title.empty();
}

FPart::FPart()
	: Title(L"")
{
}

FPart::FPart(const std::wstring& InTitle)
	: Title(InTitle)
{
}

const FPart& FPart::operator=(const FPart& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Chapters = Other.Chapters;
	}
	return *this;
}

bool FPart::IsValid() const
{
	return !Title.empty();
}

FBook::FBook()
{
}