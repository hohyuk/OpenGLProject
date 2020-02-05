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
	m_Rotate = Point(0, 45, 0);
	m_Size = 100.f;
	m_Shade = GL_SMOOTH;
	isDepth = true;
	isCulling = true;
	m_Angle = 0.f;
	// ball
	ballradian = 5.f;
	ballSpeed = 5.f;

	for (int i = 0; i < MAX_BALL; ++i)
	{
		m_ball[i] = NULL;
	}
	for (int i = 0; i < MAX_CUBE; ++i)
	{
		float size = 10 * ((float)i + 1);
		m_cube[i] = NULL;
		m_cube[i] = new Cube(0.f, 0.f, -50.f + ((float)i*50.f));
		m_cube[i]->Size = size;
		m_cube[i]->colR = float(rand() % 255) / 255.f;
		m_cube[i]->colG = float(rand() % 255) / 255.f;
		m_cube[i]->colB = float(rand() % 255) / 255.f;
	}
	isButtonOn = false;
}

void CQuad::update(int value)
{
	moveBall();
	moveCube();
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

	// ball 
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (m_ball[i] != NULL)
		{
			glPushMatrix();
			{
				glColor3f(m_ball[i]->colR, m_ball[i]->colG, m_ball[i]->colB);
				glTranslatef(m_ball[i]->xPos, m_ball[i]->yPos, m_ball[i]->zPos);
				glutSolidSphere(ballradian,10,10);
			}
			glPopMatrix();
		}
	}
	
	// cube
	for (int i = 0; i < MAX_CUBE; ++i)
	{
		if (m_cube[i] != NULL)
		{
			glPushMatrix();
			{
				glColor3f(m_cube[i]->colR, m_cube[i]->colG, m_cube[i]->colB);
				glTranslatef(m_cube[i]->xPos, m_cube[i]->yPos, m_cube[i]->zPos);
				glutSolidCube(m_cube[i]->Size);
			}
			glPopMatrix();
		}
	}
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
	case 'b':
		createBall();
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
		isButtonOn = true;
	}
}

void CQuad::motion(int x, int y)
{
	if (isButtonOn)
	{
		if (x > WinX / 2)
			m_Rotate.zPos -= 1.f;
		else if (x < WinX / 2)
			m_Rotate.zPos += 1.f;
		cout << m_Rotate.zPos << endl;
	}
}

void CQuad::freemotion(int x, int y)
{
}

void CQuad::special(int key, int x, int y)
{
}

void CQuad::run()
{
	for (int i = 0; i < MAX_BALL; ++i)
	{
		delete m_ball[i];
		m_ball[i] = NULL;
	}
}

void CQuad::cubeSpace()
{
	// 앞면
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
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

int CQuad::createBall()
{
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (m_ball[i] == NULL)
		{
			m_ball[i] = new Point();
			m_ball[i]->xPos = float(rand() % ((int)m_Size * 2)) - m_Size;
			m_ball[i]->yPos = float(rand() % ((int)m_Size * 2)) - m_Size;
			m_ball[i]->zPos = float(rand() % ((int)m_Size * 2)) - m_Size;
			m_ball[i]->colR = float(rand() % 255) / 255.f;
			m_ball[i]->colG = float(rand() % 255) / 255.f;
			m_ball[i]->colB = float(rand() % 255) / 255.f;
			m_ball[i]->xMove = ballSpeed * (float(rand()) / float(RAND_MAX)) - 0.5f;
			m_ball[i]->yMove = ballSpeed * (float(rand()) / float(RAND_MAX)) - 0.5f;
			m_ball[i]->zMove = ballSpeed * (float(rand()) / float(RAND_MAX)) - 0.5f;

			return i;
		}
	}

	cout << "ball is full... " << endl;
	return -1;
}

void CQuad::moveBall()
{
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (m_ball[i] != NULL)
		{
			if (m_ball[i]->xPos > m_Size - ballradian)
				m_ball[i]->xMove = -m_ball[i]->xMove;
			else if (m_ball[i]->xPos < -m_Size + ballradian)
				m_ball[i]->xMove = -m_ball[i]->xMove;

			if (m_ball[i]->yPos > m_Size - ballradian)
				m_ball[i]->yMove = -m_ball[i]->yMove;
			else if (m_ball[i]->yPos < -m_Size + ballradian)
				m_ball[i]->yMove = -m_ball[i]->yMove;

			if (m_ball[i]->zPos > m_Size - ballradian)
				m_ball[i]->zMove = -m_ball[i]->zMove;
			else if (m_ball[i]->zPos < -m_Size + ballradian)
				m_ball[i]->zMove = -m_ball[i]->zMove;

			m_ball[i]->xPos += m_ball[i]->xMove;
			m_ball[i]->yPos += m_ball[i]->yMove;
			m_ball[i]->zPos += m_ball[i]->zMove;
		}
	}
}

void CQuad::moveCube()
{
	// 왼쪽 오른쪽 회전
	if (m_Rotate.zPos > 360.f)
		m_Rotate.zPos = 0.f;
	else if (m_Rotate.zPos < 0)
		m_Rotate.zPos = 360.f;

	for (int i = 0; i < MAX_CUBE; ++i)
	{
		float top = m_Size - (m_cube[i]->Size / 2.f);
		float bottom = (-m_Size + (m_cube[i]->Size / 2.f));
		if (m_cube[i] != NULL)
		{
			if (m_Rotate.zPos >= 0 && m_Rotate.zPos < 90)
			{
				if (m_cube[i]->yPos >bottom)
					m_cube[i]->yPos -= 1.f;

				if (m_Rotate.zPos != 0 && m_cube[i]->xPos > bottom)
					m_cube[i]->xPos -= 1.f;
			}
			else if (m_Rotate.zPos >= 90 && m_Rotate.zPos < 180)
			{
				if (m_cube[i]->xPos > bottom)
					m_cube[i]->xPos -= 1.f;
				if (m_Rotate.zPos != 90 && m_cube[i]->yPos < top)
					m_cube[i]->yPos += 1.f;
			}
			else if (m_Rotate.zPos >= 180 && m_Rotate.zPos < 270)
			{
				if (m_cube[i]->yPos < top)
					m_cube[i]->yPos += 1.f;
				if (m_Rotate.zPos != 180 && m_cube[i]->xPos < top)
					m_cube[i]->xPos += 1.f;
			}
			else if (m_Rotate.zPos >= 270 && m_Rotate.zPos < 360)
			{
				if (m_cube[i]->xPos < top)
					m_cube[i]->xPos += 1.f;
				if (m_Rotate.zPos != 270 && m_cube[i]->yPos > bottom)
					m_cube[i]->yPos -= 1.f;
			}
		}
	}
}
