#include "stdafx.h"
#include "CAirplane.h"

CAirplane::CAirplane()
{
}

CAirplane::~CAirplane()
{
}

void CAirplane::init()
{
	m_Translate = Point{ 0.f,100.f,0.f };
	m_Angle = 0.f;
	rotorAngle = 0.f;
	airAngle = 0.f;
	engineAngle = 0.f;
	m_Color.colR = float((rand() % 255) / 255);
	m_Color.colG = float((rand() % 255) / 255);
	m_Color.colB = float((rand() % 255) / 255);
}

void CAirplane::run()
{
}

void CAirplane::render()
{
	
	glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
	glRotatef(m_Angle+90, 0, 1, 0);
	glRotatef(airAngle, 1, 0, 0);
	airplanebody();
	airplanehead();
	airplanewing(-5, 0, 5,0);		// 오른쪽 날개
	airplanewing(-5, 0, -5, 180);	// 왼쪽 날개
	airplanetail(-6, 0, 2);
	airplanetail(-6, 0, -2);
}

void CAirplane::reshape(int w, int h)
{
}

void CAirplane::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'o':
		if (airAngle > 360.f)
			airAngle = 0.f;
		airAngle += 5.f;
		break;
	case 'p':
		if (airAngle < 0.f)
			airAngle = 360.f;
		airAngle -= 5.f;
		break;
	}
}

void CAirplane::mouse(int button, int state, int x, int y)
{

}

void CAirplane::motion(int x, int y)
{
}

void CAirplane::freemotion(int x, int y)
{
}

void CAirplane::special(int key, int x, int y)
{
}

void CAirplane::update(int value)
{
	colorupdate();
	// 회전 날개
	if (rotorAngle > 360.f)
		rotorAngle = 0.f;
	rotorAngle += 5.f;

	// 비행기 움직임
	if (m_Angle > 360)
		m_Angle = 0;
	m_Angle += 0.5f;
	m_Translate.xPos = 100 * cosf(m_Angle*m_PI/180);
	m_Translate.zPos = 100 * (-sin(m_Angle*m_PI/180));
	

	// 엔진
	if (engineAngle > 360)
		engineAngle = 0.f;
	engineAngle += 5.f;
}

void CAirplane::airplanebody()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.f);
		glScalef(1.5f, 1.f, 1.f);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void CAirplane::airplanehead()
{
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 0.f);
		glTranslatef(8, 0, 0);
		glRotated(90, 0, 1, 0);
		glutSolidCone(5,10,20,20);

		// 회전 날개
		airplanerotor();
	}
	glPopMatrix();
}

void CAirplane::airplanewing(float x, float y, float z, float angle)
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.5f, 0.f);
		glTranslatef(x, y, z);
		glRotated(angle, 0, 1, 0);
		glRotated(angle, 0, 0, 1);
		glutSolidCone(5, 15, 3, 5);
	}
	glPopMatrix();
}

void CAirplane::airplanerotor()
{
	
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 1.f);
		glTranslatef(0.f, 0.f, 10.f);
		glRotatef(rotorAngle, 0, 0, 1);
		glScalef(5.f, 1.f, 1.f);
		
		glutSolidCube(2);
	}
	glPopMatrix();
}

void CAirplane::airplanetail(float x, float y, float z)
{
	glPushMatrix();
	{
		glColor3f(0.5,0.5,0.5);
		glTranslatef(x, y, z);
		glRotated(-90, 0, 1, 0);
		glutSolidCone(2, 10, 20, 20);

		airplaneengle(1, 20, engineAngle, 3);
	}
	glPopMatrix();
}

void CAirplane::airplaneengle(float scale, float pos, float& angle, int count_)
{
	if (count_ != 0)
	{
		glPushMatrix();
		{
			glColor3f(m_Color.colR, m_Color.colG, m_Color.colB);

			glTranslatef(0, 0, pos);
			glRotatef(angle, 0, 0, 1);
			glScalef(scale, scale, scale);
			glBegin(GL_POLYGON);
			{
				glVertex3f(0.f, 0.f, -10.f);
				glVertex3f(4.f, 0.f, -5.f);
				glVertex3f(2.f, 0.f, 0.f);
				glVertex3f(-2.f, 0.f, 0.f);
				glVertex3f(-4.f, 0.f, -5.f);
			}
			glEnd();
			airplaneengle(scale / 2, 10, angle, count_ - 1);
		}
		glPopMatrix();
	}
	
}

void CAirplane::colorupdate()
{
	m_Color.colR = float(rand() % 255) / 255;
	m_Color.colG = float(rand() % 255) / 255;
	m_Color.colB = float(rand() % 255) / 255;
}
