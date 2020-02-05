#include <GL/glut.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example01");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}

GLvoid drawScene()
{
	// Magenta
	glClearColor(1.f, 0.f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	// ���
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glRectf(-0.25f, -0.25f, 0.25f, 0.25f);
	// �ϴû�
	glColor4f(0.f, 1.f, 1.f, 1.f);
	glRectf(-1.f, 1.f, -0.5f, 0.5f);
	// �ʷϻ�
	glColor4f(0.f, 1.f, 0.f, 1.f);
	glRectf(0.5f, 1.f, 1.f, 0.5f);
	// ������
	glColor4f(1.f, 0.f, 0.f, 1.f);
	glRectf(-1.f, -0.5f, -0.5f, -1.f);
	// �����
	glColor4f(1.f, 1.f, 0.f, 1.f);
	glRectf(0.5f, -0.5f, 1.f, -1.f);
	glFlush();
}

GLvoid Reshape(int w,int h)
{
	glViewport(0, 0, w, h);
}