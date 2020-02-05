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

	BITMAPINFO* texture;

	glGenTextures(5, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	pBytes = LoadDIBitMap("../Resource/pyramid_1.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	pBytes = LoadDIBitMap("../Resource/pyramid_1.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	pBytes = LoadDIBitMap("../Resource/pyramid_1.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	pBytes = LoadDIBitMap("../Resource/pyramid_1.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	

	// earth
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	pBytes = LoadDIBitMap("../Resource/Earth.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	

	glBindTexture(GL_TEXTURE_2D, tex[5]);
	pBytes = LoadDIBitMap("../Resource/moon.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
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
	Pyramid_render(-50, 0, 0);
	Pyramid_render(50, 0, 0);
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
		// 피라미드
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(x, y, z);
		// 앞면
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		glBegin(GL_POLYGON);
		{
			if(isNormal)
				glNormal3f(0.0, 0.0, 1.0);
			// 위
			glTexCoord2f(0.5, 1);
			glVertex3f(0.f, 100.f, 0.f);

			//왼쪽
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0, 0);
			glVertex3f(-25.f, 0.f, 25.f);
			// 오른쪽
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(1, 0);
			glVertex3f(25.f, 0.f, 25.f);
		}
		glEnd();
		// 뒷면
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(0.0, 0.0, -1.0);
			// 위
			glTexCoord2f(0.5, 1);
			glVertex3f(0.f, 100.f, 0.f);
			//왼쪽
			glTexCoord2f(0, 0);
			glVertex3f(-25.f, 0.f, -25.f);
			// 오른쪽
			glTexCoord2f(1, 0);
			glVertex3f(25.f, 0.f, -25.f);
		}
		glEnd();
		// 왼쪽면
		glBindTexture(GL_TEXTURE_2D, tex[2]);
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(-1.f, 0.f, 0.f);

			// 위
			glTexCoord2f(0.5, 1);
			glVertex3f(0.f, 100.f, 0.f);
			//왼쪽
			glTexCoord2f(0, 0);
			glVertex3f(-25.f, 0.f, -25.f);
			// 오른쪽
			glTexCoord2f(1, 0);
			glVertex3f(-25.f, 0.f, 25.f);
		}
		glEnd();
		// 오른쪽면
		glBindTexture(GL_TEXTURE_2D, tex[3]);
		glBegin(GL_POLYGON);
		{
			if (isNormal)
				glNormal3f(1.f, 0.f, 0.f);
			// 위
			glTexCoord2f(0.5, 1);
			glVertex3f(0.f, 100.f, 0.f);
			//왼쪽
			glTexCoord2f(0, 0);
			glVertex3f(25.f, 0.f, -25.f);
			// 오른쪽
			glTexCoord2f(1, 0);
			glVertex3f(25.f, 0.f, 25.f);
		}
		glEnd();
		// 지구
		glColor3f(1.0f, 1.0f, 1.f);
		glTranslatef(0, 60, 0);
		glPushMatrix();
		{
			glRotatef(Earth_Revolution, 0, 1, 0);
			glTranslatef(40.f, 0.f, 0.f);
			glBindTexture(GL_TEXTURE_2D, tex[4]);
			glutSolidSphere(5, 30, 30);

			// 달
			glPushMatrix();
			{
				glRotatef(Moon_Revolution, 0, 1, 0);
				glTranslatef(10.f, 0.f, 0.f);
				glColor3f(1.0f, 1.0f, 1.f);
				glBindTexture(GL_TEXTURE_2D, tex[5]);
				glutSolidSphere(2.5, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
