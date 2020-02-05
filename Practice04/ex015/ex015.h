#pragma once
#include <GL/freeglut.h>

#include <iostream>
#include <algorithm>
#include <time.h>
const int Size = 10;
const int WinX = 800;
const int WinY = 600;

enum class Object
{
	Cone,
	Cube,
	Sphere,
	Torus,
	Teapot
};
struct Point
{
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float radius;
	float scale;
	bool b_Draw;
	Point() {}
	Point(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z) {}
};
class CShape
{
private:
	Point point[Size];
	Object Obj[Size];
	float Angle;
	int Count;
public:
	void Initialize()
	{
		for (int i = 0; i < Size; ++i)
		{
			point[i] = Point(0, 0, 100);
			point[i].b_Draw = false;
			point[i].radius = 10.f;
			point[i].scale = 1.f;
		}
		Count = 0;
		Angle = 0;
	}
	void Mouse(int button, int state, int x, int y)
	{
		bool Lbutton = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
		if (Lbutton)
		{
			if (Count > Size - 1)
			{
				Count = 0;
			}
			point[Count].xPos = float(x);
			point[Count].yPos = float(y);
			point[Count].scale = 1.f;
			point[Count].b_Draw = true;
			point[Count].colR = float(rand() % 2);
			point[Count].colG = float(rand() % 2);
			point[Count].colB = float(rand() % 2);
			Obj[Count] = (Object)(rand() % 5);
			++Count;
		}
	}
	void Progress()
	{
		if (Angle > 360.f)
			Angle = 0.f;
		Angle += 0.5f;
		for (int i = 0; i < Size; ++i)
		{
			if (point[i].b_Draw)
			{
				if (point[i].scale < 20)
				{
					point[i].scale += 0.05f;
				}
				else
					point[i].b_Draw = false;
					
			}
		}
	}
	void Render()
	{
		for (int i = 0; i < Size; ++i)
		{
			if (point[i].b_Draw)
			{
				glPushMatrix();
				{
					glColor3f(point[i].colR + 0.5f, point[i].colG + 0.5f, point[i].colB + 0.1f);
					glTranslatef(point[i].xPos, point[i].yPos, point[i].zPos);
					glRotatef(-Angle, 0.f, 0.f, 1.f);
					glScalef(point[i].scale, point[i].scale, point[i].scale);

					if (Obj[i] == Object::Cone)
					{
						glRotatef(45, 1.f, 0.f, 0.f);
						glutWireCone(5, 15, 10, 10);
					}
					else if (Obj[i] == Object::Cube)
					{
						glRotatef(45, 1.f, 1.f, 0.f);
						glutWireCube(10);
					}
					else if(Obj[i]==Object::Sphere)
						glutWireSphere(20, 30, 30);
					else if (Obj[i] == Object::Torus)
					{
						glutWireTorus(10, 20, 30, 20);
					}
					else if (Obj[i] == Object::Teapot)
					{
						glutWireTeapot(10);
					}
				}
				glPopMatrix();
			}
		}
	}
public:
	CShape() = default;
	~CShape() = default;
};