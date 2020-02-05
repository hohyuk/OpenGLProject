#include "stdafx.h"
#include "CCube.h"

CCube::CCube()
{
}

CCube::~CCube()
{
}

void CCube::init()
{
	m_Translate = Point(-70.f, 20.f, -60.f);
	m_Angle = 0.f;
}

void CCube::run()
{
}

void CCube::render()
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.5f, 0.f);
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		glPushMatrix();
		{
			glScalef(1.f, 5.f, 1.f);
			glutSolidCube(10);
		}
		glPopMatrix();

		glColor3f(0.5f, 0.f, 1.f);
		glTranslatef(0.f, 20.f, 0.f);
		glRotatef(m_Angle, 0, 1, 0);
		glScalef(5.f, 1.f, 1.f);

		glutSolidCube(10);
	}
	glPopMatrix();
}

void CCube::reshape(int w, int h)
{
}

void CCube::keyboard(unsigned char key, int x, int y)
{
}

void CCube::mouse(int button, int state, int x, int y)
{
}

void CCube::motion(int x, int y)
{
}

void CCube::freemotion(int x, int y)
{
}

void CCube::special(int key, int x, int y)
{
}

void CCube::update(int value)
{
	if (m_Angle > 360)
		m_Angle = 0.f;
	m_Angle += 5.f;
}
