// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTOutputWindow.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#include "Common.h"

FExampleCode::FExampleCode()
	: Title(L"")
	, DrawFunction(nullptr)
{
}

FExampleCode::FExampleCode(const std::wstring& InTitle)
	: Title(InTitle)
	, DrawFunction(nullptr)
{
}

FExampleCode::FExampleCode(const std::wstring& InTitle, void (UTOutputWindow::* InDrawFunction)(), void (UTOutputWindow::* InStartDrawFunction)(), void(UTOutputWindow::* InEndDrawFunction)())
	: Title(InTitle)
	, DrawFunction(InDrawFunction)
	, StartDrawFunction(InStartDrawFunction)
	, EndDrawFunction(InEndDrawFunction)
{
}

FExampleCode::FExampleCode(const FExampleCode& Other)
{
	Title = Other.Title;
	DrawFunction = Other.DrawFunction;
	StartDrawFunction = Other.StartDrawFunction;
	EndDrawFunction = Other.EndDrawFunction;
}

FExampleCode::~FExampleCode()
{
	if (DrawFunction)
	{
		DrawFunction = nullptr;
	}

	if (StartDrawFunction)
	{
		StartDrawFunction = nullptr;
	}

	if (EndDrawFunction)
	{
		EndDrawFunction = nullptr;
	}
}

const FExampleCode& FExampleCode::operator=(const FExampleCode& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		DrawFunction = Other.DrawFunction;
		StartDrawFunction = Other.StartDrawFunction;
		EndDrawFunction = Other.EndDrawFunction;
	}
	return *this;
}

bool FExampleCode::IsValid() const
{
	return !Title.empty();
}

UTOutputWindow::UTOutputWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
	, DrawFunctions()
{
	Initialize();
}

UTOutputWindow::~UTOutputWindow()
{

}

void UTOutputWindow::Initialize()
{
	UTWindow::Initialize();

	DrawFunctions.clear();
	DrawFunctions.resize(6);
	DrawFunctions[5].resize(30);
	StartDrawFunctions.resize(6);
	StartDrawFunctions[5].resize(30);
	EndDrawFunctions.resize(6);
	EndDrawFunctions[5].resize(30);

	DrawFunctions[5][2] = &UTOutputWindow::Code_5_2;
	
	DrawFunctions[5][4] = &UTOutputWindow::Code_5_4;
	
	StartDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_Start;
	DrawFunctions[5][5] = &UTOutputWindow::Code_5_5;
	EndDrawFunctions[5][5] = &UTOutputWindow::Code_5_5_End;

	StartDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_Start;
	DrawFunctions[5][6] = &UTOutputWindow::Code_5_6;
	EndDrawFunctions[5][6] = &UTOutputWindow::Code_5_6_End;
}

void UTOutputWindow::RenderDrawData()
{
	if (OutputExampleCodeData.IsValid() && OutputExampleCodeData.DrawFunction)
	{
		(this->*OutputExampleCodeData.DrawFunction)();
	}
}

void UTOutputWindow::SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter,unsigned int InSection, unsigned int InCodeIndex)
{
	LastOutputExampleCodeData = OutputExampleCodeData;

	OutputExampleCodeData.Title = RESOURCE_MANAGER->FindTitleContext(InPart, InChapter, InSection,InCodeIndex).c_str();
	OutputExampleCodeData.DrawFunction = DrawFunctions[InChapter][InCodeIndex];
	
	if(StartDrawFunctions[InChapter][InCodeIndex])
		OutputExampleCodeData.StartDrawFunction = StartDrawFunctions[InChapter][InCodeIndex];
	
	if(EndDrawFunctions[InChapter][InCodeIndex])
		OutputExampleCodeData.EndDrawFunction = EndDrawFunctions[InChapter][InCodeIndex];

	if (LastOutputExampleCodeData.IsValid() && LastOutputExampleCodeData.EndDrawFunction)
		(this->*LastOutputExampleCodeData.EndDrawFunction)();

	if(OutputExampleCodeData.IsValid() && OutputExampleCodeData.StartDrawFunction)
		(this->*OutputExampleCodeData.StartDrawFunction)();

	glfwSetWindowShouldClose(GetGLFWWindow(), GLFW_FALSE);
}