#include "stdafx.h"
#include "CGround.h"
CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::init()
{
	m_Info = Point(0.f, -100.f, 0.f);
}

void CGround::update(int value)
{
}

void CGround::render()
{
	glTranslatef(m_Info.xPos, m_Info.yPos, m_Info.zPos);
	glPushMatrix();
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glScalef(7, 1, 7);
		glutSolidCube(30);
	}
	glPopMatrix();

	// 다른 물체들을 땅바닥에 놓게 한다.
	glTranslatef(0.f, 15.f, 0.f);
}

void CGround::reshape(int w, int h)
{
}

void CGround::keyboard(unsigned char key, int x, int y)
{
	
}

void CGround::mouse(int button, int state, int x, int y)
{
}

void CGround::motion(int x, int y)
{
}

void CGround::freemotion(int x, int y)
{
}

void CGround::special(int key, int x, int y)
{
}

void CGround::run()
{
}

