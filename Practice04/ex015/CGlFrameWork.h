#pragma once
#include "ex015.h"
using namespace std;

namespace
{
	CShape shape;
}
class CGlFrameWork
{
private:
	using DrawFunc = void(*)();
	using ReshapeFunc = void(*)(int, int);
	using TimerFunc = void(*)(int);
	using MouseFunc = void(*)(int, int, int, int);
	using KeyFunc = void(*)(unsigned char, int, int);
	using SpcKeyFunc = void(*)(int, int, int);

	DrawFunc fnDraw{ nullptr };
	ReshapeFunc fnReshape{ nullptr };
	TimerFunc fnTimer{ nullptr };
	MouseFunc fnMouse{ nullptr };
	KeyFunc fnKey{ nullptr };
	SpcKeyFunc fnSpcKey{ nullptr };
	int m_fps = 16;
public:
	GLvoid GlutInitialize(int argc, char* argv[]
		, const int width, const int height
		, int x, int y
		, const char* caption
		, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA)
	{
		srand((unsigned)time(NULL));
		glutInit(&argc, argv);
		glutInitDisplayMode(DisplayMode);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(x, y);
		glutCreateWindow(caption);

		shape.Initialize();
	}
	GLvoid Run() { glutMainLoop(); }
	GLvoid DrawScene()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		Render();

		glutSwapBuffers();
	}
	GLvoid Reshape(int w, int h)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();
		glOrtho(0, w, h, 0, -300, 300);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	GLvoid Timer(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(m_fps, fnTimer, 1);
		shape.Progress();
	}
	GLvoid Mouse(int button, int state, int x, int y)
	{
		shape.Mouse(button, state, x, y);
		glutPostRedisplay();
	}
	GLvoid Keyboard(unsigned char key, int x, int y)
	{
		
		glutPostRedisplay();
	}
	GLvoid SpecialKeyboard(int key, int x, int y)
	{
		glutPostRedisplay();
	}
private:
	void Render()
	{
		// ±âº» ÁÂÇ¥°è.
		/*glColor3f(0.f, 1.f, 0.f);
		glBegin(GL_LINES);
		{
			glVertex3d(0, WinY / 2, 0);
			glVertex3d(WinX, WinY / 2, 0);
			glVertex3d(WinX / 2, 0, 0);
			glVertex3d(WinX / 2, WinY, 0);
		}
		glEnd();*/

		shape.Render();
	}
public:
	void RegisterDrawFunction(DrawFunc draw) { fnDraw = draw; }
	void RegisterReshapeFunction(ReshapeFunc reshape) { fnReshape = reshape; }
	void RegisterTimerFunction(TimerFunc timer) { fnTimer = timer; }
	void RegisterMouseFunction(MouseFunc mouse) { fnMouse = mouse; }
	void RegisterKeyFunction(KeyFunc key) { fnKey = key; }
	void RegisterSpecialKeyFunction(SpcKeyFunc spkey) { fnSpcKey = spkey; }
	void Bind()
	{
		glutDisplayFunc(fnDraw);
		glutReshapeFunc(fnReshape);
		glutMouseFunc(fnMouse);
		glutKeyboardFunc(fnKey);
		glutSpecialFunc(fnSpcKey);
		glutTimerFunc(m_fps, fnTimer, 1);
	}
public:
	CGlFrameWork() = default;
	~CGlFrameWork() = default;
};