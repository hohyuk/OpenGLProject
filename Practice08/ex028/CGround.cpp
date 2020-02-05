#include "stdafx.h"
#include "CGround.h"

CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::init()
{
	m_Info = Point(0.f, -100.f, 50.f);
	m_Camera = Point(0.f, 30.f, -60.f);
	waveY = 5.f;
	m_Speed = 0.1f;
}

void CGround::update(int value)
{
	if (waveY > 5.f)
		m_Speed = -m_Speed;
	else if (waveY < -5.f)
		m_Speed = -m_Speed;
	waveY += m_Speed;
}

void CGround::render()
{
	glTranslatef(m_Info.xPos, m_Info.yPos, m_Info.zPos);
	glRotatef(15.f, 1, 0, 0);
	// 왼쪽면
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(-40, 50, 0);
		glScalef(10, waveY, 20);
		
		// 곡면 제어점 설정
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &Surface[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 40, 0.0, 1.0);
		// 선을 이용하여 그리드 연결
		glEvalMesh2(GL_LINE, 0, 10, 0, 40);
		glPointSize(5.0); 
		glColor3f(0.0, 1.f, 0.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(Surface[i][j]);
		glEnd();
	}
	glPopMatrix();
	// 오른쪽면
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(40, 50, 0);
		glScalef(10, -waveY, 20);

		// 곡면 제어점 설정
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &Surface[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 40, 0.0, 1.0);
		// 선을 이용하여 그리드 연결
		glEvalMesh2(GL_LINE, 0, 10, 0, 40);
		glPointSize(5.0);
		glColor3f(0.0, 1.f, 0.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(Surface[i][j]);
		glEnd();
	}
	glPopMatrix();

	// 다른 물체들을 땅바닥에 놓게 한다.
	glTranslatef(0.f, 50.f, 0);
}

void CGround::reshape(int w, int h)
{
}

void CGround::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':m_Info.yPos += 1.f;
		cout<<"y : " << m_Camera.yPos << endl;
		break;
	case 's':m_Info.yPos -= 1.f;
		cout << "y : " << m_Camera.yPos << endl;
		break;
	case 'a':m_Info.zPos += 1.f;
		cout << "z : " << m_Camera.zPos << endl;
		break;
	case 'd':m_Info.zPos -= 1.f;
		cout << "z : " << m_Camera.zPos << endl;
		break;
	case 'q':m_Info.xPos -= 1.f;
		break;
	case 'e':m_Info.xPos += 1.f;
		break;
	case 'i': init();
		break;
	}
}

void CGround::mouse(int button, int state, int x, int y)
{
}

void CGround::motion(int x, int y)
{
}

void CGround::freemotion(int x, int y)
{
}

void CGround::special(int key, int x, int y)
{
}

void CGround::run()
{
}