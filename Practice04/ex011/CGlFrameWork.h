#pragma once
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
#include <algorithm>
#include "ex011.h"
using namespace std;

const int WinX = 800;
const int WinY = 600;

namespace
{
	CLine line;
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

	DrawFunc fnDraw{ NULL };
	ReshapeFunc fnReshape{ NULL };
	TimerFunc fnTimer{ NULL };
	MouseFunc fnMouse{ NULL };
	KeyFunc fnKey{ NULL };
	SpcKeyFunc fnSpcKey{ NULL };
	int m_fps = 16;
public:
	GLvoid GlutInitialize(int argc, char* argv[]
		, const int width, const int height
		, int x, int y
		, const char* caption
		, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(DisplayMode);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(x, y);
		glutCreateWindow(caption);

		line.Initialize();
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
		glOrtho(0, w, h, 0, -100, 100);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	GLvoid Timer(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(m_fps, fnTimer, 1);
		line.Progress();
	}
	GLvoid Mouse(int button, int state, int x, int y)
	{
		
	}
	GLvoid Keyboard(unsigned char key, int x, int y)
	{
		line.Keyboard(key);
	}
	GLvoid SpecialKeyboard(int key, int x, int y)
	{
		line.SpcKeyboard(key);
	}
public:
	void Render()
	{
		line.Coordinates(WinX,WinY);
		line.Render(WinX, WinY);
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