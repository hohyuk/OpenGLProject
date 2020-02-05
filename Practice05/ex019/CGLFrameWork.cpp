#include "stdafx.h"
#include "CScene.h"

//Scenes////////////////////
#include "CShape19.h"
///////////////////////////

#include "CGLFrameWork.h"



CGLFrameWork::CGLFrameWork()
	:m_projection{ true }
{
}


CGLFrameWork::~CGLFrameWork()
{
}

void CGLFrameWork::Init(int argc, char * argv[], int WinWidth, int WinHeight, int WinX, int WinY, const char * WinCaption, int DisplayMode)
{
	srand((unsigned)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(DisplayMode);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(WinX, WinY);
	glutCreateWindow(WinCaption);

	m_CurrScene = new CShape;
	m_CurrScene->init();
}

void CGLFrameWork::Run()
{
	glutMainLoop();
}

void CGLFrameWork::Draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Render();

	glutSwapBuffers();
}

void CGLFrameWork::Render()
{
	if (m_CurrScene) m_CurrScene->render();
}

void CGLFrameWork::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	// 3차원 그래픽스 객체를 2차원 평면으로 투영시키는 투영 변환

	glLoadIdentity();
	if (m_projection)
	{	// 원근 투영
		gluPerspective(60, double(w / h), 1.0, 500.0);
		glTranslatef(0.f, 0.f, -300.f);
	}
	else
	{	// 직각 투영
		glOrtho(0, w, 0, h, -100, 100);
		glTranslatef(WinX / 2.f, WinY / 2.f, 0.f);
	}
	
	glMatrixMode(GL_MODELVIEW);

	if (m_CurrScene) m_CurrScene->reshape(w, h);
	glutPostRedisplay();
}

void CGLFrameWork::Keyboard(unsigned char key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->keyboard(key, x, y);
}

void CGLFrameWork::Mouse(int button, int state, int x, int y)
{
	if (m_CurrScene) m_CurrScene->mouse(button, state, x, y);
}

void CGLFrameWork::Motion(int x, int y)
{
	if (m_CurrScene) m_CurrScene->motion(x, y);
}

void CGLFrameWork::FreeMotion(int x, int y)
{
	if (m_CurrScene) m_CurrScene->freemotion(x, y);
}

void CGLFrameWork::Special(int key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->special(key, x, y);
	if (key == GLUT_KEY_F1)
	{
		m_projection = !m_projection;
		Reshape(WinX, WinY);
	}
}

void CGLFrameWork::Update(int value)
{
	if (m_CurrScene) m_CurrScene->update(value);
	glutPostRedisplay();
	glutTimerFunc(m_fps, fnTimer, 1);
}
