#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

#define WinX 800
#define WinY 600
#define Size 10

struct Rect
{
	int x, y;
	int r, g, b;
	int moveX, moveY;
	bool flag;
	bool mflag, change;
};

Rect rec[Size];
int Count = 0;
int radius = 25;
GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);

void RectInit(int count_, int x_, int y_);
void Progess();
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example04");
	glutMouseFunc(Mouse);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, Timerfunction, 1);
	glutMainLoop();

	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Size; ++i)
	{
		if (rec[i].flag == true)
		{
			glColor4f(rec[i].r + 0.5f, rec[i].g, rec[i].b, 1.f);
			glRecti(rec[i].x - rec[i].moveX, rec[i].y - rec[i].moveY,
				rec[i].x + rec[i].moveX, rec[i].y + rec[i].moveY);
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
		if (Count < Size-1)
			++Count;
		else
			Count = 0;
		RectInit(Count, x, y);
	}
}

GLvoid Timerfunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, Timerfunction, 1);
	Progess();
}

void RectInit(int count_, int x_, int y_)
{
	rec[count_].x = x_;
	rec[count_].y = y_;
	rec[count_].r = rand() % 2;
	rec[count_].g = rand() % 2;
	rec[count_].b = rand() % 2;
	rec[count_].moveX = radius;
	rec[count_].moveY = radius;
	rec[count_].flag = true;
	rec[count_].mflag = true;
	rec[count_].change = true;
}
void Progess()
{
	int numX = 0;
	int numY = 0;
	for (int i = 0; i < Size; ++i)
	{
		if (rec[i].change)
		{
			numY = 0;
			rec[i].moveY = radius;
			if (rec[i].moveX > radius * 2)
				rec[i].mflag = false;
			else if (rec[i].moveX < radius)
			{
				rec[i].mflag = true;
				rec[i].change = false;
			}
			if (rec[i].mflag)
				numX = 1;
			else
				numX = -1;
		}
		else
		{
			numX = 0;
			rec[i].moveX = radius;
			if (rec[i].moveY > radius * 2)
				rec[i].mflag = false;
			else if (rec[i].moveY < radius)
			{
				rec[i].mflag = true;
				rec[i].change = true;
			}
			if (rec[i].mflag)
				numY = 1;
			else
				numY = -1;
		}
		rec[i].moveX += numX;
		rec[i].moveY += numY;
	}
}