#include "stdafx.h"
#include "CDoor.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
}

void CDoor::init()
{
	m_Translate = Point{ 0.f,20.f,-30.f };
	m_moveX = 5.f;
	m_Speed = 0.5f;

}

void CDoor::run()
{
}

void CDoor::render()
{
	glPushMatrix();
	{
		glColor3f(0.f, 1.f, 0.f);
		// ¿ÞÂÊ ±âµÕ
		glPushMatrix();
		{
			m_Translate.xPos = -5.f - m_moveX;
			glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
			glScalef(1.f, 5.f, 1.f);
			glutSolidCube(10);
		}
		glPopMatrix();

		// ¿À¸¥ÂÊ ±âµÕ
		glPushMatrix();
		{
			m_Translate.xPos = 5.f + m_moveX;
			glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
			glScalef(1.f, 5.f, 1.f);
			glutSolidCube(10);
		}
		glPopMatrix();

		// À­ ±âµÕ
		glPushMatrix();
		{
			glTranslatef(0.f, m_Translate.yPos + 20.f, m_Translate.zPos);
			glScalef(m_moveX / 5, 1.f, 1.f);
			glutSolidCube(10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CDoor::reshape(int w, int h)
{
}

void CDoor::keyboard(unsigned char key, int x, int y)
{
}

void CDoor::mouse(int button, int state, int x, int y)
{
}

void CDoor::motion(int x, int y)
{
}

void CDoor::freemotion(int x, int y)
{
}

void CDoor::special(int key, int x, int y)
{
}

void CDoor::update(int value)
{
	if (m_moveX > 20)
		m_Speed = -0.5f;
	else if (m_moveX < 0)
		m_Speed = 0.5f;
	m_moveX += m_Speed;
}
