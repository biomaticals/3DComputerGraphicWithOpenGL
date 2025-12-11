// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#ifdef INSIDEDYNAMICMATHLIBRARY_EXPORTS
#define INSIDEDYNAMICMATHLIBRARY_API __declspec(dllexport)
#else
#define INSIDEDYNAMICMATHLIBRARY_API __declspec(dllimport)
#endif

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace InsideDynamicMath
{
	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Add(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Subtract(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Multiply(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Divide(double a, double b);

	INSIDEDYNAMICMATHLIBRARY_API std::wstring ReadFileToString(const std::filesystem::path& FilePath);
	INSIDEDYNAMICMATHLIBRARY_API std::wifstream OpenFileToWStream(std::wstring Path, const std::wstring SafePrefix, std::ios_base::openmode Mode);
	INSIDEDYNAMICMATHLIBRARY_API std::wstring LeftTrim(const std::wstring& Str, size_t& OutOffset);
	INSIDEDYNAMICMATHLIBRARY_API std::wstring RightTrim(const std::wstring& Str, size_t& OutOffset);
}