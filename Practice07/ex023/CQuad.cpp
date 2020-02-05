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
	m_Rotate = Point(30, 45, 0);
	m_Size = 100.f;
	m_Shade = GL_SMOOTH;
	isDepth = true;
	isCulling = true;
	m_Angle = 0.f;
	topAngle = 0.f;
	frontAngle = 0.f;
	isTopOpen = false;
	isfrontOpen = false;
}

void CQuad::update(int value)
{
	m_Angle += 1.f;
	if (m_Angle > 360)
		m_Angle = 0.f;

	if (isTopOpen)
	{
		if (topAngle < 90.f)
			topAngle += 1.f;
	}
	else
	{
		if (topAngle > 0)
			topAngle -= 1.f;
	}
	if (isfrontOpen)
	{
		if (frontAngle < 90.f)
			frontAngle += 1.f;
	}
	else
	{
		if (frontAngle > 0)
			frontAngle -= 1.f;
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
	cube();
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
	case '5':
		isTopOpen = !isTopOpen;
		break;
	case '6':
		isfrontOpen = !isfrontOpen;
		break;
	}
}

void CQuad::mouse(int button, int state, int x, int y)
{
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

void CQuad::cube()
{
	// 앞면
	glPushMatrix();
	{
		float Pos = 100;
		glTranslatef(Pos, 0, Pos);
		glRotatef(frontAngle, 0, 1, 0);
		glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
		glBegin(GL_QUADS);
		{
			glColor3f(1.0f, 1.0f, 0.0f); // Yellow
			glVertex3f(m_Size - Pos, m_Size, m_Size - Pos);
			glColor3f(1.0f, 0.0, 1.0f); // Magenta
			glVertex3f(-m_Size - Pos, m_Size, m_Size - Pos);
			glColor3f(0.0f, 1.0f, 1.0f); // Cyan
			glVertex3f(-m_Size - Pos, -m_Size, m_Size - Pos);
			glColor3f(0.0f, 0.0f, 1.0f); // Blue
			glVertex3f(m_Size - Pos, -m_Size, m_Size - Pos);
		}
		glEnd();
	}
	glPopMatrix();
	// 뒷면
	glFrontFace(GL_CW);
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
	glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
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
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
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
	glPushMatrix();
	{
		float Pos = 100;
		glTranslatef(Pos, Pos, 0);
		glRotatef(-topAngle, 0, 0, 1);
		//glTranslatef(xPos, 0, 0);
		
		
		glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
		glBegin(GL_QUADS);
		{
			glColor3f(0.f, 0.5f, 0.f);
			glVertex3f(m_Size - Pos, m_Size - Pos, m_Size);
			glColor3f(0.7f, 0.3f, 0.f);
			glVertex3f(m_Size - Pos, m_Size - Pos, -m_Size);
			glColor3f(1.f, 0.f, 0.3f);
			glVertex3f(-m_Size - Pos, m_Size - Pos, -m_Size);
			glColor3f(0.4f, 0.2f, 0.5f);
			glVertex3f(-m_Size - Pos, m_Size - Pos, m_Size);
		}
		glEnd();
	}
	glPopMatrix();
	// 아랫면
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBegin(GL_QUADS);
	{
		glColor3f(0.f, 0.5f, 0.f);
		glVertex3f(m_Size, -m_Size, m_Size);
		glColor3f(0.7f, 0.3f, 0.f);
		glVertex3f(m_Size, -m_Size, -m_Size);
		glColor3f(1.f, 0.f, 0.3f);
		glVertex3f(-m_Size, -m_Size, -m_Size);
		glColor3f(0.4f, 0.2f, 0.5f);
		glVertex3f(-m_Size, -m_Size, m_Size);
	}
	glEnd();
}
