#include "CSnow.h"

CSnow::CSnow()
{
	init();
}

CSnow::~CSnow()
{
	run();
}

void CSnow::init()
{
	for (int i = 0; i < MAX_SNOW; ++i)
	{
		m_snow[i] = NULL;
	}
	for (int i = 0; i < MAX_MARK; ++i)
	{
		m_mark[i] = NULL;
	}
	createTime = 0.f;
	speed = 1;
	color = 0.001f;
	isStart = true;

	BITMAPINFO* texture;

	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	pBytes = LoadDIBitMap("../Resource/StoneTile.bmp", &texture);
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

void CSnow::update(int value)
{
	if (isStart)
	{
		CreateSnow();

		for (int i = 0; i < MAX_SNOW; ++i)
		{
			if (m_snow[i] != NULL)
			{
				if (m_snow[i]->yPos < 0.f)
				{
					CreateMark(m_snow[i]);
					delete m_snow[i];
					m_snow[i] = NULL;
				}
				else
					m_snow[i]->yPos -= m_snow[i]->ySpeed;
			}

			if (m_mark[i] != NULL)
			{
				if (m_mark[i]->colR < 0.5f)
				{
					delete m_mark[i];
					m_mark[i] = NULL;
				}
				else
					m_mark[i]->colR -= color;
			}
		}
	}
}

void CSnow::render()
{
	// ���� ����
	for (int i = 0; i < MAX_SNOW; ++i)
	{
		if (m_snow[i] != NULL)
		{
			glPushMatrix();
			{
				glTranslatef(m_snow[i]->xPos, m_snow[i]->yPos, m_snow[i]->zPos);
				glColor3f(1.f, 1.f, 1.f);
				glBindTexture(GL_TEXTURE_2D, tex[0]);
				glutSolidSphere(2, 20, 20);
			}
			glPopMatrix();
		}
	}

	for (int i = 0; i < MAX_MARK; ++i)
	{
		if (m_mark[i] != NULL)
		{
			glPointSize(5);
			glBegin(GL_POINTS);
			{
				glColor3d(m_mark[i]->colR, m_mark[i]->colR, m_mark[i]->colR);
				glVertex3f(m_mark[i]->xPos, m_mark[i]->yPos, m_mark[i]->zPos);
			}
			glEnd();
		}
	}
}

void CSnow::reshape(int w, int h)
{
}

void CSnow::keyboard(unsigned char key, int x, int y)
{
	if (key == 'i')
	{
		run();
		init();
	}
	else if (key == 'p')
		isStart = !isStart;
}

void CSnow::mouse(int button, int state, int x, int y)
{
}

void CSnow::motion(int x, int y)
{
}

void CSnow::freemotion(int x, int y)
{
}

void CSnow::special(int key, int x, int y)
{
}

void CSnow::run()
{
	for (int i = 0; i < MAX_SNOW; ++i)
	{
		if (m_snow[i] != NULL)
		{
			delete m_snow[i];
			m_snow[i] = NULL;
		}
	}
	for (int i = 0; i < MAX_MARK; ++i)
	{
		if (m_mark[i] != NULL)
		{
			delete m_mark[i];
			m_mark[i] = NULL;
		}
	}
}

bool CSnow::CreateSnow()
{
	for (int i = 0; i < MAX_SNOW; ++i)
	{
		if (m_snow[i] == NULL)
		{
			m_snow[i] = new Point();
			m_snow[i]->xPos = float(rand() % 200 - 100);
			m_snow[i]->yPos = 300.f;
			m_snow[i]->zPos = float(rand() % 200 - 100);
			m_snow[i]->ySpeed = speed * (float(rand()) / float(RAND_MAX));
			createTime = 0.f;
			return true;
		}
	}
	return false;
}

bool CSnow::CreateMark(Point*& snow)
{
	for (int i = 0; i < MAX_MARK; ++i)
	{
		if (m_mark[i] == NULL)
		{
			m_mark[i] = new Point();
			m_mark[i]->xPos = snow->xPos;
			m_mark[i]->yPos = snow->yPos;
			m_mark[i]->zPos = snow->zPos;
			m_mark[i]->colR = 1.f;
			return true;
		}
	}
	return false;
}
