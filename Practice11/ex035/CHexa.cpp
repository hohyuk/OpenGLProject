#include "CHexa.h"


CHexa::CHexa()
{
}


CHexa::~CHexa()
{
}

void CHexa::init()
{
	Mode = GL_LINEAR;
	m_Translate = Point(0, 0, 0);
	m_Rotate = Point(0, 0, 0);
	color = 0.1f;
	m_density = 0.5f;
	m_start = 10.f;
	m_end = 150.f;
}

void CHexa::update(int value)
{
}

void CHexa::render()
{
	

	GLfloat fog_color[4] = { color, color, color, 0.5 };
	
	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, Mode);
	glFogfv(GL_FOG_COLOR, fog_color); // fog_color는 안개의 색을 의미한다. glFogf(GL_FOG_START, start); // start는 world coordinate상에서 안개 시작 위치를 의미한다.
	glFogf(GL_FOG_END, m_end); // end는 world coordinate상에서 안개 끝 위치를 의미한다.
	glFogf(GL_FOG_DENSITY, m_density); // fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능
	
	glPushMatrix();
	{
		glTranslatef(0, 0, m_Translate.zPos);
		glRotatef(m_Rotate.yPos, 0, 1, 0);

		glColor4f(1, 0, 0, 1);
		glutSolidCube(100);

		glPushMatrix();
		{
			glColor4f(0, 0, 1, 1);
			glTranslatef(100 - 25, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor4f(0, 1, 0, 1);
			glTranslatef(-100 + 25, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();
	}
	glPopMatrix();
	
}

void CHexa::reshape(int w, int h)
{
}

void CHexa::keyboard(unsigned char key, int x, int y)
{
	// Mode
	switch (key)
	{
	case '1':Mode = GL_LINEAR; break;
	case '2':Mode = GL_EXP; break;
	case '3':Mode = GL_EXP2; break;
	case '4': if (color >= 1.f)color = 0.1;
		color += 0.1f; break;
	case 't':
		if (m_Rotate.yPos > 360)
			m_Rotate.yPos = 0.f;
		m_Rotate.yPos += 5.f;
		break;
	case 'b':
		if (m_density > 1.f)
			m_density = 0.f;
		m_density += 0.1f;
		break;
	case 'n':
		if (m_start < 0)
			m_start = 0.f;
		m_start -= 5.f;
		break;
	case 'm':
		if (m_start > m_end)
			m_start = m_end;
		m_start += 5.f;
		break;
	case 'k':
		if (m_end < m_start)
			m_end = m_start;
		m_end -= 5.f;
		break;
	case 'l':
		m_end += 5.f;
		break;
	}
}

void CHexa::mouse(int button, int state, int x, int y)
{
}

void CHexa::motion(int x, int y)
{
}

void CHexa::freemotion(int x, int y)
{
}

void CHexa::special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		m_Translate.zPos += 10.f;
		break;
	case GLUT_KEY_DOWN:
		m_Translate.zPos -= 10.f;
		break;
	}
}

void CHexa::run()
{
}
