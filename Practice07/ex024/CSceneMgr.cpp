#include "stdafx.h"
#include "CSceneMgr.h"

#include "CTorus.h"
CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::init()
{
	m_Obj = new CTorus;

	m_Obj->init();
}

void CSceneMgr::update(int value)
{
	m_Obj->update(value);
}

void CSceneMgr::render()
{
	
	coordinates();
	m_Obj->render();
}

void CSceneMgr::reshape(int w, int h)
{
	m_Obj->reshape(w, h);
}

void CSceneMgr::keyboard(unsigned char key, int x, int y)
{
	m_Obj->keyboard(key, x, y);
}

void CSceneMgr::mouse(int button, int state, int x, int y)
{
	m_Obj->mouse(button, state, x, y);
}

void CSceneMgr::motion(int x, int y)
{
	m_Obj->motion(x, y);
}

void CSceneMgr::freemotion(int x, int y)
{
	m_Obj->freemotion(x, y);
}

void CSceneMgr::special(int key, int x, int y)
{
	m_Obj->special(key, x, y);
}

void CSceneMgr::run()
{
	m_Obj->run();
}

void CSceneMgr::coordinates()
{
	// ÁÂÇ¥°è
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
