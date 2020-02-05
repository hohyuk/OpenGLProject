#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WinX 800
#define WinY 600
#define Size 5
#define PI 3.141592f
#define PSize 170		// PointSize Á¡ÀÇ °¹¼ö

struct Point
{
	float xPos, yPos;
	float corR, corG, corB;
	bool b_Draw{ false };
	bool b_PointDraw{ false };
};

Point Player[Size];
Point Dot[Size];
int Count{ 0 };
int PCount[Size];

void PointInin(int x, int y);
void Progress();
GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("example09");
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}

GLvoid DrawScene()
{
	float tempRad[Size] = { 0 };
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Size; ++i)
	{
		if (Player[i].b_Draw)
		{
			for (int j = 0, rad = 0; j < PCount[i]; ++j)
			{

				glPointSize(3);
				glColor4f(Player[i].corR + 0.5f, Player[i].corG + 0.5f, Player[i].corB + 0.5f, 1.f);
				if (j < 90)
				{
					++rad;
					Dot[i].xPos = Player[i].xPos + rad * cos(j*(2 * PI) / 30);
					Dot[i].yPos = Player[i].yPos + rad * -sin(j*(2 * PI) / 30);
					tempRad[i] = rad;
				}
				else
				{
					--rad;
					Dot[i].xPos = (Player[i].xPos + (tempRad[i] * 2)) + rad * -cos(j*(2 * PI) / 30);
					Dot[i].yPos = Player[i].yPos + rad * -sin(j*(2 * PI) / 30);
				}

				glBegin(GL_POINTS);
				{
					glVertex2f(Dot[i].xPos, Dot[i].yPos);
				}
				glEnd();
			}
		}
	}
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, WinX, WinY, 0, 0, 1);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PointInin(x, y);
	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
	Progress();
}

void PointInin(int x, int y)
{
	Player[Count].xPos = x;
	Player[Count].yPos = y;
	Player[Count].corR = rand() % 2;
	Player[Count].corG = rand() % 2;
	Player[Count].corB = rand() % 2;
	Player[Count].b_Draw = true;
	PCount[Count] = 0;
	Count++;
	if (Count > Size - 1)
		Count = 0;
}

void Progress()
{
	for (int i = 0; i < Size; ++i)
	{
		if (Player[i].b_Draw)
		{
			if (PCount[i] < PSize)
			{
				++PCount[i];
			}

		}
	}
}