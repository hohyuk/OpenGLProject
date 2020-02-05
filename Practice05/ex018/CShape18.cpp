#include "stdafx.h"
#include "CShape18.h"
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
	m_Angle = 1.f;
	m_move = 1.f;
	memset(m_mat, 0, sizeof(m_mat));
	m_mat[0] = m_mat[5] = m_mat[10] = m_mat[15] = 1;
}

void CShape::run()
{
}

void CShape::render()
{
	coordinates();
	ground();
	rollsphere();
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
	case 'p':
		matrixprint();
		break;
		// 카메라 이동
	case 'm':
		if (m_Rotate.yPos > 360)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += 1;
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
			m_Translate.xPos -= 1;
		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(9.f, 0, 0, 1);
			glMultMatrixf(m_mat);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
		}
		glPopMatrix();
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if(m_Translate.xPos<150)
			m_Translate.xPos += 1;
		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(-9.f, 0, 0, 1);
			glMultMatrixf(m_mat);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
		}
		glPopMatrix();
	}
	else if (key == GLUT_KEY_UP)
	{
		if(m_Translate.zPos>-60)
			m_Translate.zPos -= 1;
		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(-9.f, 1.f, 0.f, 0.f);
			glMultMatrixf(m_mat);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
		}
		glPopMatrix();
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (m_Translate.zPos < 60)
			m_Translate.zPos += 1;
		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(9.f, 1.f, 0.f, 0.f);
			glMultMatrixf(m_mat);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
		}
		glPopMatrix();
	
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

void CShape::rollsphere()
{
	glTranslatef(0, 40, 0);
	glPushMatrix();
	{
		glColor3f(0.4f, 1.f, 0.4f);
		glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
		
		glMultMatrixf(m_mat);
		glutWireSphere(20, 20, 20);
	}
	glPopMatrix();
	
}

void CShape::matrixprint()
{
	cout << "m_mat 행렬 : " << endl;
	for (int i = 0; i < 16; ++i)
	{
		cout << m_mat[i];
		if ((i+1) % 4 == 0 )
			cout << endl;
		else
			cout << " ";
	}
	cout << endl;
}
