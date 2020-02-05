#pragma once
// OpenGL
#include <GL/freeglut.h>

// C++
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;
const int WinX = 800;
const int WinY = 600;

struct Point
{
	float xPos, yPos, zPos;
	float colR, colG, colB;
	Point() {}
	Point(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z) {}
};

class Vector3
{
public:
	float xPos, yPos, zPos;
};
inline Vector3 Picking(int x, int y)
{
	double pickPos[3];
	GLdouble proj[16];
	GLdouble model[16];
	GLint viewport[4];

	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLfloat z;
	auto winX = static_cast<GLfloat>(x);
	auto winY = static_cast<GLfloat>(viewport[3] - y);

	//GL_DEPTH_COMPONENT 값에서 glReadPixels을 얻는다.
	glReadPixels(x, static_cast<int>(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

	auto result = gluUnProject(winX, winY, z
		, model, proj, viewport
		, &pickPos[0], &pickPos[1], &pickPos[2]);

	if (GLU_FALSE == result)
		printf("Error!\n");

	return Vector3{ static_cast<float>(pickPos[0]),static_cast<float>(pickPos[1]),static_cast<float>(pickPos[2]) };
}