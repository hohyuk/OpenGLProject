#include "CRobot.h"

CRobot::CRobot()
{
}

CRobot::~CRobot()
{
}

void CRobot::init()
{
	m_Translate = Point(0, 0, 0);
	m_Rotate = Point(0, 0, 0);
	m_Translate.xSpeed = m_Translate.ySpeed = m_Translate.zSpeed = 1.f;
	m_Translate.xDir = m_Translate.yDir = m_Translate.zDir = 0.f;
	isJump = false;
	angleX = 0.5f;
}

void CRobot::update(int value)
{
	// limit_space
	float limit_space = SPACE - 25;
	if (m_Translate.xPos > limit_space)
	{
		m_Translate.xPos = limit_space;
	}
	else if (m_Translate.xPos < -limit_space)
	{
		m_Translate.xPos = -limit_space;
	}

	if (m_Translate.zPos > limit_space)
	{
		m_Translate.zPos = limit_space;
	}
	else if (m_Translate.zPos < -limit_space)
	{
		m_Translate.zPos = -limit_space;
	}
	
	// jump
	float bottom = -SPACE + 70;

	if (isJump)
	{
		m_Translate.yDir = 1;
		if (m_Translate.yPos > 0)
			isJump = false;
	}
	else
	{
		if (m_Translate.yPos > bottom)
			m_Translate.yDir = -1;
		else
			m_Translate.yDir = 0;
	}
	
	// rotate
	
	if (m_Rotate.xPos > 15.f)
		angleX = -angleX;
	else if (m_Rotate.xPos < -15.f)
		angleX = -angleX;
	m_Rotate.xPos += angleX;
	// move
	if (m_Translate.yDir == 0)
	{
		m_Translate.xPos += (m_Translate.xSpeed * m_Translate.xDir);
		m_Translate.zPos += (m_Translate.zSpeed * m_Translate.zDir);
	}
	else
		m_Translate.yPos += (m_Translate.ySpeed * m_Translate.yDir);
	
}

void CRobot::render()
{
	robot_body();
}

void CRobot::reshape(int w, int h)
{
}

void CRobot::keyboard(unsigned char key, int x, int y)
{
	if (key == 'j')
	{
		isJump = true;
	}
	else if (key == 'i')
	{
		init();
	}
}

void CRobot::mouse(int button, int state, int x, int y)
{
}

void CRobot::motion(int x, int y)
{
}

void CRobot::freemotion(int x, int y)
{
}

void CRobot::special(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		m_Translate.xDir = 1;
		m_Translate.zDir = 0;
		m_Rotate.yPos = 90.f;
	}
	if (key == GLUT_KEY_LEFT)
	{
		m_Translate.xDir = -1;
		m_Translate.zDir = 0;
		m_Rotate.yPos = -90.f;

	}
	if (key == GLUT_KEY_UP)
	{
		m_Translate.zDir = -1;
		m_Translate.xDir = 0;
		m_Rotate.yPos = 180.f;

	}
	if (key == GLUT_KEY_DOWN)
	{
		m_Translate.zDir = 1;
		m_Translate.xDir = 0;
		m_Rotate.yPos = 0.f;

	}
}

void CRobot::run()
{
}

void CRobot::robot_body()
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.5f, 0.5f);
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		glRotatef(m_Rotate.yPos, 0, 1, 0);
		glScalef(1.5f, 2.f, 1.f);
		glutSolidCube(30);

		// Scale init 
		glScalef(1 / 1.5f, 1 / 2.f, 1.f);
		robot_head();
		robot_leg();
		robot_upper_limb();
	}
	glPopMatrix();
}

void CRobot::robot_head()
{
	glPushMatrix();
	{
		glColor3f(0.5f, 0.f, 0.5f);
		glTranslatef(0.f, 45.f, 0.f);
		glutSolidCube(30);

		// ÄÚ
		glColor3f(0.7f, 0.7f, 0.f);
		glTranslatef(0.f, 0.f, 15.f);
		glutSolidCube(5);
	}
	glPopMatrix();
}

void CRobot::robot_leg()
{
	glPushMatrix();
	{
		// Left
		glPushMatrix();
		{
			glColor3f(0.f, 1.f, 0.f);
			glRotatef(m_Rotate.xPos, 1, 0, 0);
			glTranslatef(-10.f, -50.f, 0.f);
			
			glScalef(0.7f, 2.f, 0.7f);
			glutSolidCube(20);
		}
		glPopMatrix();

		// Right
		glPushMatrix();
		{
			glColor3f(0.f, 0.f, 1.f);
			glRotatef(-m_Rotate.xPos, 1, 0, 0);
			glTranslatef(10.f, -50.f, 0.f);
			
			glScalef(0.7f, 2.f, 0.7f);
			glutSolidCube(20);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CRobot::robot_upper_limb()
{
	glPushMatrix();
	{
		// Left
		glPushMatrix();
		{
			glColor3f(0.f, 0.f, 0.7f);
			glTranslatef(-28.f, 20.f, 0.f);
			glRotatef(-m_Rotate.xPos, 1, 0, 0);
			glTranslatef(0.f, -10.f, 0.f);
			glScalef(0.5f, 2.f, 0.5f);
			glutSolidCube(20);
		}
		glPopMatrix();

		// Right
		glPushMatrix();
		{
			glColor3f(0.f, 0.7f, 0.f);
			glTranslatef(28.f, 20.f, 0.f);
			glRotatef(m_Rotate.xPos, 1, 0, 0);
			glTranslatef(0.f, -10.f, 0.f);
			glScalef(0.5f, 2.f, 0.5f);
			glutSolidCube(20);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
