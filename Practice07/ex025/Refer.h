#pragma once

const int WinX = 800;
const int WinY = 600;
const float PI{ 3.141592f };
struct Point
{
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float xMove, yMove, zMove;
	Point() {}
	Point(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z) {}
};

struct Cube
{
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float xMove, yMove, zMove;
	float Size;
	Cube() {}
	Cube(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z) {}
};