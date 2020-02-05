#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define WinX 800
#define WinY 600
#define Size 10

enum class State
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
};
const int LeftUp_x{ 100 };
const int LeftUp_y{ 100 };
const int RightDown_x{ WinX - 100 };
const int RightDown_y{ WinY - 100 };

struct Rectangle
{
	float xPos, yPos;
	float corR, corG, corB;
	float PointSize;
	float Speed;
	bool b_Draw{ false };
};

Rectangle Rec[Size];
State e_state[Size];
int Count{ 0 };
GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

void RectInit(int x, int y);
void Direction();
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("example10");
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Small Box
	glColor4f(0.2f, 0.2f, 0.2f, 1.f);
	glRectf(LeftUp_x, LeftUp_y, RightDown_x, RightDown_y);

	for (int i = 0; i < Size; ++i)
	{
		if (Rec[i].b_Draw)
		{
			glPointSize(Rec[i].PointSize);
			glBegin(GL_POINTS);
			{
				glColor4f(Rec[i].corR + 0.5f, Rec[i].corG + 0.5, Rec[i].corB + 0.5, 1.f);
				glVertex2f(Rec[i].xPos, Rec[i].yPos);
			}
			glEnd();
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
	bool Click = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
	bool SmallBox = (x > LeftUp_x && x<RightDown_x) && (y>LeftUp_y && y < RightDown_y);
	if (Click&&SmallBox)
	{
		RectInit(x, y);
	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
	Direction();
}

void RectInit(int x, int y)
{
	Rec[Count].xPos = x;
	Rec[Count].yPos = y;
	Rec[Count].corR = rand() % 2;
	Rec[Count].corG = rand() % 2;
	Rec[Count].corB = rand() % 2;
	Rec[Count].PointSize = 20;
	Rec[Count].b_Draw = true;
	Rec[Count].Speed = rand() % 10 + 1;
	e_state[Count] = State(rand()%8);
	Count++;
	if (Count > Size - 1)
		Count = 0;
	
}

void Direction()
{
	for (int i = 0; i < Size; ++i)
	{
		
		// 방향
		if (e_state[i] == State::LEFT)
			Rec[i].xPos -= Rec[i].Speed;
		else if (e_state[i] == State::RIGHT)
			Rec[i].xPos += Rec[i].Speed;
		else if (e_state[i] == State::UP)
			Rec[i].yPos -= Rec[i].Speed;
		else if (e_state[i] == State::DOWN)
			Rec[i].yPos += Rec[i].Speed;
		else if (e_state[i] == State::LEFT_UP)
		{
			Rec[i].xPos -= Rec[i].Speed;
			Rec[i].yPos -= Rec[i].Speed;
		}
		else if (e_state[i] == State::LEFT_DOWN)
		{
			Rec[i].xPos -= Rec[i].Speed;
			Rec[i].yPos += Rec[i].Speed;
		}
		else if (e_state[i] == State::RIGHT_UP)
		{
			Rec[i].xPos += Rec[i].Speed;
			Rec[i].yPos -= Rec[i].Speed;
		}
		else if (e_state[i] == State::RIGHT_DOWN)
		{
			Rec[i].xPos += Rec[i].Speed;
			Rec[i].yPos += Rec[i].Speed;
		}

		// 크기 변화
		if (Rec[i].xPos < LeftUp_x || Rec[i].xPos>RightDown_x ||
			Rec[i].yPos<LeftUp_y || Rec[i].yPos>RightDown_y)
			Rec[i].PointSize -= 0.5;

		// 사라짐
		if (Rec[i].PointSize < 1.f)
		{
			Rec[i].corR = -0.5f;
			Rec[i].corG = -0.5f;
			Rec[i].corB = -0.5f;
		}
	}
	
}