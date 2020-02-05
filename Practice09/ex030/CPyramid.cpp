#include "CPyramid.h"

CPyramid::CPyramid()
{
}

CPyramid::~CPyramid()
{
}

void CPyramid::init()
{
	m_Translate = Point(0.f, 0.f, 0.f);
	Earth_Revolution = 0;
	Moon_Revolution = 0;
	isNormal = false;
}

void CPyramid::update(int value)
{
	if (Earth_Revolution > 360)
		Earth_Revolution = 0.f;
	Earth_Revolution += 0.5f;

	if (Moon_Revolution > 360)
		Moon_Revolution = 0.f;
	Moon_Revolution += 1.f;
}

void CPyramid::render()
{
	//Pyramid_render(-50, 0, 0);
	//Pyramid_render(50, 0, 0);
	// ���� ����
	if (isNormal)
		glEnable(GL_NORMALIZE);
	else
		glDisable(GL_NORMALIZE);
	Pyramid_(-50, 0, 0);
	Pyramid_(50, 0, 0);
}

void CPyramid::reshape(int w, int h)
{
}

void CPyramid::keyboard(unsigned char key, int x, int y)
{
	if (key == '6')
		isNormal = !isNormal;
}

void CPyramid::mouse(int button, int state, int x, int y)
{
}

void CPyramid::motion(int x, int y)
{
}

void CPyramid::freemotion(int x, int y)
{
}

void CPyramid::special(int key, int x, int y)
{
}

void CPyramid::run()
{
}

void CPyramid::Pyramid_render(float x, float y, float z)
{
	glPushMatrix();
	{
		// �Ƕ�̵�
		glColor3f(0.f, 1.f, 0.f);
		glTranslatef(x, y, z);
		glPushMatrix();
		{
			glRotatef(-90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			glutSolidCone(30, 80, 4, 4);
		}
		glPopMatrix();

		// ����
		glColor3f(0.0f, 0.0f, 0.5f);
		glTranslatef(0, 60, 0);
		glPushMatrix();
		{
			glRotatef(Earth_Revolution, 0, 1, 0);
			glTranslatef(40.f, 0.f, 0.f);
			glutSolidSphere(5, 30, 30);

			// ��
			glPushMatrix();
			{
				glColor3f(0.0f, 0.5f, 0.f);
				glRotatef(Moon_Revolution, 0, 1, 0);
				glTranslatef(10.f, 0.f, 0.f);
				glutSolidSphere(2.5, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CPyramid::Pyramid_(float x, float y, float z)
{
	glPushMatrix();
	{
		// �Ƕ�̵�
		glColor3f(0.f, 1.f, 0.f);
		glTranslatef(x, y, z);
		// �ո�
		glBegin(GL_POLYGON);
		{
			if(isNormal)
				glNormal3f(0.0, 0.0, 1.0);
			// ��
			
			glVertex3f(0.f, 100.f, 0.f);

			//����
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(-25.f, 0.f, 25.f);
			// ������
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(25.f, 0.f, 25.f);
		}
		glEnd();
		// �޸�
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(0.0, 0.0, -1.0);
			// ��
			glVertex3f(0.f, 100.f, 0.f);
			//����
			glVertex3f(-25.f, 0.f, -25.f);
			// ������
			glVertex3f(25.f, 0.f, -25.f);
		}
		glEnd();
		// ���ʸ�
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(-1.f, 0.f, 0.f);

			// ��
			glVertex3f(0.f, 100.f, 0.f);
			//����
			glVertex3f(-25.f, 0.f, -25.f);
			// ������
			glVertex3f(-25.f, 0.f, 25.f);
		}
		glEnd();
		// �����ʸ�
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(1.f, 0.f, 0.f);
			// ��
			glVertex3f(0.f, 100.f, 0.f);
			//����
			glVertex3f(25.f, 0.f, -25.f);
			// ������
			glVertex3f(25.f, 0.f, 25.f);
		}
		glEnd();
		// ����
		glColor3f(0.0f, 0.0f, 0.5f);
		glTranslatef(0, 60, 0);
		glPushMatrix();
		{
			glRotatef(Earth_Revolution, 0, 1, 0);
			glTranslatef(40.f, 0.f, 0.f);
			glutSolidSphere(5, 30, 30);

			// ��
			glPushMatrix();
			{
				glColor3f(0.0f, 0.5f, 0.f);
				glRotatef(Moon_Revolution, 0, 1, 0);
				glTranslatef(10.f, 0.f, 0.f);
				glutSolidSphere(2.5, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
