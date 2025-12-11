// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "InsideDynamicMath.h"

namespace InsideDynamicMath
{
	extern "C" double Add(double a, double b)
    {
        return a + b;
    }

	extern "C" double Subtract(double a, double b)
    {
        return a - b;
    }

	extern "C" double Multiply(double a, double b)
    {
        return a * b;
    }

	extern "C" double Divide(double a, double b)
    {
        return a / b;
    }

	__declspec(dllexport) std::wstring ReadFileToString(const std::filesystem::path& FilePath)
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

	__declspec(dllexport) std::wifstream OpenFileToWStream(std::wstring Path, const std::wstring SafePrefix, std::ios_base::openmode Mode)
	{
		std::wifstream Stream(Path, Mode);
		if(Stream.fail())
		{
			Path = SafePrefix + Path;
			Stream.open(Path, Mode);

			if(Stream.fail())
			{
				std::wcerr << std::format(L"failed to open {}\n", Path);
				return std::wifstream{};
			}
		}

		Stream.imbue(std::locale("en_US.UTF-8"));

		return Stream;
	}

	__declspec(dllexport) std::wstring LeftTrim(const std::wstring& Str, size_t& OutOffset)
	{
		size_t FirstNonSpace = Str.find_first_not_of(L" \t\n\r");
		OutOffset = FirstNonSpace;
		return (FirstNonSpace == std::wstring::npos) ? std::wstring() : Str.substr(FirstNonSpace);
	}

	__declspec(dllexport) std::wstring RightTrim(const std::wstring& Str, size_t& OutOffset)
	{
		size_t LastNonSpace = Str.find_last_not_of(L" \t\n\r");
		OutOffset = LastNonSpace;
		return (LastNonSpace == std::wstring::npos) ? std::wstring() : Str.substr(0, LastNonSpace + 1);
	}
}