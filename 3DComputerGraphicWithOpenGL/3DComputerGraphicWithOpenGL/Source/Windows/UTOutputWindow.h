// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "UTWindow.h"
#include <vector>

#define REGISTER_DRAW_FUNCTION(Chapter, CodeIndex) \
	{ \
		if (this->DrawFunctions.size() <= Chapter) \
		{ \
			this->DrawFunctions.resize(Chapter + 1); \
		} \
		if (this->DrawFunctions[Chapter].size() <= CodeIndex) \
		{ \
			this->DrawFunctions[Chapter].resize(CodeIndex + 1); \
		} \
		(this->DrawFunctions)[Chapter][CodeIndex] = &UTOutputWindow::MyDisplay_##Chapter##_##CodeIndex; \
	} \

class UTOutputWindow;

struct FExampleCode
{
	FExampleCode();
	FExampleCode(const std::wstring& InTitle);
	FExampleCode(const std::wstring& InTitle, void (UTOutputWindow::* InDrawFunction)(), void (UTOutputWindow::* InStartDrawFunction)(), void(UTOutputWindow::* InEndDrawFunction)());
	FExampleCode(const FExampleCode& Other);
	~FExampleCode();
	const FExampleCode& operator=(const FExampleCode& Other);
	bool IsValid() const;

	std::wstring Title;
	void (UTOutputWindow::* DrawFunction)() = nullptr;
	void (UTOutputWindow::* StartDrawFunction)() = nullptr;
	void (UTOutputWindow::* EndDrawFunction)() = nullptr;
};

class UTOutputWindow : public UTWindow
{
public:
	UTOutputWindow(const std::string& Title, int Width, int Height);
	virtual ~UTOutputWindow() override;
	void Initialize() override;
	virtual void RenderDrawData() override;

public:
	void SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);

private:
	void Code_5_2();

	void Code_5_4();

	void Code_5_5_Start();
	void Code_5_5();
	void Code_5_5_End();
	void Code_5_5_Reshape(GLFWwindow* Window, int NewWidth, int NewHeight);


private:
	using DrawFuncPtr = void (UTOutputWindow::*)();
	std::vector<std::vector<DrawFuncPtr>> DrawFunctions;

	std::vector<std::vector<DrawFuncPtr>> StartDrawFunctions;
	std::vector<std::vector<DrawFuncPtr>> EndDrawFunctions;

public:
	FExampleCode OutputExampleCodeData;
	FExampleCode LastOutputExampleCodeData;
};