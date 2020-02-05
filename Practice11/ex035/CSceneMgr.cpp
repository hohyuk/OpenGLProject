#include "stdafx.h"
#include "CSceneMgr.h"

#include "CHexa.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::init()
{
	isDepth = true;
	m_Obj[0] = new CHexa;
	
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->init();
	}
}

void CSceneMgr::update(int value)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->update(value);
	}
}

void CSceneMgr::render()
{
	// 은면 제거
	if (isDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	coordinates();
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->render();
	}
}

void CSceneMgr::reshape(int w, int h)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->reshape(w, h);
	}
}

void CSceneMgr::keyboard(unsigned char key, int x, int y)
{
	if (key == '0')
		isDepth = !isDepth;
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->keyboard(key, x, y);
	}
}

void CSceneMgr::mouse(int button, int state, int x, int y)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->mouse(button, state, x, y);
	}
}

void CSceneMgr::motion(int x, int y)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->motion(x, y);
	}
}

void CSceneMgr::freemotion(int x, int y)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->freemotion(x, y);
	}
}

void CSceneMgr::special(int key, int x, int y)
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->special(key, x, y);
	}
}

void CSceneMgr::run()
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		m_Obj[i]->run();
	}
}

void CSceneMgr::coordinates()
{
	// 좌표계
	glPushMatrix();
	{
		glTranslatef(0, 150, 0);
		glBegin(GL_LINES);
		{
			glColor3f(1.f, 0.f, 0.f);
			glVertex3d(0, 0, 0);
			glVertex3d(10, 0, 0);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 10, 0);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, 10);
		}
		glEnd();
	}
	glPopMatrix();
}
