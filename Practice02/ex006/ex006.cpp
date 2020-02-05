#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define WinX 800
#define WinY 600
#define Size 10
struct Rectangle
{
	float x, y;
	float radius{ 25 };
	float r, g, b;
	bool b_draw;
	int moveX, moveY;
	float tempX, tempY;
};

Rectangle Rec[Size];
int Count{ 0 };
int Rcount{ 0 };
bool b_Rotate{ false };

GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);
GLvoid RotateTimer(int value);
void RectInit();
void RectRotate();
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	RectInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example06");
	glutMouseFunc(Mouse);
	glutTimerFunc(2000, TimerFunction, 1);
	glutTimerFunc(50, RotateTimer, 2);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	
	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < Size; ++i)
	{
		if (Rec[i].b_draw)
		{
			glColor4f(Rec[i].r + 0.1f, Rec[i].g + 0.1f, Rec[i].b + 0.1f, 1.f);
			glRectf(Rec[i].x - Rec[i].radius, Rec[i].y - Rec[i].radius, Rec[i].x + Rec[i].radius, Rec[i].y + Rec[i].radius);
		}
	}
	
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glOrtho(0, WinX, WinY, 0, 0, 1);
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	
	glutPostRedisplay();
	glutTimerFunc(2000, TimerFunction, 1);
	if (Count < Size)
		Rec[Count++].b_draw = true;
}

GLvoid RotateTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, RotateTimer, 2);
	
	if (b_Rotate)
		RectRotate();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		b_Rotate = !b_Rotate;
	}
}

void RectInit()
{
	for (int i = 0; i < Size; ++i)
	{
		Rec[i].b_draw = false;
		Rec[i].x = (rand() % (WinX / 2)) + 300;
		Rec[i].y = (rand() % (WinY / 2)) + 200;
		Rec[i].r = rand() % 2;
		Rec[i].g = rand() % 2;
		Rec[i].b = rand() % 2;
		Rec[i].moveX = 2;
		Rec[i].moveY = 0;
		Rec[i].tempX = Rec[i].x;
		Rec[i].tempY = Rec[i].y;
	}
}

void RectRotate()
{
	if (Rcount >= Size)
	{
		Rcount = 0;
		b_Rotate = false;
	}
	else
	{
		if (Rec[Rcount].x > WinX - Rec[Rcount].radius)
		{
			Rec[Rcount].moveX = 0;
			Rec[Rcount].moveY = 2;
		}
		if (Rec[Rcount].y > WinY - Rec[Rcount].radius)
		{
			Rec[Rcount].moveX = -2;
			Rec[Rcount].moveY = 0;
		}
		if (Rec[Rcount].x < Rec[Rcount].radius)
		{
			Rec[Rcount].moveX = 0;
			Rec[Rcount].moveY = -2;
		}
		if (Rec[Rcount].y < Rec[Rcount].tempY)
		{
			Rec[Rcount].moveX = 2;
			Rec[Rcount].moveY = 0;
			if (Rec[Rcount].x > Rec[Rcount].tempX)
			{
				if (Rcount < Size)
				{
					Rec[Rcount].x = Rec[Rcount].tempX;
					Rec[Rcount].y = Rec[Rcount].tempY;
					Rec[Rcount].moveX = 2;
					Rec[Rcount].moveY = 0;
					++Rcount;
				}

			}
		}
		std::cout << Rcount << std::endl;
		Rec[Rcount].x += Rec[Rcount].moveX;
		Rec[Rcount].y += Rec[Rcount].moveY;
	}
	
	
}
