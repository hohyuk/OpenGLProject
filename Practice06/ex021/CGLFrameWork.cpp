#include "stdafx.h"
#include "CSceneMgr.h"

#include "CGLFrameWork.h"



CGLFrameWork::CGLFrameWork()
{
	m_Camera = Point{ 0.f,0.f,0.f };
	m_Rotate = Point{ 0.f,0.f,0.f };
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
}

void CGLFrameWork::update(int value)
{
	if (m_SceneMgr) m_SceneMgr->update(value);
	glutPostRedisplay();
	glutTimerFunc(m_fps, fnTimer, 1);
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
	glMatrixMode(GL_PROJECTION);	// 3차원 그래픽스 객체를 2차원 평면으로 투영시키는 투영변환

	glLoadIdentity();
	// 원근 투영
	gluPerspective(60.f, double(w / h), 1.0, 1000.0);
	glTranslatef(0.f, 0.f, -300.f);

	// 카메라
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
	case 'i':
		m_Rotate = Point(0.f, 0.f, 0.f);
	}
	if (m_SceneMgr) m_SceneMgr->keyboard(key, x, y);
	reshape(WinX, WinY);
	glutPostRedisplay();
}

void CGLFrameWork::special(int key, int x, int y)
{
	if (m_SceneMgr) m_SceneMgr->special(key, x, y);
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
