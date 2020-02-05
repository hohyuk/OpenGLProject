#include "CTorus.h"



CTorus::CTorus()
{
}


CTorus::~CTorus()
{
}

void CTorus::init()
{
	m_initTrans = Point(0.f, -50.f, 0.f);
	memset(m_mat, 0, sizeof(m_mat));
	m_mat[0] = m_mat[5] = m_mat[10] = m_mat[15] = 1;

	// torus 좌표값을 x축 90도로 바꾸고 초기화한다.
	glPushMatrix();
	{
		glRotatef(90, 1, 0, 0);
		glMultMatrixf(m_mat);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
	}
	glPopMatrix();

	torusInit();
	torusRadIN = 10;

	isDepth = false;
}

void CTorus::update(int value)
{
	// 바닥면. -150
	float floor = -((-m_initTrans.yPos * 2 - m_initTrans.yPos) - 15) + torusHeight;
	if (Count < MAX_COUNT)
	{
		if (m_Torus[Count] == NULL)
		{
			createTorus(Count);
		}
		else
		{
			if (m_Torus[Count]->yPos > floor)
			{
				m_Torus[Count]->yPos -= 0.5f;
				m_TorusR[Count]->yPos += 1.f;
			}
			else
			{
				if (m_Torus[Count]->xPos > 0.f)
					m_Torus[Count]->xPos -= 1.f;
				else
					isArrival[Count++] = true;
			}
		}
	}
	else
	{
		deleteTorus();
	}
	
}

void CTorus::render()
{
	glTranslatef(m_initTrans.xPos, m_initTrans.yPos, m_initTrans.zPos);
	floor();
	pillar();
	toruses();
}

void CTorus::reshape(int w, int h)
{
}

void CTorus::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		isDepth = !isDepth;
		break;
	}
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

void CTorus::run()
{
}

void CTorus::torusInit()
{
	Count = 0;
	torusHeight = 0;
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		m_Torus[i] = NULL;
		m_TorusR[i] = NULL;
		isArrival[i] = false;
	}
}

void CTorus::createTorus(int count)
{
	m_Torus[count] = new Point(30, 0, 0);
	m_TorusR[count] = new Point(0, 0, 0);
	torusHeight += (torusRadIN * 2);
}

void CTorus::deleteTorus()
{
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		delete m_Torus[i];
		delete m_TorusR[i];
		torusHeight = 0;
	}
	torusInit();
}

void CTorus::floor()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.5f, 0.f);
		glScalef(5, 1, 5);
		glutSolidCube(50);
	}
	glPopMatrix();
}

void CTorus::pillar()
{
	glTranslatef(0, -m_initTrans.yPos * 2, 0);
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.f);
		glScalef(1, 30, 1);
		glutSolidCube(5);
	}
	glPopMatrix();
}

void CTorus::toruses()
{
	if (isDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Torus[i] != NULL)
		{
			glPushMatrix();
			{
				glRotatef(m_TorusR[i]->yPos, 0, 1, 0);
				glTranslatef(m_Torus[i]->xPos, m_Torus[i]->yPos - m_initTrans.yPos, m_Torus[i]->zPos);

				glMultMatrixf(m_mat);
				if (isArrival[i])
				{
					glutSolidTorus(torusRadIN, 50, 30, 30);
				}
				else
				{
					glutWireTorus(torusRadIN, 50, 30, 30);
				}
			}
			glPopMatrix();
		}
	}
}
