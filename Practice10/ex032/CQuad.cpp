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
	m_Rotate = Point(30, 45, 0);
	m_Shade = GL_SMOOTH;
	isDepth = true;
	isCulling = true;
	m_Angle = 0.f;
	topAngle = 0.f;
	frontAngle = 0.f;
	isTopOpen = false;
	isfrontOpen = false;
	
	// Texture
	BITMAPINFO* texture;

	glGenTextures(6, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->bmiHeader.biWidth, texture->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[4]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[5]);
	pBytes = LoadDIBitMap("../Resource/create.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);

}

void CQuad::update(int value)
{
	m_Angle += 1.f;
	if (m_Angle > 360)
		m_Angle = 0.f;

	if (isTopOpen)
	{
		if (topAngle < 90.f)
			topAngle += 1.f;
	}
	else
	{
		if (topAngle > 0)
			topAngle -= 1.f;
	}
	if (isfrontOpen)
	{
		if (frontAngle < 90.f)
			frontAngle += 1.f;
	}
	else
	{
		if (frontAngle > 0)
			frontAngle -= 1.f;
	}
}

void CQuad::render()
{
	
	//// 쉐이딩
	//glShadeModel(m_Shade); // 또는 glShadeModel (GL_FLAT)
	//// 은면 제거
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
	cube();
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
	case '5':
		isTopOpen = !isTopOpen;
		break;
	case '6':
		isfrontOpen = !isfrontOpen;
		break;
	}
}

void CQuad::mouse(int button, int state, int x, int y)
{
}

void CQuad::motion(int x, int y)
{
}

void CQuad::freemotion(int x, int y)
{
}

void CQuad::special(int key, int x, int y)
{
}

void CQuad::run()
{
}

void CQuad::cube()
{
	glColor3f(1, 1, 1);
	// 앞면
	glPushMatrix();
	{
		float Pos = 100;
		glTranslatef(Pos, 0, Pos);
		glRotatef(frontAngle, 0, 1, 0);
		glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		glBegin(GL_QUADS);
		{
			//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
			glTexCoord2f(1, 1);
			glVertex3f(SPACE - Pos, SPACE, SPACE - Pos);
			//glColor3f(1.0f, 0.0, 1.0f); // Magenta
			glTexCoord2f(0, 1);
			glVertex3f(-SPACE - Pos, SPACE, SPACE - Pos);
			//glColor3f(0.0f, 1.0f, 1.0f); // Cyan
			glTexCoord2f(0, 0);
			glVertex3f(-SPACE - Pos, -SPACE, SPACE - Pos);
			//glColor3f(0.0f, 0.0f, 1.0f); // Blue
			glTexCoord2f(1, 0);
			glVertex3f(SPACE - Pos, -SPACE, SPACE - Pos);
		}
		glEnd();
	}
	glPopMatrix();
	// 뒷면
	glFrontFace(GL_CW);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
	{
		//glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glTexCoord2f(1, 1);
		glVertex3f(SPACE, SPACE, -SPACE);
		//glColor3f(0.0f, 1.0f, 1.0f); // Cyan
		glTexCoord2f(0, 1);
		glVertex3f(-SPACE, SPACE, -SPACE);
		//glColor3f(1.0f, 0.0, 1.0f); // Magenta
		glTexCoord2f(0, 0);
		glVertex3f(-SPACE, -SPACE, -SPACE);
		//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glTexCoord2f(1, 0);
		glVertex3f(SPACE, -SPACE, -SPACE);
	}
	glEnd();
	// 왼쪽면
	glFrontFace(GL_CCW);	
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBegin(GL_QUADS);
	{
		//glColor3f(1.0f, 0.0f, 0.0f); 
		glTexCoord2f(1, 1);
		glVertex3f(-SPACE, SPACE, SPACE);
		//glColor3f(0.0f, 0.0, 1.0f); 
		glTexCoord2f(0, 1);
		glVertex3f(-SPACE, SPACE, -SPACE);
		//glColor3f(0.0f, 1.0f, 0.0f); 
		glTexCoord2f(0, 0);
		glVertex3f(-SPACE, -SPACE, -SPACE);
		//glColor3f(1.0f, 0.0f, 1.0f); 
		glTexCoord2f(1, 0);
		glVertex3f(-SPACE, -SPACE, SPACE);
	}
	glEnd();
	// 오른쪽면
	glFrontFace(GL_CW);	
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBegin(GL_QUADS);
	{
		//glColor3f(1.f, 1.f, 0.f);
		glTexCoord2f(1, 1);
		glVertex3f(SPACE, SPACE, SPACE);
		//glColor3f(1.f, 0.f, 1.f);
		glTexCoord2f(0, 1);
		glVertex3f(SPACE, SPACE, -SPACE);
		//glColor3f(1.f, 1.f, 1.f);
		glTexCoord2f(0, 0);
		glVertex3f(SPACE, -SPACE, -SPACE);
		//glColor3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(SPACE, -SPACE, SPACE);
	}
	glEnd();

	// 윗면
	glPushMatrix();
	{
		float Pos = 100;
		glTranslatef(Pos, Pos, 0);
		glRotatef(-topAngle, 0, 0, 1);
		//glTranslatef(xPos, 0, 0);
		
		glFrontFace(GL_CCW);	// 시계 반대방향 (Y -> M -> C ->B)
		glBindTexture(GL_TEXTURE_2D, tex[4]);
		glBegin(GL_QUADS);
		{
			//glColor3f(0.f, 0.5f, 0.f);
			glTexCoord2f(1, 1);
			glVertex3f(SPACE - Pos, SPACE - Pos, SPACE);
			//glColor3f(0.7f, 0.3f, 0.f);
			glTexCoord2f(0, 1);
			glVertex3f(SPACE - Pos, SPACE - Pos, -SPACE);
			//glColor3f(1.f, 0.f, 0.3f);
			glTexCoord2f(0, 0);
			glVertex3f(-SPACE - Pos, SPACE - Pos, -SPACE);
			//glColor3f(0.4f, 0.2f, 0.5f);
			glTexCoord2f(1, 0);
			glVertex3f(-SPACE - Pos, SPACE - Pos, SPACE);
		}
		glEnd();
	}
	glPopMatrix();
	// 아랫면
	glFrontFace(GL_CW);	// 시계 반대방향 (Y -> M -> C ->B)
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glBegin(GL_QUADS);
	{
		//glColor3f(0.f, 0.5f, 0.f);
		glTexCoord2f(1, 1);
		glVertex3f(SPACE, -SPACE, SPACE);
		//glColor3f(0.7f, 0.3f, 0.f);
		glTexCoord2f(0, 1);
		glVertex3f(SPACE, -SPACE, -SPACE);
		//glColor3f(1.f, 0.f, 0.3f);
		glTexCoord2f(0, 0);
		glVertex3f(-SPACE, -SPACE, -SPACE);
		//glColor3f(0.4f, 0.2f, 0.5f);
		glTexCoord2f(1, 0);
		glVertex3f(-SPACE, -SPACE, SPACE);
	}
	glEnd();
}
