// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "camera.h"
#include <GL/freeglut_std.h>
#include "Manager/WindowManager.h"

Camera::Camera(void)
{
	setDefaultCamera();
}

void Camera::setDefaultCamera(void)
{
	setShape(45.0f, 640 / (float)480, 0.1f, 200.0f);
	Point3 eyePoint = Point3(10.0, 0.0, 0.0);
	Point3 lookPoint = Point3(0.0, 0.0, 0.0); 
	Vector3 upVector = Vector3(0, 1, 0); 
	set(eyePoint, lookPoint, upVector);
}

void Camera::set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ)
{
	Point3 Eye = Point3(eyeX, eyeY, eyeZ); 
	Point3 look = Point3(lookX, lookY, lookZ);
	Vector3 up = Vector3(upX, upY, upZ);
	eye.set(Eye);
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);//시점과 카메라좌표를 빼서 시축(optical axis)구성
	u.set(up.cross(n)); // 카메라 업벡터와의 내적으로 u구성
	v.set(n.cross(u)); // u와 n의 내적으로 시점좌표계의 y축
	u.normalize(); v.normalize(); n.normalize();// 세 시점좌표계 축들을 정규화 이로써 카메라 시공간의 정규직교기저가 완성됨
	setModelViewMatrix();
}

void Camera::set(Point3 Eye, Point3 look, Vector3 up) 
{ 
	eye.set(Eye);
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	u.set(up.cross(n));
	v.set(n.cross(u));
	u.normalize(); v.normalize(); n.normalize();
	setModelViewMatrix();
}

void Camera::setModelViewMatrix(void) 
{
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	float m[16];// 
	Vector3 eVec(eye.x, eye.y, eye.z);
	m[0] = u.x;	m[4] = u.y;	m[8] = u.z;	m[12] = -eVec.dot(u);
	m[1] = v.x;	m[5] = v.y;	m[9] = v.z;	m[13] = -eVec.dot(v);
	m[2] = n.x;	m[6] = n.y;	m[10] = n.z;	m[14] = -eVec.dot(n);
	m[3] = 0;		m[7] = 0;		m[11] = 0;	m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::setShape(float vAngle, float asp, float nr, float fr)
{	
	glfwMakeContextCurrent(OUTPUT_WINDOW->GetGLFWWindow());
	viewAngle = vAngle;
	aspect = asp;
	nearDist = nr;
	farDist = fr;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setAspect(float asp)
{
	aspect = asp;
}

void Camera::getShape(float& vAngle, float& asp, float& nr, float& fr) 
{
	vAngle = viewAngle;
	asp = aspect;
	nr = nearDist;
	fr = farDist;
}

void Camera::slide(double du, double dv, double dn) 
{
	eye.x += du * u.x + dv * v.x + dn * n.x;//시점좌표축의 정규직교기저에 이동변환행렬을 곱한다 변환된 결과를 모델뷰행렬에 적용
	eye.y += du * u.y + dv * v.y + dn * n.y;//시점좌표계가 이동한 효과 // Emmanuel Agu자료15페이지 참고
	eye.z += du * u.z + dv * v.z + dn * n.z;
	setModelViewMatrix();
}

void Camera::rotAxes(Vector3& a, Vector3& b, float angle) 
{ 
	//시점좌표계를 이루는 기저를 기울여 회전변환// Emmanuel Agu자료 21페이지 참고
	float ang = 3.14159265 / 180 * angle;//각을 라디안단위로 변환한다. cos, sin 함수를 이용하기 위해서
	float C = cos(ang), S = sin(ang); // 변환하려는 각의 cos, sin 값 구함
	Vector3 t(C * a.x + S * b.x, C * a.y + S * b.y, C * a.z + S * b.z); b.set(-S * a.x + C * b.x, -S * a.y + C * b.y, -S * a.z + C * b.z);// 이를 이용해 두 축을 angle만큼 회전한다
	a.set(t.x, t.y, t.z);
}

void Camera::roll(float angle)
{
	rotAxes(u, v, angle);//n축중심의 회전 나머지 u,v축이 angle각도만큼 회전한다
	setModelViewMatrix();
}

void Camera::pitch(float angle)
{
	rotAxes(n, v, angle);//u축중심의 회전 나머지 n,v축이 angle각도만큼 회전한다
	setModelViewMatrix();
}

void Camera::yaw(float angle)
{
	rotAxes(u, n, angle);//v축중심의 회전 나머지 u,n축이 angle각도만큼 회전한다
	setModelViewMatrix();
}

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}

float Vector3::dot(Vector3 b) 
{ 
	return x * b.x + y * b.y + z * b.z;
}

void Vector3::normalize() 
{
	double sizeSq = x * x + y * y + z * z;
	if (sizeSq < 0.0000001) 
	{
		return;
	}
	float scaleFactor = 1.0 / (float)sqrt(sizeSq);
	x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
}