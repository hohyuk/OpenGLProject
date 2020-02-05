#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define WinX 800
#define WinY 600
#define Size 5
#define PI 3.14f

struct Rectangle
{
	float xPos, yPos;
	float moveX, moveY;
	float corR, corG, corB;
	float Angle;
	bool b_draw{ false };

	bool left_button{ false };
};

Rectangle PlayRec;
Rectangle Rec[Size];
int Count{ 0 };
float Radius{ 25 };
float Speed{ 5.f };
GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerFunction(int value);

void RectInit(int x, int y);
void Follow();

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example08");
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
	if (PlayRec.b_draw)
	{
		glColor4f(1.f, 0.f, 0.f, 1.f);
		glRectf(PlayRec.xPos - 10, PlayRec.yPos - 10, PlayRec.xPos + 10, PlayRec.yPos + 10);
	}
	for (int i = 0; i < Size; ++i)
	{
		if (Rec[i].b_draw)
		{
			glColor4f(Rec[i].corR + 0.3f, Rec[i].corG + 0.3, Rec[i].corB + 0.3, 1.f);
			glRectf(Rec[i].xPos - Radius, Rec[i].yPos - Radius, Rec[i].xPos + Radius, Rec[i].yPos + Radius);
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
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		RectInit(x, y);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PlayRec.b_draw = true;
		PlayRec.left_button = true;
		PlayRec.xPos = x;
		PlayRec.yPos = y;
	}
	else
		PlayRec.left_button = false;
}

GLvoid Motion(int x, int y)
{
	if (PlayRec.left_button)
	{
		PlayRec.xPos = x;
		PlayRec.yPos = y;
	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
	if(PlayRec.b_draw)
		Follow();
}

void RectInit(int x, int y)
{
	Rec[Count].xPos = x;
	Rec[Count].yPos = y;
	Rec[Count].b_draw = true;
	Rec[Count].corR = rand() % 2;
	Rec[Count].corG = rand() % 2;
	Rec[Count].corB = rand() % 2;
	Rec[Count].moveX = 0;
	Rec[Count].moveY = 0;
	Rec[Count].Angle = 0;
	++Count;
	if (Count > Size - 1)
		Count = 0;
}

void Follow()
{
	float fWidth[Size]{ 0 };
	float fHeight[Size]{ 0 };
	float fDistance[Size]{ 0 };
	for (int i = 0; i < Size; ++i)
	{
		/*if (Rec[i].xPos < PlayRec.xPos)
			Rec[i].moveX = Speed;
		else if (Rec[i].xPos > PlayRec.xPos)
			Rec[i].moveX = -Speed;
		if (Rec[i].yPos < PlayRec.yPos)
			Rec[i].moveY = Speed;
		else if (Rec[i].yPos > PlayRec.yPos)
			Rec[i].moveY = -Speed;

		Rec[i].xPos += Rec[i].moveX + cos(PI / 180);
		Rec[i].yPos += Rec[i].moveY - sin(PI / 180);*/
		fWidth[i] = PlayRec.xPos - Rec[i].xPos;
		fHeight[i] = PlayRec.yPos - Rec[i].yPos;
		fDistance[i] = sqrt((fWidth[i] * fWidth[i]) + (fHeight[i] * fHeight[i]));

		// 아크코사인으로 각도를 구한다. W/D
		Rec[i].Angle = acosf(fWidth[i] / fDistance[i]) * 180 / PI;

		if (PlayRec.yPos > Rec[i].yPos)
			Rec[i].Angle = 360 - Rec[i].Angle;

		Rec[i].xPos += cos(Rec[i].Angle*PI / 180)*Speed;
		Rec[i].yPos += -sin(Rec[i].Angle*PI / 180)*Speed;
	}
}