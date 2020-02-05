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
	m_Info = Point(0.f, -100.f, 50.f);
	m_Camera = Point(0.f, 30.f, -60.f);
}

void CGround::run()
{
}

void CGround::render()
{



	glTranslatef(m_Info.xPos, m_Info.yPos, m_Info.zPos);
	glRotatef(15.f, 1, 0, 0);
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glScalef(2, 1, 2);
		glutSolidCube(100);
	}
	glPopMatrix();

	// 다른 물체들을 땅바닥에 놓게 한다.
	glTranslatef(0.f, 50.f, 0);
}

void CGround::reshape(int w, int h)
{
}

void CGround::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':m_Info.yPos += 1.f;
		cout << "y : " << m_Camera.yPos << endl;
		break;
	case 's':m_Info.yPos -= 1.f;
		cout << "y : " << m_Camera.yPos << endl;
		break;
	case 'a':m_Info.zPos += 1.f;
		cout << "z : " << m_Camera.zPos << endl;
		break;
	case 'd':m_Info.zPos -= 1.f;
		cout << "z : " << m_Camera.zPos << endl;
		break;
	case 'q':m_Info.xPos -= 1.f;
		break;
	case 'e':m_Info.xPos += 1.f;
		break;
	case 'i': init();
		break;
	}
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

void CGround::update(int value)
{

}
