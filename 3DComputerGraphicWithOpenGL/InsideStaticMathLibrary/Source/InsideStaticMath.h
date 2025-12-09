// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <array>
#include <string>
#include <windows.h>

namespace InsideStaticMath
{
	class Arithmetic
	{
	public:
		// Returns a + b
		static double Add(double a, double b);

		// Returns a - b
		static double Subtract(double a, double b);

		// Returns a * b
		static double Multiply(double a, double b);

		// Returns a / b
		static double Divide(double a, double b);
	};

	struct OrthoBounds
	{
		float _left, _right;
		float _bottom, _top;
		float _near, _far;
	};

	//|  2 / (r - l)     0               0              - (r + l) / (r - l) |
	//|  0               2 / (t - b)     0              - (t + b) / (t - b) |
	//|  0               0               - 2 / (f - n)  - (f + n) / (f - n) |
	//|  0               0               0                        1         |

	inline OrthoBounds GetOrthoBoundsFromProjectionMatrix(float Matrix[16])
	{
		// OpenGLÀº column-major ¹æ½Ä
		float a = Matrix[0];  // 2 / (r - l)
		float b = Matrix[12]; // -(r + l) / (r - l)

		float c = Matrix[5];  // 2 / (t - b)
		float d = Matrix[13]; // -(t + b) / (t - b)

		float e = Matrix[10]; // -2 / (f - n)
		float f = Matrix[14]; // -(f + n) / (f - n)

		OrthoBounds bounds;

		bounds._left = b / a - 1.f;
		bounds._right = b / a + 1.f;

		bounds._bottom = d / c - 1.f;
		bounds._top = d / c + 1.f;

		bounds._near = -(f / e + 1.f);
		bounds._far = -(f / e - 1.f);

		return bounds;
	}

	inline std::array<double, 2> CursorPosFromOrthoCoords(int Width, int Height, OrthoBounds OrthoBound, const std::array<double, 2>&CursorCoords)
	{
		double orthoX = CursorCoords[0] / (double)Width * (OrthoBound._right - OrthoBound._left) + OrthoBound._left;
		double orthoY = -CursorCoords[1] / (double)Height * (OrthoBound._top - OrthoBound._bottom) + OrthoBound._top;
		return { orthoX, orthoY };
	}

	inline std::string WStringToUtf8(const std::wstring& wstr)
	{
		if (wstr.empty())
			return {};

		int size_needed = WideCharToMultiByte(CP_UTF8, 0,
			wstr.data(), (int)wstr.size(),
			nullptr, 0, nullptr, nullptr);
		std::string strTo(size_needed, '\0');

		WideCharToMultiByte(CP_UTF8, 0,
			wstr.data(), (int)wstr.size(),
			&strTo[0], size_needed,
			nullptr, nullptr);
		return strTo;
	}
}