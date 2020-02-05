#include "stdafx.h"
#include "CSceneMgr.h"

#include "CGround.h"
#include "CCone.h"
#include "CCube.h"
#include "CDoor.h"
#include "CSphere.h"
#include "CTorus.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::init()
{
	m_Objs[0] = new CGround;
	m_Objs[1] = new CCone;
	m_Objs[2] = new CCube;
	m_Objs[3] = new CDoor;
	m_Objs[4] = new CSphere;
	m_Objs[5] = new CTorus;

	Size = 6;
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->init();
	}
}

void CSceneMgr::update(int value)
{
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->update(value);
	}
}

void CSceneMgr::render()
{
	
	coordinates();
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->render();
	}
}

void CSceneMgr::reshape(int w, int h)
{
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->reshape(w, h);
	}
}

void CSceneMgr::keyboard(unsigned char key, int x, int y)
{
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->keyboard(key, x, y);
	}
}

void CSceneMgr::mouse(int button, int state, int x, int y)
{
	
}

void CSceneMgr::motion(int x, int y)
{
	
}

void CSceneMgr::freemotion(int x, int y)
{
	
}

void CSceneMgr::special(int key, int x, int y)
{
	for (int i = 0; i < Size; ++i)
	{
		m_Objs[i]->special(key, x, y);
	}
}

void CSceneMgr::run()
{
	for (int i = 0; i < Size; ++i)
	{
		delete m_Objs[i];
	}
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
