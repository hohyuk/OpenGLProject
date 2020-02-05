#include "stdafx.h"
#include "CTorus.h"

CTorus::CTorus()
{
}

CTorus::~CTorus()
{
}

void CTorus::init()
{
	m_Translate = Point(0.f, 0.f, 0.f);
	m_moveY = 1.f;
	m_Angle = 0.f;
}

void CTorus::run()
{
}

void CTorus::render()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.5f);
		
		glTranslatef(-70, 0, 60);		// 먼저 이동을 시킨다.

		glPushMatrix();		// Cube
		{
			glColor3f(0.7f, 0.f, 0.3f);
			glTranslatef(0, 20, 0);
			glScalef(1, 5, 1);
			glutSolidCube(10);
		}
		glPopMatrix();
		

		glPushMatrix();		// Torus
		{
			glColor3f(0.5f, 0.f, 1.f);

			glTranslatef(0, m_Translate.yPos, 0);		// 먼저 이동을 시킨다.
			glRotatef(90, 1, 0, 0);						// x축으로 회전 시킨다.
			glRotatef(m_Angle, 0, 0, 1);				// z축으로 계속 회전 시킨다.

			glutWireTorus(10, 20, 20, 20);
		}
		glPopMatrix();
		
		
	}
	glPopMatrix();
}

void CTorus::reshape(int w, int h)
{
}

void CTorus::keyboard(unsigned char key, int x, int y)
{
}

void CTorus::mouse(int button, int state, int x, int y)
{
}

void CTorus::motion(int x, int y)
{
}

void CTorus::freemotion(int x, int y)
{
}

void CTorus::special(int key, int x, int y)
{
}

void CTorus::update(int value)
{
	if (m_Translate.yPos > 50)
		m_moveY -= 1.f;
	else if (m_Translate.yPos < 0)
		m_moveY += 1.f;
	m_Translate.yPos += m_moveY;

	if (m_Angle > 360.f)
		m_Angle = 0.f;
	m_Angle += 5.f;
}
