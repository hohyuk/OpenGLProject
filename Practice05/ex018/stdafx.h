#pragma once
// OpenGL
#include <GL/freeglut.h>
//#include <GL/glut.h>

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