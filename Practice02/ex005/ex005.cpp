#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#define WinX 800
#define WinY 600
#define Size 10

struct Shape
{
	int x, y;
	int r, g, b;
	int moveX, moveY;
	bool b_draw;
	bool b_flag, change;
	bool directionX;
	bool directionY;
};
//변수
Shape wShape[Size];
bool wDraw = true;
int Count = 0;
int radius = 25;
int TimeSpeed = 100;
//함수
GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
GLvoid MoveTimer(int value);
GLvoid SpecialKey(int key, int x, int y);

void Menu();
void MenuFunc(int button);
void ShapeInit(int count_, int x_, int y_);
void StretchProgress();
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example05");
	Menu();
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutSpecialFunc(SpecialKey);
	glutTimerFunc(100, Timerfunction, 1);
	glutTimerFunc(0, MoveTimer, 2);
	glutMainLoop();
	
	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < Size; ++i)
	{
		if (wShape[i].b_draw)
		{
			glColor4f(wShape[i].r + 0.5f, wShape[i].g, wShape[i].b, 1.f);

			if (wDraw)
			{
				glRecti(wShape[i].x - wShape[i].moveX, wShape[i].y - wShape[i].moveY,
					wShape[i].x + wShape[i].moveX, wShape[i].y + wShape[i].moveY);
			}
			else
			{
				glBegin(GL_TRIANGLES);
				{
					glVertex2i(wShape[i].x - wShape[i].moveX, wShape[i].y + wShape[i].moveY);
					glVertex2i(wShape[i].x, wShape[i].y - wShape[i].moveY);
					glVertex2i(wShape[i].x + wShape[i].moveX, wShape[i].y + wShape[i].moveY);
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
		if (Count < Size - 1)
			++Count;
		else
			Count = 0;
		ShapeInit(Count, x, y);
	}
}

GLvoid Timerfunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, Timerfunction, 1);
	StretchProgress();
}

GLvoid MoveTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(TimeSpeed, MoveTimer, 2);
	int numX = 0;
	int numY = 0;
	for (int i = 0; i < Size; ++i)
	{
		if (wShape[i].x < radius)
			wShape[i].directionX = true;
		else if (wShape[i].x > WinX - radius)
			wShape[i].directionX = false;

		if (wShape[i].y < radius)
			wShape[i].directionY = true;
		else if (wShape[i].y > WinY - radius)
			wShape[i].directionY = false;

		if (wShape[i].directionX)
			numX = 1;
		else
			numX = -1;

		if (wShape[i].directionY)
			numY = 1;
		else
			numY = -1;

		wShape[i].x += numX;
		wShape[i].y += numY;
	}
}
void ShapeInit(int count_, int x_, int y_)
{
	wShape[count_].x = x_;
	wShape[count_].y = y_;
	wShape[count_].r = rand() % 2;
	wShape[count_].g = rand() % 2;
	wShape[count_].b = rand() % 2;
	wShape[count_].moveX = radius;
	wShape[count_].moveY = radius;
	wShape[count_].b_draw = true;
	wShape[count_].change = true;
	wShape[count_].directionX = true;
	wShape[count_].directionY = true;
}

void StretchProgress()
{
	int numX = 0, numY = 0;

	for (int i = 0; i < Size; ++i)
	{

		if (wShape[i].change)		// x축으로 늘어남
		{
			numY = 0;
			wShape[i].moveY = radius;
			if (wShape[i].moveX > radius * 2)
				wShape[i].b_flag = false;
			else if (wShape[i].moveX < radius)
			{
				wShape[i].b_flag = true;
				wShape[i].change = false;
			}
			if (wShape[i].b_flag)
				numX = 1;
			else
				numX = -1;
		}
		else
		{
			numX = 0;
			wShape[i].moveX = radius;
			if (wShape[i].moveY > radius * 2)
				wShape[i].b_flag = false;
			else if (wShape[i].moveY < radius)
			{
				wShape[i].b_flag = true;
				wShape[i].change = true;
			}
			if (wShape[i].b_flag)
				numY = 1;
			else
				numY = -1;
		}
		wShape[i].moveX += numX;
		wShape[i].moveY += numY;
	}
}

GLvoid SpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		if (TimeSpeed <= 5)
			TimeSpeed = 5;
		else
			TimeSpeed -= 5;
	}
		
	else if (key == GLUT_KEY_DOWN)
		TimeSpeed += 5;
	glutPostRedisplay();

}

void Menu()
{
	int SubMenu1;
	int MainMenu;

	SubMenu1 = glutCreateMenu(MenuFunc);
	{
		glutAddMenuEntry("Rect", 1);
		glutAddMenuEntry("Triangle", 2);
	}
	MainMenu = glutCreateMenu(MenuFunc);
	{
		glutAddSubMenu("Type", SubMenu1);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		wDraw = true;
		break;
	case 2:
		wDraw = false;
		break;
	}
	glutPostRedisplay();
}