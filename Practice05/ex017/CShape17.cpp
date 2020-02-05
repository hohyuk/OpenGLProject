#include "stdafx.h"
#include "CShape17.h"

CShape::CShape()
{
}


CShape::~CShape()
{
}


void CShape::init()
{
	m_model = E_Wire;
	m_Info = Point(0.f, 0.f, 0.f);
	m_Translate = Point(0.f, 0.f, 0.f);
	m_Rotate = Point(0.f, 0.f, 0.f);
	m_Camera = Point(0.f, 10.f, 0.f);
	m_Angle = 1.f;
	m_move = 0.5f;
	m_mainR = 0.f;
	m_mainSpeed = 0.5f;
	m_co1R = 0.f;
	m_mini1 = 0.f;
	m_co2R = 0.f;
	m_mini2 = 0.f;
	m_co3R = 0.f;
	m_mini3 = 0.f;
}

void CShape::run()
{
}

void CShape::render()
{
	
	coordinates();
	mainsphere();
	course1();
	course2();
	course3();
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
	
	// Model
	case '1':
		m_model = E_Wire;
		break;
	case '2':
		m_model = E_Solid;
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

}

void CShape::update(int value)
{
	// mainSphere 공전
	if (m_mainR > 360)
		m_mainR = 0;
	m_mainR += m_mainSpeed;
	// 경로 1 회전
	if (m_co1R > 360)
		m_co1R = 0;
	m_co1R += 1.f;
	if (m_mini1 > 360)
		m_mini1 = 0;
	m_mini1 += 0.5f;
	// 경로 2 회전
	if (m_co2R > 360)
		m_co2R = 0;
	m_co2R += 0.5f;
	if (m_mini2 > 360)
		m_mini2 = 0;
	m_mini2 += 0.3f;
	// 경로 3 회전
	if (m_co3R > 360)
		m_co3R = 0;
	m_co3R += 0.7f;
	if (m_mini3 > 360)
		m_mini3 = 0;
	m_mini3 += 0.5f;
}

void CShape::coordinates()
{
	// 좌표계
	//glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
	//glRotatef(m_Rotate.xPos, 1.f, 0.f, 0.f);
	//glRotatef(m_Rotate.yPos, 0.f, 1.f, 0.f);
	//glRotatef(m_Rotate.zPos, 0.f, 0.f, 1.f);
	glPushMatrix();
	{
		glTranslatef(0, 100, 0);
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

void CShape::mainsphere()
{
	glColor3f(1.f, 0.f, 0.f);
	glPushMatrix();
	{
		glRotatef(m_mainR, 1, 0, 1);
		model(m_model, 30, 30, 30);
	}
	glPopMatrix();
}

void CShape::course1()
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 1.f);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 100 * cos(i*m_PI / 180);
				m_Info.zPos = 100 * sin(i*m_PI / 180);
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 100 * cos(m_co1R * m_PI / 180);
		m_Translate.zPos = 100 * -sin(m_co1R *m_PI / 180);

		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glPushMatrix();
		{
			glRotatef(m_co1R, 1, 0, 1);
			glColor3f(1.f, 1.f, 0.f);
			model(m_model, 20, 20, 20);
		}
		glPopMatrix();
		
		glColor3f(0.f, 1.f, 0.f);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 50 * cos(i*m_PI / 180);
				m_Info.zPos = 50 * (-sin(i*m_PI / 180));
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 50 * cos(m_mini1 * m_PI / 180);
		m_Translate.zPos = 50 * -sin(m_mini1 *m_PI / 180);
		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glRotatef(m_mini1, 1, 0, 1);
		glColor3f(0.5f, 0.5f, 0.f);
		model(m_model, 5, 15, 15);
	}
	glPopMatrix();
}

void CShape::course2()
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 1.f);
		glTranslatef(0, 0, 0);
		glRotatef(45, 0, 0, 1);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 100 * cos(i*m_PI / 180);
				m_Info.zPos = 100 * (-sin(i*m_PI / 180));
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 100 * -cos(m_co2R * m_PI / 180);
		m_Translate.zPos = 100 * sin(m_co2R *m_PI / 180);

		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glPushMatrix();
		{
			glRotatef(m_co2R, 1, 1, 0);
			glColor3f(1.f, 0.f, 1.f);
			model(m_model, 20, 20, 20);
		}
		glPopMatrix();

		glColor3f(0.f, 1.f, 0.f);
		glRotatef(-45, 0, 0, 1);			// 테를 다시 제자리로 돌린다.
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 50 * cos(i*m_PI / 180);
				m_Info.zPos = 50 * (-sin(i*m_PI / 180));
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 50 * cos(m_mini2 * m_PI / 180);
		m_Translate.zPos = 50 * -sin(m_mini2 *m_PI / 180);
		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glRotatef(m_mini2, 1, 0, 1);
		glColor3f(0.5f, 0.f, 0.5f);
		model(m_model, 5, 15, 15);
	}
	glPopMatrix();
}

void CShape::course3()
{
	glPushMatrix();
	{
		glColor3f(0.f, 0.f, 1.f);
		glTranslatef(0, 0, 0);
		glRotatef(-45, 0, 0, 1);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 100 * cos(i*m_PI / 180);
				m_Info.zPos = 100 * (-sin(i*m_PI / 180));
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 100 * -cos(m_co3R * m_PI / 180);
		m_Translate.zPos = 100 * sin(m_co3R *m_PI / 180);

		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glPushMatrix();
		{
			glRotatef(m_co3R, 1, 1, 0);
			glColor3f(0.f, 1.f, 1.f);
			model(m_model, 20, 20, 20);
		}
		glPopMatrix();

		glColor3f(0.f, 1.f, 0.f);
		glRotatef(45, 0, 0, 1);			// 테를 다시 제자리로 돌린다.
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 360; ++i)
			{
				m_Info.xPos = 50 * cos(i*m_PI / 180);
				m_Info.zPos = 50 * (-sin(i*m_PI / 180));
				glVertex3f(m_Info.xPos, m_Info.yPos, m_Info.zPos);
			}
		}
		glEnd();

		m_Translate.xPos = 50 * cos(m_mini3 * m_PI / 180);
		m_Translate.zPos = 50 * -sin(m_mini3 *m_PI / 180);
		glTranslatef(m_Translate.xPos, 0, m_Translate.zPos);
		glRotatef(m_mini3, 1, 0, 1);
		glColor3f(0.f, 0.5f, 0.5f);
		model(m_model, 5, 15, 15);
	}
	glPopMatrix();
}

void CShape::model(E_Model e_model, double rad, int slice, int stack)
{
	if (e_model == E_Wire)
	{
		glutWireSphere(rad, slice, stack);
	}
	else if (e_model == E_Solid)
	{
		glutSolidSphere(rad, slice, stack);
	}
}
