#include "stdafx.h"
#include "CQuad.h"

CQuad::CQuad()
{
}


CQuad::~CQuad()
{
}

void CQuad::init()
{
	m_Rotate = Point(0, 0, 0);
	m_Size = SPACE;

	curtainPosY = 0;
	isOpen = true;
	
	m_Shade = GL_SMOOTH;
	isDepth = true;
	isCulling = true;
	m_Angle = 0.f;

}

void CQuad::update(int value)
{
	if (isOpen)
	{
		if (curtainPosY < 200.f)
			curtainPosY += 5.f;
	}
	else
	{
		if (curtainPosY > 0.f)
			curtainPosY -= 5.f;
	}
}

void CQuad::render()
{
	
	// 쉐이딩
	glShadeModel(m_Shade); // 또는 glShadeModel (GL_FLAT)
	// 은면 제거
	if (isDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// 컬링
	if (isCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// 정육면체 그리기.
	glRotatef(m_Rotate.xPos, 1, 0, 0);
	glRotatef(m_Rotate.yPos + m_Angle, 0, 1, 0);
	glRotatef(m_Rotate.zPos, 0, 0, 1);

	cubeSpace();

}

void CQuad::reshape(int w, int h)
{
}

void CQuad::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		m_Shade = GL_SMOOTH;
		break;
	case '2':
		m_Shade = GL_FLAT;
		break;
	case '3':
		isDepth = !isDepth;
		break;
	case '4':
		isCulling = !isCulling;
		break;
	case 'o':
		isOpen = !isOpen;
		break;
	case 'c':
		m_Rotate.zPos += 1.f;
		cout << m_Rotate.zPos << endl;
		break;
	case 'i':
		init();
		break;
	}
}

void CQuad::mouse(int button, int state, int x, int y)
{
	//isButtonOn = button == GLUT_DOWN &&state == GLUT_LEFT_BUTTON;
	if (button == GLUT_DOWN &&state == GLUT_LEFT_BUTTON)
	{
		
	}
}

void CQuad::motion(int x, int y)
{
	
}

void CQuad::freemotion(int x, int y)
{
}

void CQuad::special(int key, int x, int y)
{
}

void CQuad::run()
{
	
}

void CQuad::cubeSpace()
{
	// 앞면
	glPushMatrix();
	{
		glTranslatef(0, curtainPosY, 0);
		glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
		glBegin(GL_QUADS);
		{
			glColor3f(1.0f, 1.0f, 0.0f); // Yellow
			glVertex3f(m_Size, m_Size, m_Size);
			glColor3f(1.0f, 0.0, 1.0f); // Magenta
			glVertex3f(-m_Size, m_Size, m_Size);
			glColor3f(0.0f, 1.0f, 1.0f); // Cyan
			glVertex3f(-m_Size, -m_Size, m_Size);
			glColor3f(0.0f, 0.0f, 1.0f); // Blue
			glVertex3f(m_Size, -m_Size, m_Size);
		}
		glEnd();
	}
	glPopMatrix();
	
	// 뒷면
	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(m_Size, m_Size, -m_Size);
		glColor3f(0.0f, 1.0f, 1.0f); // Cyan
		glVertex3f(-m_Size, m_Size, -m_Size);
		glColor3f(1.0f, 0.0, 1.0f); // Magenta
		glVertex3f(-m_Size, -m_Size, -m_Size);
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(m_Size, -m_Size, -m_Size);
	}
	glEnd();
	// 왼쪽면
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f); 
		glVertex3f(-m_Size, m_Size, m_Size);
		glColor3f(0.0f, 0.0, 1.0f); 
		glVertex3f(-m_Size, m_Size, -m_Size);
		glColor3f(0.0f, 1.0f, 0.0f); 
		glVertex3f(-m_Size, -m_Size, -m_Size);
		glColor3f(1.0f, 0.0f, 1.0f); 
		glVertex3f(-m_Size, -m_Size, m_Size);
	}
	glEnd();
	// 오른쪽면
	glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBegin(GL_QUADS);
	{
		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(m_Size, m_Size, m_Size);
		glColor3f(1.f, 0.f, 1.f);
		glVertex3f(m_Size, m_Size, -m_Size);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(m_Size, -m_Size, -m_Size);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_Size, -m_Size, m_Size);
	}
	glEnd();

	// 윗면
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBegin(GL_QUADS);
	{
		glColor3f(0.f, 0.5f, 0.f);
		glVertex3f(m_Size, m_Size, m_Size);
		glColor3f(0.7f, 0.3f, 0.f);
		glVertex3f(m_Size, m_Size, -m_Size);
		glColor3f(1.f, 0.f, 0.3f);
		glVertex3f(-m_Size, m_Size, -m_Size);
		glColor3f(0.4f, 0.2f, 0.5f);
		glVertex3f(-m_Size, m_Size, m_Size);
	}
	glEnd();

	// 아랫면
	glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBegin(GL_QUADS);
	{
		glColor3f(0.f, 2.f, 0.2f);
		glVertex3f(m_Size, -m_Size, m_Size);
		glColor3f(0.3f, 0.3f, 0.3f);
		glVertex3f(m_Size, -m_Size, -m_Size);
		glColor3f(0.5f, 0.f, 0.3f);
		glVertex3f(-m_Size, -m_Size, -m_Size);
		glColor3f(0.f, 0.2f, 0.2f);
		glVertex3f(-m_Size, -m_Size, m_Size);
	}
	glEnd();
}
