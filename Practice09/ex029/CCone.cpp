#include "stdafx.h"
#include "CCone.h"

CCone::CCone()
{
}

CCone::~CCone()
{
}

void CCone::init()
{
	m_Translate = Point(70.f, 0.f, 60.f);
	m_Scale = 1.f;
	m_Speed = 0.01f;
}

void CCone::run()
{
}

void CCone::render()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.5f);
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		glPushMatrix();
		{
			glRotatef(-90, 1, 0, 0);
			glScalef(m_Scale, m_Scale, m_Scale);
			glutSolidCone(10, 20, 30, 30);
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(0.f, 50.f, 0.f);
			glRotatef(90, 1, 0, 0);
			glScalef(2.5f-m_Scale, 2.5f-m_Scale, 2.5f-m_Scale);
			glutSolidCone(10, 20, 30, 30);
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void CCone::reshape(int w, int h)
{
}

void CCone::keyboard(unsigned char key, int x, int y)
{
}

void CCone::mouse(int button, int state, int x, int y)
{
}

void CCone::motion(int x, int y)
{
}

void CCone::freemotion(int x, int y)
{
}

void CCone::special(int key, int x, int y)
{
}

void CCone::update(int value)
{
	if (m_Scale > 2.f)
		m_Speed = -0.01f;
	else if (m_Scale < 0.5f)
		m_Speed = 0.01f;
	m_Scale += m_Speed;
}
