#include "stdafx.h"
#include "CLighting.h"

CLighting::CLighting()
{

}

CLighting::~CLighting()
{

}

void CLighting::init()
{
	isLightNum1 = isLightNum2 = isLightNum3 = isLightNum4 = false;
	ambient = 0.5f;
	m_Angle = 0.f;
	isTurn = false;
	isNormal = false;
}

void CLighting::update(int value)
{
	if (isTurn)
	{
		if (m_Angle > 360)
			m_Angle = 0.f;
		m_Angle += 1.f;
	}
	
}

void CLighting::render()
{
	//// 법선 벡터
	if (isNormal)
		glEnable(GL_NORMALIZE);
	else
		glDisable(GL_NORMALIZE);
	// 전체 조명
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat ambient_light[4] = { ambient,ambient,ambient,ambient };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	glEnable(GL_COLOR_MATERIAL);
	/*glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	GLfloat specular_light[4] = { 0.5f ,0.5f ,0.5f ,0.5 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_light);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
*/
	glPushMatrix();
	{
		glNormal3f(0.0, 50.0, 0.0);
		glRotatef(m_Angle, 0, 1, 0);
		// 부분 조명
		// 오른쪽 부분
		flash(160, 10, 110, GL_LIGHT1, isLightNum1, 1, 0, 0, 1);
		flash(160, 10, -110, GL_LIGHT2, isLightNum2, 0, 1, 0, 1);
		// 왼쪽 부분
		flash(-160, 10, 110, GL_LIGHT3, isLightNum3, 0, 0, 1, 1);
		flash(-160, 10, -110, GL_LIGHT4, isLightNum4);
	}
	glPopMatrix();
	
	
}

void CLighting::reshape(int w, int h)
{
}

void CLighting::keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		isLightNum1 = !isLightNum1;
	}
	else if (key == '2')
	{
		isLightNum2 = !isLightNum2;
	}
	else if (key == '3')
	{
		isLightNum3 = !isLightNum3;
	}
	else if (key == '4')
	{
		isLightNum4 = !isLightNum4;
	}
	else if (key == '5')
	{
		if (ambient > 1.f)
			ambient = 0.1f;
		ambient += 0.1f;
	}
	else if (key == '6')
	{
		isNormal = !isNormal;
	}
	else if (key == '7')
	{
		isTurn = !isTurn;
	}
	else if (key == 'i')
	{
		init();
	}
}

void CLighting::mouse(int button, int state, int x, int y)
{
}

void CLighting::motion(int x, int y)
{
}

void CLighting::freemotion(int x, int y)
{
}

void CLighting::special(int key, int x, int y)
{
}

void CLighting::run()
{
}

void CLighting::flash(float x, float y, float z, GLenum light, bool isLight, float r, float g, float b, float a)
{
	GLfloat ambient_light[4] = { r,g,b,a };
	GLfloat diffuse_light[4] = { 1.f,1.f,1.f,1.f };
	GLfloat specular_light[4] = { 1.f,1.f,1.f,1.f };

	GLfloat light_Pos[4] = { x, y, z, 1 };

	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glutSolidCube(5);
	}
	glPopMatrix();
	if (isLight)
	{
		glLightfv(light, GL_AMBIENT, ambient_light);
		glLightfv(light, GL_DIFFUSE, diffuse_light);
		glLightfv(light, GL_SPECULAR, specular_light);
		glLightfv(light, GL_POSITION, light_Pos);
		glEnable(light);
	}
	else
		glDisable(light);
}


