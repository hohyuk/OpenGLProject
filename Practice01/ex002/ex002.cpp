#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example02");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}

GLvoid drawScene()
{
	int random = rand() % 5 + 5;
	int num1 = 800 / random;
	int num2 = 600 / (random - 2);
	glClearColor(0.f, 1.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1.f, 0.f, 0.f, 1.f);
	for (int i = 0; i < random-2; ++i)
	{
		for (int j = 0; j < random+1; ++j)
		{
			if ((i+j)%2==0)
			{
				glRectf(j * num1, i * num2, (j * num1) + num1, (i * num2) + num2);
			}
		}
	}
	
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, 0, 1);
}