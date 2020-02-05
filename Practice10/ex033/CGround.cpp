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
	BITMAPINFO* texture;

	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	pBytes = LoadDIBitMap("../Resource/aaa.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

void CGround::update(int value)
{
}

void CGround::render()
{
	//// 기본 바닥
	//glTranslatef(m_Info.xPos, m_Info.yPos, m_Info.zPos);
	//glPushMatrix();
	//{
	//	glColor3f(0.5f, 0.5f, 0.5f);
	//	glScalef(7, 1, 7);
	//	glutSolidCube(30);
	//}
	//glPopMatrix();
	glTranslatef(m_Info.xPos, m_Info.yPos, m_Info.zPos);
	for (int i = -15; i < 15; ++i)
	{
		for (int j = -10; j < 10; ++j)
		{
			glPushMatrix();
			{
				glColor3f(1.f, 1.f, 1.f);
				glBindTexture(GL_TEXTURE_2D, tex[0]);
				
				glTranslatef(i * 10, 10, j * 10);
				glutSolidCube(10);
			}
			glPopMatrix();
		}
	}

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

