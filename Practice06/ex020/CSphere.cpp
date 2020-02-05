#include "stdafx.h"
#include "CSphere.h"

CSphere::CSphere()
{
}

CSphere::~CSphere()
{
}

void CSphere::init()
{
	m_Translate = Point(70.f, 20.f, -60.f);
	m_Scale = 1.f;
	m_Speed = 0.01f;
}

void CSphere::run()
{
}

void CSphere::render()
{
	glPushMatrix();
	{
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		glPushMatrix();
		{
			glColor3f(0.f, 0.5f, 0.f);
			glScalef(1.f, 5.f, 1.f);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(0.5f, 0.f, 1.f);
			glTranslatef(0.f, 30.f, 0.f);
			glScalef(m_Scale, m_Scale, m_Scale);
			glutWireSphere(10,20,20);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void CSphere::reshape(int w, int h)
{
}

void CSphere::keyboard(unsigned char key, int x, int y)
{
}

void CSphere::mouse(int button, int state, int x, int y)
{
}

void CSphere::motion(int x, int y)
{
}

void CSphere::freemotion(int x, int y)
{
}

void CSphere::special(int key, int x, int y)
{
}

void CSphere::update(int value)
{
	if (m_Scale > 2.f)
		m_Speed = -0.01f;
	else if (m_Scale < 1.f)
		m_Speed = 0.01f;
	m_Scale += m_Speed;
}
