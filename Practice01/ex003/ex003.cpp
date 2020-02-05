#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

#define LINE 0
#define TRIANGLE 1
#define QUAD 2
#define PENTAGON 3

const int WX = 600;
const int WY = 600;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Parts();
void Shapes();

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WX, WY);
	glutCreateWindow("Examlpe03");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}

GLvoid drawScene()
{
	// 바탕색
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	Parts();
	Shapes();
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, WX, WY, 0, 0, 1);
}

void Parts()
{
	glColor4f(1.f, 1.f, 1.f, 1.f);
	
	for (int i = 0; i < 4; ++i)
	{
		glLineWidth(2.f);
		int length = i *(WX / 3);
		// x축
		glBegin(GL_LINES);
		glVertex2i(0, length);
		glVertex2i(WX, length);
		glEnd();
		// y축
		glBegin(GL_LINES);
		glVertex2i(length, 0);
		glVertex2i(length, WY);
		glEnd();
	}
}

void Shapes()
{
	
	int random = rand() % 4;
	int count = random;
	int vertex = 0;			// 꼭지점
	int glshape = 0;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{	
			int Rrand = rand() % 2;
			int Brand = rand() % 2;
			int Grand = rand() % 2;
			int xm = x * 200;
			int ym = y * 200;
			
			if (count == LINE)
			{
				glshape = GL_LINES;
				vertex = 2;
			}
			else if (count == TRIANGLE)
			{
				glshape = GL_TRIANGLES;
				vertex = 3;
			}
			else if (count == QUAD)
			{
				glshape = GL_QUADS;
				vertex = 4;
			}
			else if (count == PENTAGON)
			{
				glshape = GL_POLYGON;
				vertex = 5;
			}
			glColor4f(Rrand+0.5, Brand, Grand, 1.f);
			glBegin(glshape);
			for (int i = 0; i < vertex; ++i)
			{
				if (i == 0)
					glVertex2i(xm + 50, ym + 50);
				else if (i == 1)
					glVertex2i(xm + 50, ym + 150);
				else if (i == 2)
					glVertex2i(xm + 150, ym + 150);
				else if (i == 3)
					glVertex2i(xm + 150, ym + 50);
				else if (i == 4)
					glVertex2i(xm + 100, ym + 30);
				else if (i == 5)
					glVertex2i(xm + 100, ym + 180);
			}
			glEnd();
			if (count >= 3)
				count = 0;
			else
				++count;
		}
	}
	
}