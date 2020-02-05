#include "stdafx.h"
#include "CScene.h"

//Scenes////////////////////
#include "CGround.h"
#include "CTorus.h"
#include "CCube.h"
#include "CSphere.h"
#include "CCone.h"
#include "CDoor.h"
///////////////////////////

#include "CGLFrameWork.h"


Vector3 g_Picking;

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

	m_CurrScene = new CGround;
	m_Torus = new CTorus;
	m_Cube = new CCube;
	m_Sphere = new CSphere;
	m_Cone = new CCone;
	m_Door = new CDoor;
	m_CurrScene->init();
	m_Torus->init();
	m_Cube->init();
	m_Sphere->init();
	m_Cone->init();
	m_Door->init();
}

void CGLFrameWork::Run()
{
	glutMainLoop();
	delete m_CurrScene;
	delete m_Torus;
	delete m_Cube;
	delete m_Sphere;
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
	if (m_Torus) m_Torus->render();
	if (m_Cube) m_Cube->render();
	if (m_Sphere) m_Sphere->render();
	if (m_Cone) m_Cone->render();
	if (m_Door) m_Door->render();

	glPointSize(5);
	glBegin(GL_POINTS);
	{
		glColor3f(0.2f, 0.8f, 0.3f);
		glVertex3f(g_Picking.xPos, g_Picking.yPos, g_Picking.zPos);

	}
	glEnd();
	glPointSize(1);
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
	if (m_Torus) m_Torus->reshape(w, h);
	if (m_Cube) m_Cube->reshape(w, h);
	if (m_Sphere) m_Sphere->reshape(w, h);
	if (m_Cone) m_Cone->reshape(w, h);
	if (m_Door) m_Door->reshape(w, h);


	glutPostRedisplay();
}

void CGLFrameWork::Keyboard(unsigned char key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->keyboard(key, x, y);
	if (m_Torus) m_Torus->keyboard(key, x, y);
	if (m_Cube) m_Cube->keyboard(key, x, y);
	if (m_Sphere) m_Sphere->keyboard(key, x, y);
	if (m_Cone) m_Cone->keyboard(key, x, y);
	if (m_Door) m_Door->keyboard(key, x, y);

}

void CGLFrameWork::Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_Picking = Picking(x, y);
		cout << g_Picking.xPos << " , " << g_Picking.yPos << " , " << g_Picking.zPos << endl;
	}
	if (m_CurrScene) m_CurrScene->mouse(button, state, x, y);
	if (m_Torus) m_Torus->mouse(button, state, x, y);
	if (m_Cube) m_Cube->mouse(button, state, x, y);
	if (m_Sphere) m_Sphere->mouse(button, state, x, y);
	if (m_Cone) m_Cone->mouse(button, state, x, y);
	if (m_Door) m_Door->mouse(button, state, x, y);

	
}

void CGLFrameWork::Motion(int x, int y)
{
	if (m_CurrScene) m_CurrScene->motion(x, y);
	if (m_Torus) m_Torus->motion(x, y);
	if (m_Cube) m_Cube->motion(x, y);
	if (m_Sphere) m_Sphere->motion(x, y);
	if (m_Cone) m_Cone->motion(x, y);
	if (m_Door) m_Door->motion(x, y);

}

void CGLFrameWork::FreeMotion(int x, int y)
{
	if (m_CurrScene) m_CurrScene->freemotion(x, y);
	if (m_Torus) m_Torus->freemotion(x, y);
	if (m_Cube) m_Cube->freemotion(x, y);
	if (m_Sphere) m_Sphere->freemotion(x, y);
	if (m_Cone) m_Cone->motion(x, y);
	if (m_Door) m_Door->motion(x, y);

}

void CGLFrameWork::Special(int key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->special(key, x, y);
	if (m_Torus) m_Torus->special(key, x, y);
	if (m_Cube) m_Cube->special(key, x, y);
	if (m_Sphere) m_Sphere->special(key, x, y);
	if (m_Cone) m_Cone->special(key, x, y);
	if (m_Door) m_Door->special(key, x, y);

	if (key == GLUT_KEY_F1)
	{
		m_projection = !m_projection;
		Reshape(WinX, WinY);
	}
}

void CGLFrameWork::Update(int value)
{
	if (m_CurrScene) m_CurrScene->update(value);
	if (m_Torus) m_Torus->update(value);
	if (m_Cube) m_Cube->update(value);
	if (m_Sphere) m_Sphere->update(value);
	if (m_Cone) m_Cone->update(value);
	if (m_Door) m_Door->update(value);

	glutPostRedisplay();
	glutTimerFunc(m_fps, fnTimer, 1);
}
