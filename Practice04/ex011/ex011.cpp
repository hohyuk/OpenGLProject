#include <GL/glut.h>

#define WinX 800
#define WinY 600
GLvoid DrawScene();
GLvoid Reshape(int w, int h);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
	glutCreateWindow("Example11");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}

GLvoid DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	{
		glVertex3f(0, WinY / 2.f, 0.f);
		glVertex3f(WinX, WinY / 2.f, 0.f);
		glVertex3f(WinX / 2.f, 0, 0.f);
		glVertex3f(WinX / 2.f, WinY, 0.f);
	}
	glEnd();

	glColor3f(1.f, 0.f, 0.f);

	glutSolidCube(30);
	glPushMatrix();
	{
		glRotatef(45.f, 0.f, 0.f, 0.f);
		glTranslatef(100, 200, 0);
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WinX, WinY, 0, -100.f, 100.f);
	glutPostRedisplay();
}