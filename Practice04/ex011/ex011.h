#pragma once
#define SIZE 5
const float PI{ 3.141592f };
const float SizeX = 200;

struct Point
{
	float xPos;
	float yPos;
	float zPos;
};
struct Rect
{
	float xPos;
	float yPos;
	float Lrad;
	float Rrad;
	bool b_Draw;
};
class CLine
{
private:
	Point point;
	float moveX, moveY;
	float ScaleX;
	float RotateX, RotateY, RotateZ;
	float Anim, RectAnim;
	bool b_Anim;
	Rect rect[SIZE];
public:
	void Initialize()
	{
		point.xPos = 0.f;
		point.yPos = 0.f;
		point.zPos = 0.f;
		moveX = 0, moveY = 0;
		ScaleX = 1;
		RotateX = 0, RotateY = 0, RotateZ = 0;
		Anim = 0;
		RectAnim = 0;
		b_Anim = false;
		for (int i = 0; i < SIZE; ++i)
		{
			rect[i].xPos = (float)(i * 100);
			rect[i].yPos = 25;
			rect[i].Lrad = -25;
			if (rect[i].xPos >= 0)
			{
				rect[i].b_Draw = true;
				rect[i].Rrad = 25;
			}	
			else
			{
				rect[i].b_Draw = false;
				rect[i].Lrad = 25;
			}
				
		}
	}
	void Coordinates(const int width,const int height)
	{
		glColor3f(0.f, 1.f, 0.f);
		glBegin(GL_LINES);
		{
			glVertex3f(0.f, height/2.f, 0.f);
			glVertex3f((float)width, height/2.f, 0.f);
			glVertex3f(width/2.f, 0.f, 0.f);
			glVertex3f(width/2.f, (float)height, 0.f);
		}
		glEnd();
		
	}
	void Render(const int width, const int height)
	{
		// 1. Sin 곡선.
		glPushMatrix();
		{
			// 중점 맞추기.
			glTranslatef(width / 2.f + moveX, height / 2.f - 200, 0);
			glRotatef(RotateX, 1.f, 0.f, 0.f);
			glRotatef(RotateY, 0.f, 1.f, 0.f);
			glRotatef(RotateZ, 0.f, 0.f, 1.f);
			glScalef(ScaleX, 1.f, 1.f);

			glColor3f(1.f, 1.f, 1.f);
			glBegin(GL_LINE_STRIP);
			for (float i = -SizeX; i < SizeX; ++i)
			{
				point.xPos = i;
				point.yPos = -50 * sin((i * PI / 30) - Anim);
				glVertex3f(point.xPos, point.yPos, 0.f);
			}
			glEnd();
		}
		glPopMatrix();
		// 2. 코사인 곡선.
		glPushMatrix();
		{
			// 중점 맞추기.
			glTranslatef(width / 2.f + moveX, height / 2.f - 100, 0);
			glRotatef(RotateX, 1.f, 0.f, 0.f);
			glRotatef(RotateY, 0.f, 1.f, 0.f);
			glRotatef(RotateZ, 0.f, 0.f, 1.f);
			glScalef(ScaleX, 1.f, 1.f);

			glColor3f(1.f, 1.f, 1.f);
			glBegin(GL_LINE_STRIP);
			for (float i = -SizeX; i < SizeX; ++i)
			{
				point.xPos = i;
				point.yPos = -50 * cos((i * PI / 30) - Anim);
				glVertex3f(point.xPos, point.yPos, 0.f);
			}
			glEnd();
		}
		glPopMatrix();
		// 3. 스프링 
		glPushMatrix();
		{
			// 중점 맞추기.
			glTranslatef(width / 2.f + moveX, height / 2.f + 100, 0);
			glRotatef(RotateX, 1.f, 0.f, 0.f);
			glRotatef(RotateY, 0.f, 1.f, 0.f);
			glRotatef(RotateZ, 0.f, 0.f, 1.f);
			glScalef(ScaleX, 1.f, 1.f);
			
			glBegin(GL_LINE_STRIP);
			for (float i = -SizeX; i < SizeX; ++i)
			{
				if (i < -20)
					glColor3f(1.f, 0.f, 0.f);
				else if(i<50)
					glColor3f(1.f, 0.f, 1.f);
				else
					glColor3f(0.f, 0.f, 1.f);
				point.xPos = i + 50 * cos((i*PI/30)-Anim);
				point.yPos = 50 * (-sin((i * PI / 30) - Anim));
				glVertex3f(point.xPos, point.yPos, 0.f);
			}
			glEnd();
		}
		glPopMatrix();
		// 4. 큐브
		glPushMatrix();
		{
			glTranslatef(width / 2.f + moveX, height / 2.f + 200, 0);
			glRotatef(RotateX, 1.f, 0.f, 0.f);
			glRotatef(RotateY, 0.f, 1.f, 0.f);
			glRotatef(RotateZ, 0.f, 0.f, 1.f);
			glScalef(ScaleX, 1.f, 1.f);
			
			glPushMatrix();
			{
				// 중점 맞추기 (-200을 원점으로).
				float CenterX = -200.f;
				glTranslatef(CenterX, 0.f, 0);

				glColor3f(1.f, 1.f, 1.f);
				for (int i = 0; i < SIZE; ++i)
				{
					if (rect[i].b_Draw)
					{
						glRectf(rect[i].xPos + rect[i].Lrad, -rect[i].yPos,
							rect[i].xPos + rect[i].Rrad, rect[i].yPos);
					}

				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		// Rotate
		case 'x':case 'X':
			if (RotateX < 360)
				RotateX += 5.f;
			else
				RotateX = 0.f;
			break;
		case 'y':case 'Y':
			if (RotateY < 360)
				RotateY += 5.f;
			else
				RotateY = 0.f;
			break;
		case 'z':case 'Z':
			if (RotateZ < 360)
				RotateZ += 5.f;
			else
				RotateZ = 0.f;
			break;
		// Scale
		case 's':case 'S':
			ScaleX += 1;
			break;
		case 'd':case 'D':
			if(ScaleX>0)
				ScaleX -= 1;
			break;
		// Reset
		case 'i':case 'I':
			Initialize();
			break;
		// Animation
		case 'a':case 'A':
			b_Anim = !b_Anim;
			break;
		// Quit
		case 'q':case 'Q':
			glutLeaveMainLoop();
			break;
		}
	}
	void SpcKeyboard(int key)
	{
		if (key == GLUT_KEY_LEFT)
			moveX -= 10;
		else if (key == GLUT_KEY_RIGHT)
			moveX += 10;
	}
	void Progress()
	{
		if (b_Anim)
		{
			if (Anim > 2*PI)
				Anim = 0;
			Anim += 0.25;

			for (int i = 0; i < SIZE; ++i)
			{
				rect[i].xPos += 1;
				if (rect[i].xPos > 400)
				{
					if (rect[i].Rrad < rect[i].Lrad)
					{
						rect[i].b_Draw = false;
						rect[i].Rrad = 25;
						rect[i].Lrad = 25;
						rect[i].xPos = -50;
					}
					rect[i].Rrad -= 1;
				}
				else if (rect[i].xPos > -50)
				{
					rect[i].b_Draw = true;
					if (rect[i].Lrad > -25)
						--rect[i].Lrad;
				}
					
				
			}
		}
			

	}
public:
	CLine() = default;
	~CLine() = default;
};