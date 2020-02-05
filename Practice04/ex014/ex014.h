#pragma once
#include <GL/freeglut.h>

#include <iostream>
#include <algorithm>

const int WinX = 800;
const int WinY = 600;

struct Point
{
	float xPos;
	float yPos;
	float zPos;
	Point() {}
	Point(float x, float y, float z)
		:xPos(x), yPos(y), zPos(z)
	{}
};

class CShape
{
private:
	Point ptXY[3], ptYZ[3];		// »ï°¢Çü ¸¸µé±â. xyÆò¸é »ï°¢Çü, yzÆò¸é »ï°¢Çü.
	Point pointXY, pointYZ;
	float AngleY;
	float MiniAngleY;
	bool b_Angle;
	bool b_MiniT;				// ÀÛÀº »ï°¢Çü ¿òÁ÷ÀÓ.
	bool b_MiniR;				// ÀÛÀº »ï°¢Çü Rotate.
	float f_moveX, f_moveY, f_moveZ;
	int Count;
public:
	void Initialize()
	{
		// xyÆò¸é »ï°¢Çü ¸¸µé±â.
		ptXY[0] = Point(-200, 200, 0);
		ptXY[1] = Point(0, -200, 0);
		ptXY[2] = Point(200, 200, 0);
		// yzÆò¸é »ï°¢Çü ¸¸µé±â.
		ptYZ[0] = Point(-200, 200, 0);
		ptYZ[1] = Point(0, -200, 0);
		ptYZ[2] = Point(200, 200, 0);

		// ÀÛÀº »ï°¢Çü.
		pointXY = ptXY[0];
		pointYZ = ptYZ[0];
		b_Angle = false;
		b_MiniT = false;
		b_MiniR = false;
		AngleY = 0;
		MiniAngleY = 0;
		Count = 0;
	}
	void TranslateTrangle(float& x, float& y, Point* pt, const int Size = 3)
	{
		if (Count < Size - 1)
		{
			if (pt[Count].xPos < pt[Count + 1].xPos)
				f_moveX = 0.5f;
			else
				f_moveX = -0.5f;

			float fWidth = pt[Count + 1].xPos - pt[Count].xPos;
			float fHeight = pt[Count + 1].yPos - pt[Count].yPos;

			f_moveY = (fHeight / fWidth)*(x - pt[Count].xPos) + pt[Count].yPos;
			bool b_distance = pt[Count].yPos > pt[Count + 1].yPos;
			if (b_distance)
			{
				if (f_moveY < pt[Count + 1].yPos)
					++Count;
			}
			else
			{
				if (f_moveY > pt[Count + 1].yPos)
					++Count;
			}
		}
		else
		{
			if (pt[0].xPos < pt[Count].xPos)
				f_moveX = -0.5f;
			else
				f_moveX = 0.5f;
			float fWidth = pt[Count].xPos - pt[0].xPos;
			float fHeight = pt[Count].yPos - pt[0].yPos;
			if (fHeight / fWidth == 0 && x<pt[0].xPos)
			{
				f_moveY = pt[0].yPos;
				Count = 0;
			}
			else
			{
				f_moveY = (fHeight / fWidth)*(x - pt[Count].xPos) + pt[Count].yPos;
				bool b_distance = pt[0].yPos < pt[Count].yPos;

				if (b_distance)
				{
					if (f_moveY < pt[0].yPos)
						Count = 0;
				}
				else
				{
					if (f_moveY > pt[0].yPos)
						Count = 0;
				}
			}

		}
		x += f_moveX;
		y = f_moveY;
	}
	void Progress()
	{
		if (b_Angle)
		{
			if (AngleY > 360.f)
				AngleY = 0.f;
			AngleY += 0.5f;
		}
		if (b_MiniR)
		{
			if (MiniAngleY > 360.f)
				MiniAngleY = 0.f;
			MiniAngleY += 1.f;
		}
		if (b_MiniT)
		{
			// xyÆò¸é ÀÛÀº »ï°¢Çü.
			TranslateTrangle(pointXY.xPos, pointXY.yPos, ptXY);
			// yzÆò¸é ÀÛÀº »ï°¢Çü.
			TranslateTrangle(pointYZ.xPos, pointYZ.yPos, ptYZ);
		}

	}
	void Render()
	{
		glPushMatrix();
		{
			glTranslated(WinX / 2, WinY / 2, 0);
			glRotatef(AngleY, 0.f, 1.f, 0.f);
			glColor3f(0.f, 1.f, 0.f);

			// xyÆò¸é
			glBegin(GL_LINE_LOOP);
			{
				for (int i = 0; i < 3; ++i)
					glVertex3f(ptXY[i].xPos, ptXY[i].yPos, ptXY[i].zPos);
			}
			glEnd();
			// yzÆò¸é
			glBegin(GL_LINE_LOOP);
			{
				for (int i = 0; i < 3; ++i)
					glVertex3f(ptYZ[i].zPos, ptYZ[i].yPos, ptYZ[i].xPos);
			}
			glEnd();

			// xyÆò¸é in »ï°¢Çü
			glPushMatrix();
			{
				glColor3f(1.f, 0.5f, 0.5f);
				glTranslated(pointXY.xPos, pointXY.yPos, pointXY.zPos);
				glRotatef(MiniAngleY, 0.f, 1.f, 0.f);
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(-15.f, 15.f, 0.f);
					glVertex3f(0.f, -15.f, 0.f);
					glVertex3f(15.f, 15.f, 0.f);
				}
				glEnd();
			}
			glPopMatrix();
			// yzÆò¸é in »ï°¢Çü
			glPushMatrix();
			{
				glColor3f(1.f, 0.5f, 0.5f);
				glTranslated(pointYZ.zPos, pointYZ.yPos, pointYZ.xPos);
				glRotatef(MiniAngleY, 0.f, 1.f, 0.f);
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(0.f, 15.f, -15.f);
					glVertex3f(0.f, -15.f, 0.f);
					glVertex3f(0.f, 15.f, 15.f);
				}
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'q':			// Rotate
			b_Angle = !b_Angle;
			break;
		case 'w':
			b_MiniT = !b_MiniT;
			break;
		case 'e':
			b_MiniR = !b_MiniR;
			break;
		case 'r':			// Reset
			Initialize();
			break;
		}
	}
public:
	CShape() = default;
	~CShape() = default;
};