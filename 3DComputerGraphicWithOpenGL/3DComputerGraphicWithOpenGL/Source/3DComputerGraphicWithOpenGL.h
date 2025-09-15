// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <windows.h>
#include "CoreMinimal.h"
#include "Common.h"
#include <string>
#include "Windows/UTMainWindow.h"
#include "Windows/UTOutputWindow.h"

void UpdateManager();

int main(int, char**);
static void glfw_error_callback(int error, const char* description);

inline std::string WStringToUtf8(const std::wstring& wstr) 
{
	if (wstr.empty()) 
	return {};
	
	int size_needed = WideCharToMultiByte(CP_UTF8, 0,
		wstr.data(), (int)wstr.size(),
		nullptr, 0, nullptr, nullptr);
	std::string strTo(size_needed, 0);
	
	WideCharToMultiByte(CP_UTF8, 0,
		wstr.data(), (int)wstr.size(),
		strTo.data(), size_needed,
		nullptr, nullptr);
	return strTo;
}