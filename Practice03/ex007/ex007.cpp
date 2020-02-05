#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define WinX 800
#define WinY 600
#define Size 10
#define PI 3.14f
struct Circle
{
	float x{ 0 }, y{ 0 };
	float radius;
	float Cr, Cg, Cb;
	bool b_draw{ false };
};

Circle circle[Size];
int Count{ 0 };
float Angle{ 0 };
void CircleInit(int x,int y);
void FireWorks();
GLvoid DrawScene();
GLvoid Reshape(int w,int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example07");
	glutMouseFunc(Mouse);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPointSize(3);
	
	for (int i = 0; i < Size; ++i)
	{
		if (circle[i].b_draw)
		{
			glColor4f(circle[i].Cr + 0.5f, circle[i].Cg + 0.5f, circle[i].Cb + 0.5f, 5.f);
			for (int j = 0; j < 30; ++j)
			{
				float x = circle[i].x + (circle[i].radius * cos(j*(2 * PI) / 30));
				float y = circle[i].y + (circle[i].radius * -sin(j*(2 * PI) / 30));

				if (x > WinX||x<0||y<0||y>WinY)
				{
					circle[i].b_draw = false;
				}
				glBegin(GL_POINTS);
				{
					glVertex2f(x, y);
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
		CircleInit(x, y);
	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
	FireWorks();
}

void CircleInit(int x,int y)
{
	circle[Count].x = x;
	circle[Count].y = y;
	circle[Count].Cr = rand() % 2;
	circle[Count].Cg = rand() % 2;
	circle[Count].Cb = rand() % 2;
	circle[Count].radius = 5;
	circle[Count].b_draw = true;
	++Count;
	if (Count > Size-1)
		Count = 0;
	
}

void FireWorks()
{
	int num = 0;
	for (int i = 0; i < Size; ++i)
	{
		if (circle[i].b_draw)
		{
			if (i % 2 == 0)
			{
				if (circle[i].radius > 100)
				{
					circle[i].radius = 0;
				}
				else
					num = 5.f;
			}
			else
				num = 5.f;
			
			circle[i].radius += num;
		}
	}
}