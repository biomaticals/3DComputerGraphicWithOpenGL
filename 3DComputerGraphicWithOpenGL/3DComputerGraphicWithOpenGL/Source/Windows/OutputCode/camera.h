// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <windows.h>
#include <strstream>
#include <math.h>

class Point3
{
public:
	Point3()
	{
		x = y = z = 0;
	}

	Point3(float xx, float yy, float zz)
	{
		x = xx; y = yy; z = zz;
	}

	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}

public:
	float x, y, z;
};

class Vector3
{
public:
	Vector3()
	{
		x = y = z = 0.0;
	}

	Vector3(float xx, float yy, float zz)
	{
		x = xx; y = yy; z = zz;
	}

	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

	void set(const Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	void flip()
	{
		x = -x; y = -y; z = -z;
	}

	void setDiff(Point3& a, Point3& b)
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}

	void normalize();
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);

public:
	float x, y, z;
};

class Camera
{
public:
	Camera(void);

	void setModelViewMatrix();
	void set(Point3 Eye, Point3 look, Vector3 up);
	void set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ);
	void setShape(float viewAngle, float aspect, float Near, float Far);
	void setAspect(float asp);
	void getShape(float& viewAngle, float& aspect, float& Near, float& Far);
	void rotAxes(Vector3& a, Vector3& b, float angle);
	void setDefaultCamera();
	
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void slide(double du, double dv, double dn);

public:
	Point3 eye;
	Vector3 u, v, n;
	float aspect, nearDist, farDist, viewAngle;
};
