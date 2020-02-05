#pragma once

const int WinX = 800;
const int WinY = 600;
const float SPACE = 100.f;
const float PI{ 3.141592f };
struct Point
{
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float xSpeed, ySpeed, zSpeed;
	float xDir, yDir, zDir;

	Point() {}
	Point(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z) {}
};

