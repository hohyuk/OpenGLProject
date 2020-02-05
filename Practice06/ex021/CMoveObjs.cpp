#include "stdafx.h"
#include "CMoveObjs.h"

CMoveObjs::CMoveObjs()
{
}

CMoveObjs::~CMoveObjs()
{
}

void CMoveObjs::init()
{
	m_SphereT = Point(0.f, 0.f, 0.f);
	m_SphereR = Point(0.f, 0.f, 0.f);
	moveSphere = 2 * 15 * m_PI / 360.f;		// 구의 1각도당 스피드.
	angleSphere = -1.f;

	m_Translate = Point(70.f, 0.f, 0.f);
	m_Rotate = Point(0.f, 0.f, 0.f);
	m_middle = Point(0.f, 0.f, 0.f);
	m_top = Point(0.f, 0.f, 0.f);

	b_move = true;
}

void CMoveObjs::run()
{
}

void CMoveObjs::render()
{
	// Sphere
	sphere_draw();

	// Car
	glPushMatrix();
	{
		// 1. 이동하는 중점
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		glRotatef(m_Rotate.yPos, 0, 1, 0);
		wheel(-10,0,-10);
		wheel(-10, 0, 10);
		wheel(10, 0, -10);
		wheel(10, 0, 10);

		bottomrect();
		middlerect();
		toprect();
	}
	glPopMatrix();
}

void CMoveObjs::reshape(int w, int h)
{
}

void CMoveObjs::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// middle
	case 'v':
		if (m_middle.xPos > -90)
			m_middle.xPos -= 5;
		cout << m_middle.xPos << endl;
		break;
	case 'b':
		if (m_middle.xPos < 90)
			m_middle.xPos += 5;
		cout << m_middle.xPos << endl;
		break;
	case 'n':
		if (m_middle.yPos > 360)
			m_middle.yPos = 0;
		m_middle.yPos += 1.5f;
		cout << m_middle.yPos << endl;
		break;
	case 'm':
		if (m_middle.yPos < 0)
			m_middle.yPos = 360;
		m_middle.yPos -= 1.5f;
		cout << m_middle.yPos << endl;
		break;
		// top
	case 'h':
		if (m_top.xPos > -90)
			m_top.xPos -= 5;
		cout << m_top.xPos << endl;
		break;
	case 'j':
		if (m_top.xPos < 90)
			m_top.xPos += 5;
		cout << m_top.xPos << endl;
		break;
	case 'k':
		if (m_top.zPos < 90)
			m_top.zPos += 1.5f;
		cout << m_top.zPos << endl;
		break;
	case 'l':
		if (m_top.zPos > -90)
			m_top.zPos -= 1.5f;

		cout << m_top.zPos << endl;
		break;
	}
}

void CMoveObjs::mouse(int button, int state, int x, int y)
{
}

void CMoveObjs::motion(int x, int y)
{
}

void CMoveObjs::freemotion(int x, int y)
{
}

void CMoveObjs::special(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		init();
	}
	else if (key == GLUT_KEY_UP)
	{
		
		if (m_Translate.xPos < 90)
		{
			m_Translate.xPos += cosf(m_Rotate.yPos*m_PI / 180);
			m_Translate.zPos += -sin(m_Rotate.yPos*m_PI / 180);
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (m_Translate.xPos > -90)
		{
			m_Translate.xPos -= cosf(m_Rotate.yPos*m_PI / 180);
			m_Translate.zPos -= -sin(m_Rotate.yPos*m_PI / 180);
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (m_Rotate.yPos < 0.f)
			m_Rotate.yPos = 360.f;
		m_Rotate.yPos -= 5.f;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (m_Rotate.yPos > 360.f)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += 5.f;
	}
}

void CMoveObjs::update(int value)
{
	
	if(Collision())
		sphere_move();
}

void CMoveObjs::sphere_draw()
{
	glPushMatrix();
	{
		glColor3f(0.3f, 0.f, 0.f);
		glTranslatef(m_SphereT.xPos, m_SphereT.yPos, m_SphereT.zPos);
		glRotatef(m_SphereR.zPos, 0, 0, 1);
		glutWireSphere(15, 20, 20);
	}
	glPopMatrix();
}

void CMoveObjs::sphere_move()
{
	if (m_SphereT.xPos > 100)
	{
		moveSphere = -moveSphere;
		angleSphere = -angleSphere;
	}
	else if (m_SphereT.xPos < -100)
	{
		moveSphere = -moveSphere;
		angleSphere = -angleSphere;
	}
	m_SphereT.xPos += moveSphere;
	m_SphereR.zPos += angleSphere;
}

void CMoveObjs::wheel(float x,float y,float z)
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 0.1f);
		glTranslatef(x, y, z);
		glRotatef(m_Rotate.xPos, 1, 0, 0);
		glRotatef(m_Rotate.zPos, 0, 0, 1);
		glutWireTorus(3, 3, 20, 20);
	}
	glPopMatrix();
}

void CMoveObjs::bottomrect()
{
	glTranslatef(0.f, 10.f, 0.f);
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.f);
		glScalef(3, 2, 2);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CMoveObjs::middlerect()
{
	glTranslatef(0.f, 15.f, 0.f);
	glRotatef(m_middle.xPos, 1, 0, 0);
	glRotatef(m_middle.yPos, 0, 1, 0);
	glTranslatef(0.f, 12.f/2, 0.f);
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 1.0f);
		glScalef(1, 2, 1);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CMoveObjs::toprect()
{
	glTranslatef(0.f,10.f, 0.f);
	glRotatef(m_top.xPos, 1, 0, 0);
	glRotatef(m_top.zPos, 0, 0, 1);
	glTranslatef(0.f, 5.f/2, 0.f);
	glPushMatrix();
	{
		glColor3f(0.f, 1.f, 0.f);
		glScalef(0.5f, 1.f, 0.5f);
		glutSolidCube(10);
	}
	glPopMatrix();
}

bool CMoveObjs::Collision()
{
	float x = m_Translate.xPos - m_SphereT.xPos;
	float z = m_Translate.zPos - m_SphereT.zPos;
	float fDistance = sqrtf((x*x) + (z*z));

	if (fDistance < 30)
	{
		return false;
	}
	
	return true;
}
