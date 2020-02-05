#include "CRobot.h"

CRobot::CRobot()
{
}

CRobot::~CRobot()
{
}

void CRobot::init()
{
	m_Translate = Point(0, 100, 0);
	m_Rotate = Point(0, 0, 0);
	m_Translate.xSpeed = m_Translate.ySpeed = m_Translate.zSpeed = 1.f;
	m_Translate.xDir = m_Translate.yDir = m_Translate.zDir = 0.f;
	isJump = false;
	angleX = 0.5f;
	exponent = 120;
	isSportLight = true;
	for (int i = 0; i < MAX_BALL; ++i)
	{
		ball[i] = NULL;
	}
}

void CRobot::update(int value)
{
	if (pyramid_area(-50, 0) || pyramid_area(50, 0))
	{
		if (m_Translate.xDir == 1)
		{
			m_Translate.xPos -= 1.f;
			m_Translate.xDir = 0.f;
		}
		else if (m_Translate.xDir == -1)
		{
			m_Translate.xPos += 1.f;
			m_Translate.xDir = 0.f;
		}
		if (m_Translate.zDir == 1)
		{
			m_Translate.zPos -= 1.f;
			m_Translate.zDir = 0.f;
		}
		else if (m_Translate.zDir == -1)
		{
			m_Translate.zPos += 1.f;
			m_Translate.zDir = 0.f;
		}
	}
	// limit_space
	float limit_spaceX = 150 - 15;
	float limit_spaceZ = 100 - 15;
	if (m_Translate.xPos > limit_spaceX)
	{
		m_Translate.xPos = limit_spaceX;
	}
	else if (m_Translate.xPos < -limit_spaceX)
	{
		m_Translate.xPos = -limit_spaceX;
	}

	if (m_Translate.zPos > limit_spaceZ)
	{
		m_Translate.zPos = limit_spaceZ;
	}
	else if (m_Translate.zPos < -limit_spaceZ)
	{
		m_Translate.zPos = -limit_spaceZ;
	}
	
	// jump
	float bottom = 35 ;

	if (isJump)
	{
		m_Translate.yDir = 1;
		if (m_Translate.yPos > 100)
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
	
	ballMove();
}

void CRobot::render()
{
	flash(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos, GL_LIGHT5, isSportLight);
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
	else if (key == 'p')
	{
		for (int i = 0; i < MAX_BALL; ++i)
		{
			if (ball[i] == NULL)
			{
				ball[i] = new Point(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);
				ball[i]->yDir = i * 5;
			}
			
		}
	}
	else if (key == '8')
	{
		isSportLight = !isSportLight;
	}
	else if (key == '+' || key == '=')
	{
		if (exponent < 10)
			exponent = 80;
		exponent -= 5.f;
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
		glScalef(0.5f, 0.5f, 0.5f);
		glScalef(1.5f, 2.f, 1.f);
		glutSolidCube(30);

		// Scale init 
		glScalef(1 / 1.5f, 1 / 2.f, 1.f);
		robot_head();
		robot_leg();
		robot_upper_limb();

		ballRender();
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

		// 코
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

void CRobot::flash(float x, float y, float z, GLenum light, bool isLight, float r, float g, float b, float a)
{
	GLfloat ambient_light[4] = { r,g,b,a };
	GLfloat diffuse_light[4] = { 50.f,50.f,10.f,15.f };
	GLfloat specular_light[4] = { 1.f,1.f,1.f,1.f };

	GLfloat light_Pos[4] = { x, y+100, z, 1 };
	GLfloat light_Dir[3] = { 0,-1,0 };
	glPushMatrix();
	{
		glTranslatef(x, y+100, z);
		glutSolidCube(5);
	}
	glPopMatrix();
	if (isLight)
	{
		glLightfv(light, GL_AMBIENT, ambient_light);
		glLightfv(light, GL_DIFFUSE, diffuse_light);
		glLightfv(light, GL_SPECULAR, specular_light);
		glLightfv(light, GL_POSITION, light_Pos);
		glLightf(light, GL_SPOT_CUTOFF, 60.0f);
		glLightf(light, GL_SPOT_EXPONENT, exponent);			// 스포트라이트 크기 0이되면 커진다
		glLightfv(light, GL_SPOT_DIRECTION, light_Dir);
		glEnable(light);

	}
	else
		glDisable(light);
}

bool CRobot::pyramid_area(float x, float z)
{
	// Rect & Rect Collision.
	float left_1, right_1, top_1, bottom_1;		
	float left_2, right_2, top_2, bottom_2;		
	float robotSize = 15;
	float pyramidSize = 15;
	left_1 = m_Translate.xPos - robotSize;
	right_1 = m_Translate.xPos + robotSize;
	bottom_1 = m_Translate.zPos - robotSize;
	top_1 = m_Translate.zPos + robotSize;

	
	left_2 = x -  pyramidSize;
	right_2 = x + pyramidSize;
	bottom_2 = z - pyramidSize;
	top_2 = z + pyramidSize;

	// Not Collision
	if (left_1 > right_2)
		return false;
	if (right_1 < left_2)
		return false;

	if (bottom_1 > top_2)
		return false;
	if (top_1 < bottom_2)
		return false;

	// Collision
	return true;
}

void CRobot::ballRender()
{
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (ball[i] != NULL)
		{
			glPushMatrix();
			{


				glColor3f(0.5, 0.5, 0.f);
				glRotatef(ball[i]->yDir, 0, 1, 0);
				glTranslatef(ball[i]->xPos, ball[i]->yPos, ball[i]->zPos);
				glutSolidSphere(5, 10, 10);

			}
			glPopMatrix();
		}
	}
}

void CRobot::ballMove()
{
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (ball[i] != NULL)
		{
			if (ball[i]->xPos > SPACE+100)
			{
				delete ball[i];
				ball[i] = NULL;
			}
			else
				ball[i]->xPos += 1.f;
		}
	}
}


