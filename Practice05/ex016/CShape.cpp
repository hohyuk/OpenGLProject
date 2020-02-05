#include "stdafx.h"
#include "CShape.h"



CShape::CShape()
{
}


CShape::~CShape()
{
}

void CShape::init()
{
	m_Rotate = Point(0.f, 0.f, 0.f);
	m_Translate = Point(0.f, 0.f, 0.f);
	m_leftR = Point(0.f, 0.f, 0.f);
	m_rightR = Point(0.f, 0.f, 0.f);
	m_Angle = 5.f;
	rand_left = 0;		// 0Àº ¸ØÃã.
	rand_right = 0;
	shape = E_Cube;
	m_Camera = Point(0.f, 0.f, 0.f);
}

void CShape::run()
{
}

void CShape::render()
{
	gluLookAt(0, 0, 500, m_Camera.xPos, m_Camera.yPos, -100, 0, 1, 0);
	coordinates();
	ground();
	leftshape();
	rightshape();
}

void CShape::reshape(int w, int h)
{
}

void CShape::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': case 'X':
		if (m_Rotate.xPos > 360.f)
			m_Rotate.xPos = 0.f;
		m_Rotate.xPos += m_Angle;
		break;
	case 'y': case 'Y':
		if (m_Rotate.yPos > 360.f)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += m_Angle;
		break;
	case 'z': case 'Z':
		if (m_Rotate.zPos > 360.f)
			m_Rotate.zPos = 0.f;
		m_Rotate.zPos += m_Angle;
		break;
	case 'i': case 'I':
		init();
		break;
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	case 'l': case 'L':
		m_leftR = Point(0.f, 0.f, 0.f);
		rand_left = rand() % 3+1;
		break;
	case 'r': case 'R':
		m_rightR = Point(0.f, 0.f, 0.f);
		rand_right = rand() % 3+1;
		break;
	case '1':
		shape = E_Cube;
		break;
	case '2':
		shape = E_Circle;
		break;
	case '3':
		shape = E_Cone;
		break;
	case '4':
		shape = E_Teapot;
		break;
	}
}

void CShape::mouse(int button, int state, int x, int y)
{
}

void CShape::motion(int x, int y)
{
}

void CShape::freemotion(int x, int y)
{
}

void CShape::special(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		m_Camera.xPos += m_Angle;
}

void CShape::update(int value)
{
	if (rand_left == 1)
	{
		if (m_leftR.xPos > 360)
			m_leftR.xPos = 0.f;
		m_leftR.xPos += m_Angle;
	}
	else if (rand_left == 2)
	{
		if (m_leftR.yPos > 360)
			m_leftR.yPos = 0.f;
		m_leftR.yPos += m_Angle;
	}
	else if (rand_left == 3)
	{
		if (m_leftR.zPos > 360)
			m_leftR.zPos = 0.f;
		m_leftR.zPos += m_Angle;
	}

	if (rand_right == 1)
	{
		if (m_rightR.xPos > 360)
			m_rightR.xPos = 0.f;
		m_rightR.xPos += m_Angle;
	}
	else if (rand_right == 2)
	{
		if (m_rightR.yPos > 360)
			m_rightR.yPos = 0.f;
		m_rightR.yPos += m_Angle;
	}
	else if (rand_right == 3)
	{
		if (m_rightR.zPos > 360)
			m_rightR.zPos = 0.f;
		m_rightR.zPos += m_Angle;
	}
}

void CShape::coordinates()
{
	// ÁÂÇ¥°è
	glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
	glRotatef(m_Rotate.xPos, 1.f, 0.f, 0.f);
	glRotatef(m_Rotate.yPos, 0.f, 1.f, 0.f);
	glRotatef(m_Rotate.zPos, 0.f, 0.f, 1.f);
	glBegin(GL_LINES);
	{
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(0, 0, 0);
		glVertex3d(10, 0, 0);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 10, 0);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, 10);
	}
	glEnd();
}

void CShape::ground()
{
	glPushMatrix();
	{
		//glLoadIdentity();
		glColor3f(0.4f, 0.4f, 0.f);
		glTranslatef(0.f, -150.f, 0.f);
		glScalef(30.f, 10.f, 30.f);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CShape::leftshape()
{
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 0.f);
		glTranslatef(-50.f, -60.f, 100.f);
		glRotatef(m_leftR.xPos, 1.f, 0.f, 0.f);
		glRotatef(m_leftR.yPos, 0.f, 1.f, 0.f);
		glRotatef(m_leftR.zPos, 0.f, 0.f, 1.f);
		
		if (shape == E_Cube)
		{
			glScalef(3.f, 8.f, 3.f);
			glutSolidCube(10);
		}
		else if (shape == E_Circle)
		{
			glScalef(2.f, 2.f, 2.f);
			glutSolidSphere(10, 30, 30);
		}
		else if (shape == E_Cone)
		{
			glTranslatef(0.f, -20.f, 0.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			glutSolidCone(20, 50, 20, 20);
		}
		else if (shape == E_Teapot)
		{
			glScalef(2.f, 2.f, 2.f);
			glutSolidTeapot(10);
		}
	}
	glPopMatrix();
}

void CShape::rightshape()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.5f);
		glTranslatef(30.f, -20.f, 200.f);
		glRotatef(m_rightR.xPos, 1.f, 0.f, 0.f);
		glRotatef(m_rightR.yPos, 0.f, 1.f, 0.f);
		glRotatef(m_rightR.zPos, 0.f, 0.f, 1.f);
		
		if (shape == E_Cube)
		{
			glScalef(5.f, 2.f, 2.f);
			glutWireCube(10);
		}
		else if (shape == E_Circle)
		{
			glutWireSphere(10, 20, 20);
		}
		else if (shape == E_Cone)
		{
			glTranslatef(0.f, -20.f, 0.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			glutWireCone(20, 50, 20, 20);
		}
		else if (shape == E_Teapot)
		{
			glRotatef(180, 0.f, 1.f, 0.f);
			glutWireTeapot(10);
		}
	}
	glPopMatrix();
}
