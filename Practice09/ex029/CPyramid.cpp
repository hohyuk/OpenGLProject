#include "CPyramid.h"

CPyramid::CPyramid()
{
}

CPyramid::~CPyramid()
{
}

void CPyramid::init()
{
	m_Translate = Point(0.f, 0.f, 0.f);
	Earth_Revolution = 0;
	Moon_Revolution = 0;
}

void CPyramid::update(int value)
{
	if (Earth_Revolution > 360)
		Earth_Revolution = 0.f;
	Earth_Revolution += 0.5f;

	if (Moon_Revolution > 360)
		Moon_Revolution = 0.f;
	Moon_Revolution += 1.f;
}

void CPyramid::render()
{
	// 피라미드
	glColor3f(0.5f, 0.5f, 0.f);
	glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
	glPushMatrix();
	{
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(30, 60, 4, 4);
	}
	glPopMatrix();

	// 지구
	glColor3f(0.0f, 0.0f, 0.5f);
	glTranslatef(0, 60, 0);
	glPushMatrix();
	{
		glRotatef(Earth_Revolution, 0, 1, 0);
		glTranslatef(40.f, 0.f, 0.f);
		glutSolidSphere(5, 30, 30);

		// 달
		glPushMatrix();
		{
			glColor3f(0.0f, 0.5f, 0.f);
			glRotatef(Moon_Revolution, 0, 1, 0);
			glTranslatef(10.f, 0.f, 0.f);
			glutSolidSphere(2.5, 30, 30);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CPyramid::reshape(int w, int h)
{
}

void CPyramid::keyboard(unsigned char key, int x, int y)
{
}

void CPyramid::mouse(int button, int state, int x, int y)
{
}

void CPyramid::motion(int x, int y)
{
}

void CPyramid::freemotion(int x, int y)
{
}

void CPyramid::special(int key, int x, int y)
{
}

void CPyramid::run()
{
}
