// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "InsideDynamicMath.h"

namespace InsideDynamicMath
{
    double Add(double a, double b)
    {
        return a + b;
    }

    double Subtract(double a, double b)
    {
        return a - b;
    }

    double Multiply(double a, double b)
    {
        return a * b;
    }

    double Divide(double a, double b)
    {
        return a / b;
    }

	std::wstring ReadFileToString(const std::filesystem::path& FilePath)
	{
		std::ifstream Stream(FilePath, std::ios::in | std::ios::binary);
		if (!Stream)
		{
			std::cerr << std::format("failed to open {}\n", FilePath.string());
			return {};
		}

		std::wstring Contents((std::istreambuf_iterator<char>(Stream)), std::istreambuf_iterator<char>());
		return Contents;
	}

	std::wstring LeftTrim(const std::wstring& Str, size_t& OutOffset)
	{
		size_t FirstNonSpace = Str.find_first_not_of(L" \t\n\r");
		OutOffset = FirstNonSpace;
		return (FirstNonSpace == std::wstring::npos) ? std::wstring() : Str.substr(FirstNonSpace);
	}

	std::wstring RightTrim(const std::wstring& Str, size_t& OutOffset)
	{
		size_t LastNonSpace = Str.find_last_not_of(L" \t\n\r");
		OutOffset = LastNonSpace;
		return (LastNonSpace == std::wstring::npos) ? std::wstring() : Str.substr(0, LastNonSpace + 1);
	}
}