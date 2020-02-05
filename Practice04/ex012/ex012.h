#pragma once
#include <GL/freeglut.h>
#include <iostream>

#define SIZE 5
const float PI{ 3.141592f };

enum class Course
{
	Circle,
	Sine,
	Spring,
	Tornado,
	Zigzag,
	Course_Draw,
	
};
struct Point
{
	float xPos;
	float yPos;
	bool Draw;
};
class CShape
{
private:
	Point point;
	Point pt[SIZE];
	Course course{Course::Circle};
	float width, height;
	float f_Scale;
	float f_Rotate;
	float vary;		// 모형 변화
	float Angle;
	float f_movex, f_movey;	// 도형 움직임 값 정하기
	float moveX, moveY;
	bool b_Draw;	// true = cube false = trangle
	bool b_Translate;
	bool b_Scale;
	bool b_Rotate;
	bool b_Direction;
	int Count;
	int MouseCount;
public:
	void Initialize(const int width_,const int height_)
	{
		width = (float)width_;
		height = (float)height_;
		point.xPos = 0;
		point.yPos = 0;
		f_Scale = 1.f;
		f_Rotate = 0.f;
		vary = 0.05f;
		Angle = 0.f;
		f_movex = 0.5f;
		f_movey = 0.5f;
		b_Draw = true;
		b_Translate = false;
		b_Scale = false;
		b_Rotate = false;
		Count = 0;
		MouseCount = 0;
		b_Direction = true;	// 방향
		point.Draw = false;	// 오른쪽 마우스 클릭 후 도형 생성
		for (int i = 0; i < SIZE; ++i)
		{
			pt[i].xPos = -400.f + (float)(i * 200);
			if (i % 2 == 0)
				pt[i].yPos = 100;
			else
				pt[i].yPos = -100;
			pt[i].Draw = false;
		}
	}
	void CourseTranslate()
	{
		if (b_Translate)
		{
			if (course == Course::Circle)
			{
				if (Angle > 360)
					Angle = 0.f;
				Angle += f_movex;
			}
			else if (course == Course::Sine)
			{
				if (Angle > 360)
					f_movex = -0.5f;
				else if (Angle < -360)
					f_movex = 0.5f;
				Angle += f_movex;
			}
			else if (course == Course::Spring)
			{
				if (Angle > 275)
					f_movex = -0.5f;
				else if (Angle < -335)
					f_movex = 0.5f;
				Angle += f_movex;
			}
			else if (course == Course::Tornado)
			{
				if (Angle > 360)
					f_movex = -0.5f;
				else if (Angle < 0)
					f_movex = 0.5f;
				Angle += f_movex;
			}
			else if (course == Course::Zigzag)
			{
				if (b_Direction)
				{
					if (Count >= SIZE-1)
						b_Direction = false;

					f_movex = 0.5f;
					float fWidth = pt[Count + 1].xPos - pt[Count].xPos;
					float fHeight = pt[Count + 1].yPos - pt[Count].yPos;

					f_movey = (fHeight / fWidth)*(moveX - pt[Count].xPos) + pt[Count].yPos;
					if ((Count + 1) % 2 == 0)
					{
						if (f_movey > pt[Count + 1].yPos)
							++Count;
					}
					else
					{
						if (f_movey < pt[Count + 1].yPos)
							++Count;
					}
				}
				else
				{
					if (Count <= 0)
						b_Direction = true;

					f_movex = -0.5f;
					float fWidth = pt[Count - 1].xPos - pt[Count].xPos;
					float fHeight = pt[Count - 1].yPos - pt[Count].yPos;

					f_movey = (fHeight / fWidth)*(moveX - pt[Count].xPos) + pt[Count].yPos;
					if ((Count - 1) % 2 == 0)
					{
						if (f_movey > pt[Count - 1].yPos)
							--Count;
					}
					else
					{
						if (f_movey < pt[Count - 1].yPos)
							--Count;
					}
				}
				moveX += f_movex;
				moveY = f_movey;
			}
			else if (course == Course::Course_Draw)
			{
				int DrawCount = 0;
				for (int i = 0; i < SIZE; ++i)
				{
					if (pt[i].Draw)
						++DrawCount;
				}
				if (b_Direction)
				{
					if (Count >= DrawCount - 1)
						b_Direction = false;
					// x1이 x2보다 작을때 증가값.
					if (pt[Count].xPos < pt[Count + 1].xPos)
						f_movex = 0.5f;
					else
						f_movex = -0.5f;
					// 직선의 방정식을 구한다.
					float fWidth = pt[Count + 1].xPos - pt[Count].xPos;
					float fHeight = pt[Count + 1].yPos - pt[Count].yPos;
					bool flag = pt[Count].yPos < pt[Count + 1].yPos;
					
					f_movey = (fHeight / fWidth)*(moveX - pt[Count].xPos) + pt[Count].yPos;
					if (flag)
					{
						if (f_movey > pt[Count + 1].yPos)
							++Count;
					}
					else
					{
						if (f_movey < pt[Count + 1].yPos)
							++Count;
					}
				}
				else
				{
					if (Count < 1)
						b_Direction = true;
					// x2이 x1보다 작을때 증가값.
					if (pt[Count].xPos < pt[Count - 1].xPos)
						f_movex = 0.5f;
					else
						f_movex = -0.5f;
					// 직선의 방정식을 구한다.
					float fWidth = pt[Count - 1].xPos - pt[Count].xPos;
					float fHeight = pt[Count - 1].yPos - pt[Count].yPos;
					bool flag = pt[Count].yPos < pt[Count - 1].yPos;

					f_movey = (fHeight / fWidth)*(moveX - pt[Count].xPos) + pt[Count].yPos;
					if (flag)
					{
						if (f_movey > pt[Count - 1].yPos)
							--Count;
					}
					else
					{
						if (f_movey < pt[Count - 1].yPos)
							--Count;
					}
				}

				moveX += f_movex;
				moveY = f_movey;
			}
		}
		
	}
	void Progress()
	{
		if (b_Scale)
		{
			if (f_Scale > 5)
				vary = -0.05f;
			else if (f_Scale < 1)
				vary = 0.05f;
			f_Scale += vary;
		}
		if (b_Rotate)
		{
			if (f_Rotate > 360)
				f_Rotate = 0.f;
			f_Rotate += 0.5f;
		}
		CourseTranslate();
	}
	void Render()
	{
		glTranslatef(width / 2.f, height / 2.f, 0.f);
		if (course == Course::Circle)
		{
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = 0; i < 61; ++i)
					{
						point.xPos = 200 * cosf(i*PI / 30.f);
						point.yPos = 200 * -sin(i*PI / 30.f);
						glVertex3f(point.xPos, point.yPos, 0.f);
					}
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				point.xPos = 200 * cosf(Angle*PI / 180.f);
				point.yPos = 200 * -sinf(Angle*PI / 180.f);

				glTranslatef(point.xPos, point.yPos, 0.f);
				glRotatef(f_Rotate, 0.f, 0.f, 1.f);
				glScalef(f_Scale, f_Scale, 1.f);
				if (b_Draw)
					glutSolidCube(10);
				else
				{
					glBegin(GL_TRIANGLES);
					{
						glVertex3f(-5.f, 5.f, 0.f);
						glVertex3f(0.f, -5.f, 0.f);
						glVertex3f(5.f, 5.f, 0.f);
					}
					glEnd();
				}
			}
			glPopMatrix();
		}
		else if (course == Course::Sine)
		{
			// Sin
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = -360; i < 361; ++i)
					{
						point.xPos = (float)i;
						point.yPos = 200 * -sinf(i*PI / 180.f);
						glVertex3f(point.xPos, point.yPos, 0.f);
					}
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				point.xPos = Angle;
				point.yPos = 200 * -sinf(Angle*PI / 180.f);

				glTranslatef(point.xPos, point.yPos, 0.f);
				glRotatef(f_Rotate, 0.f, 0.f, 1.f);
				glScalef(f_Scale, f_Scale, 1.f);
				if (b_Draw)
					glutSolidCube(10);
				else
				{
					glBegin(GL_TRIANGLES);
					{
						glVertex3f(-5.f, 5.f, 0.f);
						glVertex3f(0.f, -5.f, 0.f);
						glVertex3f(5.f, 5.f, 0.f);
					}
					glEnd();
				}

			}
			glPopMatrix();
		}
		else if (course == Course::Spring)
		{
			// Spring
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = -335; i < 276; ++i)
					{
						point.xPos = (float)i + 150 * -cosf(i*PI / 60.f);
						point.yPos = 150 * sinf(i*PI / 60.f);
						glVertex3f(point.xPos, point.yPos, 0.f);
					}
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				point.xPos = Angle + 150 * -cosf(Angle*PI / 60.f);
				point.yPos = 150 * sinf(Angle*PI / 60.f);

				glTranslatef(point.xPos, point.yPos, 0.f);
				glRotatef(f_Rotate, 0.f, 0.f, 1.f);
				glScalef(f_Scale, f_Scale, 1.f);
				if (b_Draw)
					glutSolidCube(10);
				else
				{
					glBegin(GL_TRIANGLES);
					{
						glVertex3f(-5.f, 5.f, 0.f);
						glVertex3f(0.f, -5.f, 0.f);
						glVertex3f(5.f, 5.f, 0.f);
					}
					glEnd();
				}

			}
			glPopMatrix();
		}
		else if (course == Course::Tornado)
		{
			// Tornado
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = 0; i < 361; ++i)
					{
						point.xPos = i* -cosf(i*PI / 60.f);
						point.yPos = i * sinf(i*PI / 60.f);
						glVertex3f(point.xPos, point.yPos, 0.f);
					}
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				point.xPos = Angle * -cosf(Angle*PI / 60.f);
				point.yPos = Angle * sinf(Angle*PI / 60.f);

				glTranslatef(point.xPos, point.yPos, 0.f);
				glRotatef(f_Rotate, 0.f, 0.f, 1.f);
				glScalef(f_Scale, f_Scale, 1.f);
				if (b_Draw)
					glutSolidCube(10);
				else
				{
					glBegin(GL_TRIANGLES);
					{
						glVertex3f(-5.f, 5.f, 0.f);
						glVertex3f(0.f, -5.f, 0.f);
						glVertex3f(5.f, 5.f, 0.f);
					}
					glEnd();
				}

			}
			glPopMatrix();
		}
		else if (course == Course::Zigzag)
		{
			// Zigzag
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = 0; i < 5; ++i)
						glVertex3f(pt[i].xPos, pt[i].yPos, 0.f);
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				point.xPos = moveX;
				point.yPos = moveY;

				glTranslatef(point.xPos, point.yPos, 0.f);
				glRotatef(f_Rotate, 0.f, 0.f, 1.f);
				glScalef(f_Scale, f_Scale, 1.f);
				if (b_Draw)
					glutSolidCube(10);
				else
				{
					glBegin(GL_TRIANGLES);
					{
						glVertex3f(-5.f, 5.f, 0.f);
						glVertex3f(0.f, -5.f, 0.f);
						glVertex3f(5.f, 5.f, 0.f);
					}
					glEnd();
				}

			}
			glPopMatrix();
		}
		else if (course == Course::Course_Draw)
		{
			//Free_Draw
			glLoadIdentity();
			glPushMatrix();
			{
				glColor3f(0.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				{
					for (int i = 0; i < 5; ++i)
					{
						if (pt[i].Draw)
							glVertex3f(pt[i].xPos, pt[i].yPos, 0.f);
					}
				}
				glEnd();

				glColor3f(1.f, 1.f, 0.f);
				if (point.Draw)
				{
					point.xPos = moveX;
					point.yPos = moveY;

					glTranslatef(point.xPos, point.yPos, 0.f);
					glRotatef(f_Rotate, 0.f, 0.f, 1.f);
					glScalef(f_Scale, f_Scale, 1.f);
					if (b_Draw)
						glutSolidCube(10);
					else
					{
						glBegin(GL_TRIANGLES);
						{
							glVertex3f(-5.f, 5.f, 0.f);
							glVertex3f(0.f, -5.f, 0.f);
							glVertex3f(5.f, 5.f, 0.f);
						}
						glEnd();
					}
				}
			}
			glPopMatrix();
		}
	}
	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		// 삼각형 사각형 선택하기.
		case 'q':
			b_Draw = !b_Draw;
			break;
		case 'a':
			b_Scale = !b_Scale;
			break;
		case 's':
			b_Rotate = !b_Rotate;
			break;
		case 'd':
			b_Translate = !b_Translate;
			break;
		case '1':
			course = Course::Circle;
			Initialize((const int)width, (const int)height);
			break;
		case '2':
			course = Course::Sine;
			Initialize((const int)width, (const int)height);
			break;
		case '3':
			course = Course::Spring;
			Initialize((const int)width, (const int)height);
			break;
		case '4':
			course = Course::Tornado;
			Initialize((const int)width, (const int)height);
			break;
		case '5':
			course = Course::Zigzag;
			Initialize((const int)width, (const int)height);
			moveX = pt[0].xPos;
			moveY = pt[0].yPos;
			break;
		case '6':
			course = Course::Course_Draw;
			Initialize((const int)width, (const int)height);
			break;
		case 'z':
			Initialize((const int)width, (const int)height);
			break;
		case 'x':
			glutLeaveMainLoop();
			break;
		}
	}
	void Mouse(int button,int state,int x, int y)
	{
		bool L_flag = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
		bool R_flag = button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN;
		bool Draw_flag = course == Course::Course_Draw;
		if (L_flag && Draw_flag && !point.Draw)
		{
			if (MouseCount > SIZE - 1)
				MouseCount = 0;
			pt[MouseCount].xPos = (float)x;
			pt[MouseCount].yPos = (float)y;
			pt[MouseCount].Draw = true;
			++MouseCount;
		}
		else if (R_flag && !point.Draw)
		{
			b_Translate = false;
			point.Draw = true;
			moveX = pt[0].xPos;
			moveY = pt[0].yPos;
		}
	}
public:
	CShape() = default;
	~CShape() = default;
};