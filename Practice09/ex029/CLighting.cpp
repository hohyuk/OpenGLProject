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
	ambient = 0.1f;
	diffuse = 0.1f;
	specular = 1.f;
	isLightNum1 = false;
	isLightNum2 = false;

}

void CLighting::update(int value)
{
}

void CLighting::render()
{
	GLfloat ambient_light[4] = { ambient,ambient,ambient,1 };
	GLfloat diffuse_light[4] = { diffuse ,diffuse ,diffuse ,1 };
	GLfloat specular_light[4] = { specular ,specular ,specular ,0.5 };
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular_light);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_light);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	Light1();
	Light2();
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
		if (ambient > 1)
			ambient = 0.1f;
		ambient += 0.1f;
	}
	else if (key == '4')
	{
		if (diffuse > 1)
			diffuse = 0.1f;
		diffuse += 0.1f;
	}
	else if (key == '5')
	{
		if (specular > 1)
			specular = 0.1f;
		specular += 0.1f;
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

void CLighting::Light1()
{
	GLfloat ambient_light[4] = { 1.f,0.f,0.f,1.f };
	GLfloat diffuse_light[4] = { 1.f,1.f,1.f,1.f };
	GLfloat specular_light[4] = { 1.f,1.f,1.f,1.f };

	GLfloat light_Pos[4] = { 100, 50, 0, 1 };
	glPushMatrix();
	{
		glTranslatef(light_Pos[0], light_Pos[1], light_Pos[2]);
		glutSolidSphere(2, 10, 10);
	}
	glPopMatrix();
	if (isLightNum1)
	{
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
		glLightfv(GL_LIGHT1, GL_POSITION, light_Pos);
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
}

void CLighting::Light2()
{
	GLfloat ambient_light[4] = { 1.f,1.f,0.f,1.f };
	GLfloat diffuse_light[4] = { 1.f,1.f,1.f,1.f };
	GLfloat specular_light[4] = { 1.f,1.f,1.f,1.f };

	GLfloat light_Pos[4] = { -100, 50, 0, 1 };
	glPushMatrix();
	{
		glTranslatef(light_Pos[0], light_Pos[1], light_Pos[2]);
		glutSolidSphere(2, 10, 10);
	}
	glPopMatrix();
	if (isLightNum2)
	{
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular_light);
		glLightfv(GL_LIGHT2, GL_POSITION, light_Pos);
		
		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}
}
