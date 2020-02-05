#include "stdafx.h"
#include "CScene.h"

//Scenes////////////////////
#include "CShape17.h"
///////////////////////////

#include "CGLFrameWork.h"



CGLFrameWork::CGLFrameWork()
	:m_projection{true}
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
	m_Camera = Point{ 0.f,0.f,0.f };
	m_Rotate = Point{ 0.f,0.f,0.f };
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
		glOrtho(0, w, h, 0, -100, 100);
		glTranslatef(WinX / 2.f, WinY / 2.f, 0.f);
	}
	gluLookAt(m_Camera.xPos, m_Camera.yPos, m_Camera.zPos, 0, 0, -100, 0, 1, 0);
	glRotatef(m_Rotate.xPos, 1.f, 0.f, 0.f);
	glRotatef(m_Rotate.yPos, 0.f, 1.f, 0.f);
	glRotatef(m_Rotate.zPos, 0.f, 0.f, 1.f);
	glMatrixMode(GL_MODELVIEW);

	if (m_CurrScene) m_CurrScene->reshape(w, h);
	glutPostRedisplay();
}

void CGLFrameWork::Keyboard(unsigned char key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->keyboard(key, x, y);

	switch (key)
	{
	case 'x':case 'X':
		if (m_Rotate.xPos > 360)
			m_Rotate.xPos = 0;
		m_Rotate.xPos += 1.f;
		break;
	case 'y':case 'Y':
		if (m_Rotate.yPos > 360)
			m_Rotate.yPos = 0;
		m_Rotate.yPos += 1.f;
		break;
	case 'z':case 'Z':
		if (m_Rotate.zPos > 360)
			m_Rotate.zPos = 0;
		m_Rotate.zPos += 1.f;
		break;
		// 카메라 이동
	case 'a':
		m_Camera.xPos -= 1;
		break;
	case 'd':
		m_Camera.xPos += 1;
		break;
	case 'w':
		m_Camera.yPos += 1;
		cout << m_Camera.yPos << endl;
		break;
	case 's':
		m_Camera.yPos -= 1;
		cout << m_Camera.yPos << endl;
		break;
	case 'o':
		m_Camera.zPos += 1;		// 멀리 이동.
		break;
	case 'p':
		m_Camera.zPos -= 1;		// 화면 쪽으로 이동
		break;
	case 'i':
		m_Camera = Point{ 0.f,0.f,0.f };
		m_Rotate = Point{ 0.f,0.f,0.f };
		break;
	}
	Reshape(WinX, WinY);
	glutPostRedisplay();
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
