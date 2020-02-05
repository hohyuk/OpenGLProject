#include "stdafx.h"
#include "CShape19.h"
CShape::CShape()
{
}


CShape::~CShape()
{
}

void CShape::init()
{
	m_Info = Point(0.f, 0.f, 0.f);
	m_Translate = Point(0.f, 0.f, 0.f);
	m_Rotate = Point(0.f, 0.f, 0.f);
	m_Camera = Point(0.f, 10.f, 0.f);
	m_middle = Point(0.f, 0.f, 0.f);
	m_top = Point(0.f, 0.f, 0.f);
	m_move = 1.f;
	m_rad = 10.f;
	m_Angle = 360 / (2 * m_rad);
}

void CShape::run()
{
}

void CShape::render()
{
	gluLookAt(m_Camera.xPos, m_Camera.yPos, m_Camera.zPos, m_Camera.xPos, 0, -10 + m_Camera.zPos, 0, 1, 0);
	coordinates();
	ground();

	// 0. 바닥
	glTranslatef(0, 40, 0);
	// 1.이동하는 중점을 정한다.
	glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
	// 2. y축으로 이동시킨다.
	glRotatef(m_Rotate.yPos, 0, 1, 0);

	roolsphere(0,0,-20);		// 왼쪽 바퀴
	roolsphere(0,0, 20);		// 오른쪽 바퀴
	bottomrect();				// bottom

	middlerect();

	toprect();
}

void CShape::reshape(int w, int h)
{
}

void CShape::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':case 'I':
		init();
		break;
	case 'q':case 'Q':
		glutLeaveMainLoop();
		break;
	case 'x':case 'X':
		break;
	case 'y':case 'Y':
		break;
	case 'z':case 'Z':
		break;
		// 카메라 이동
	case 'a':
		m_Camera.xPos -= m_move;
		break;
	case 'd':
		m_Camera.xPos += m_move;
		break;
	case 'w':
		m_Camera.zPos -= m_move;
		break;
	case 's':
		m_Camera.zPos += m_move;
		break;
	case 'o':
		m_Camera.yPos += m_move;		// 멀리 이동.
		break;
	case 'p':
		m_Camera.yPos -= m_move;		// 화면 쪽으로 이동
		break;
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
	{

		if (m_Translate.xPos > -150)
		{
			m_Translate.xPos -= cos(m_Rotate.yPos*m_PI / 180);
			m_Translate.zPos -= -sin(m_Rotate.yPos*m_PI / 180);
		}
		if (m_Rotate.zPos > 360)
			m_Rotate.zPos = 0.f;
		m_Rotate.zPos += m_Angle*cos(m_Rotate.yPos*m_PI / 180);
		cout << m_Translate.xPos << endl;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (m_Translate.xPos < 150)
		{
			m_Translate.xPos += cos(m_Rotate.yPos*m_PI/180)*1;
			m_Translate.zPos += -sin(m_Rotate.yPos*m_PI / 180);
		}
			
		if (m_Rotate.zPos < 0)
			m_Rotate.zPos = 360.f;
		m_Rotate.zPos -= m_Angle*cos(m_Rotate.yPos*m_PI / 180);
		cout << m_Translate.xPos << endl;
	}
	else if (key == GLUT_KEY_UP)
	{
		if (m_Rotate.yPos > 360)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += 1;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (m_Rotate.yPos < 0)
			m_Rotate.yPos = 360.f;
		m_Rotate.yPos -= 1;
	}
}

void CShape::update(int value)
{
	
}

void CShape::coordinates()
{
	// 좌표계
	glPushMatrix();
	{
		glTranslatef(0, 150, 0);
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
	glPopMatrix();
}

void CShape::ground()
{
	glPushMatrix();
	{
		glColor3f(0.4f, 0.4f, 0.f);
		glScalef(30.f, 5.f, 20.f);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CShape::roolsphere(float x, float y, float z)
{

	glColor3f(0.4f, 1.f, 0.4f);

	glPushMatrix();
	{
		glTranslatef(x, y, z);
		// 3. 바퀴의 회전을 시킨다.
		glRotatef(m_Rotate.xPos, 1, 0, 0);
		glRotatef(m_Rotate.zPos, 0, 0, 1);

		glutWireTorus(m_rad / 2.f, m_rad, 20, 20);
		glutWireTeapot(m_rad);
	}
	glPopMatrix();
}

void CShape::bottomrect()
{
	glTranslatef(0.f, m_rad, 0.f);
	glPushMatrix();
	{
		glColor3f(1.f, 0.4f, 0.4f);
		glScalef(5, 4, 3);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CShape::middlerect()
{
	glTranslatef(0.f, m_rad * 2, 0.f);
	glRotatef(m_middle.xPos, 1, 0, 0);
	glRotatef(m_middle.yPos, 0, 1, 0);
	glTranslatef(0.f, (m_rad * 3) / 2, 0.f);
	glPushMatrix();
	{
		glColor3f(4.f, 0.4f, 1.0f);
		glScalef(2, 4, 1);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CShape::toprect()
{
	glTranslatef(0.f, m_rad * 2, 0.f);
	glRotatef(m_top.xPos, 1, 0, 0);
	glRotatef(m_top.zPos, 0, 0, 1);
	glTranslatef(0.f, (m_rad * 3) / 2, 0.f);
	glPushMatrix();
	{
		
		glColor3f(4.f, 1.0f, 1.0f);
		glScalef(1, 3, 0.5);
		glutSolidCube(10);
	}
	glPopMatrix();
}
