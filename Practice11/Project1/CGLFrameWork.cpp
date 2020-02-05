#include "stdafx.h"
#include "CSceneMgr.h"

#include "CGLFrameWork.h"



CGLFrameWork::CGLFrameWork()
{
	m_Trans = Point{ 0.f,0.f,-600.f };
	m_Rotate = Point{ 0.f,0.f,0.f };
	isProject = true;	// ���� : true �������� : false
}

CGLFrameWork::~CGLFrameWork()
{

}

void CGLFrameWork::init(int argc, char * argv[], int WinWidth, int WinHeight, int WinX_, int WinY_, const char * WinCaption, int DisplayMode)
{
	srand((unsigned)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(DisplayMode);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(WinX_, WinY_);
	glutCreateWindow(WinCaption);

	m_SceneMgr = new CSceneMgr;
	m_SceneMgr->init();
	isJoomIn = false;
	isJoomOut = false;
}

void CGLFrameWork::update(int value)
{
	if (m_SceneMgr) m_SceneMgr->update(value);
	glutPostRedisplay();
	glutTimerFunc(m_fps, fnTimer, 1);

	// 3���� ȸ���ϱ�
	if (m_Trans.zPos > -250)
	{
		isJoomIn = true;
	}
	if (isJoomIn)
	{
		if (m_Rotate.yPos > 360 * 3)
		{
			m_Rotate.yPos = 0.f;
			isJoomOut = true;
		}
		else
			m_Rotate.yPos += 1.f;
	}
	if (isJoomOut)
	{
		isJoomIn = false;
		if (m_Trans.zPos > -400)
			m_Trans.zPos -= 1.f;
		else
		{
			m_Rotate.yPos = 0.f;
			isJoomOut = false;
		}
			
	}
	reshape(WinX, WinY);
}

void CGLFrameWork::draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render();

	glutSwapBuffers();
}

void CGLFrameWork::render()
{
	if (m_SceneMgr) m_SceneMgr->render();
}

void CGLFrameWork::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	// 3���� �׷��Ƚ� ��ü�� 2���� ������� ������Ű�� ������ȯ

	glLoadIdentity();
	if (isProject)
	{
		// ���� ����
		glOrtho(0, w, 0, h, -500, 500);
		glTranslated(WinX / 2.f, WinY / 2.f, 0);
	}
	else
	{
		// ���� ����
		gluPerspective(60.f, double(w / h), 1.0, 1000.0);
		glTranslatef(m_Trans.xPos, m_Trans.yPos, m_Trans.zPos);
	}
	

	// ī�޶�
	glRotatef(m_Rotate.xPos, 1, 0, 0);
	glRotatef(m_Rotate.yPos, 0, 1, 0);
	glRotatef(m_Rotate.zPos, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

	if (m_SceneMgr) m_SceneMgr->reshape(w, h);
	glutPostRedisplay();
}

void CGLFrameWork::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		if (m_Rotate.xPos > 360.f)
			m_Rotate.xPos = 0.f;
		m_Rotate.xPos += 5.f;
		break;
	case 'y':
		if (m_Rotate.yPos > 360.f)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += 5.f;
		break;
	case 'z':
		if (m_Rotate.zPos > 360.f)
			m_Rotate.zPos = 0.f;
		m_Rotate.zPos += 5.f;
		break;
	case 'w':
		if (!isJoomIn && !isJoomOut)
			m_Trans.zPos += 1.f;
		cout << m_Trans.zPos << endl;
		break;
	case 's':m_Trans.zPos -= 1.f;
		cout << m_Trans.zPos << endl;
		break;
	case 'a':m_Trans.xPos += 1.f;
		break;
	case 'd':m_Trans.xPos -= 1.f;
		break;
	case 'i':
		m_Trans = Point{ 0.f,0.f,-400.f };
		m_Rotate = Point(0.f, 0.f, 0.f);
		break;
	}
	if (m_SceneMgr) m_SceneMgr->keyboard(key, x, y);
	reshape(WinX, WinY);
	glutPostRedisplay();
}

void CGLFrameWork::special(int key, int x, int y)
{
	if (m_SceneMgr) m_SceneMgr->special(key, x, y);
	if (key == GLUT_KEY_F1) isProject = !isProject;
	reshape(WinX, WinY);
	glutPostRedisplay();
}

void CGLFrameWork::mouse(int button, int state, int x, int y)
{
	if (m_SceneMgr) m_SceneMgr->mouse(button, state, x, y);
	glutPostRedisplay();
}

void CGLFrameWork::motion(int x, int y)
{
	if (m_SceneMgr) m_SceneMgr->motion(x, y);
	glutPostRedisplay();
}

void CGLFrameWork::freemotion(int x, int y)
{
	if (m_SceneMgr) m_SceneMgr->freemotion(x, y);
	glutPostRedisplay();
}

void CGLFrameWork::run()
{
	glutMainLoop();
	if(m_SceneMgr) m_SceneMgr->run();
	delete m_SceneMgr;
}