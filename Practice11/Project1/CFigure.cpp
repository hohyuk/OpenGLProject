#include "CFigure.h"



CFigure::CFigure()
{
	
}


CFigure::~CFigure()
{
}

void CFigure::init()
{
	m_Translate = Point{ -250,200,0 };
	for (int i = 0; i < 9; ++i)
	{
		Sphere_Alpha[i] = 1.f;
		Cone_Alpha[i] = 1.f;
		Teapot_Alpha[i] = 1.f;

	}

	number = 0;
}

void CFigure::update(int value)
{
}

void CFigure::render()
{
	
	// 초기위치
	glTranslatef(m_Translate.xPos, m_Translate.yPos, m_Translate.zPos);

	FontRender();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			glPushMatrix();
			{
				glTranslatef(j * 250, i * (-200), 0);
				int num = (i * 3) + j;
				if (num == number)
				{
					glColor3f(1, 0, 0);
					ChoiceRender(250, 200);
				}
				glEnable(GL_BLEND);
				BlendingType(num);
				FigureRender(num);
			}
			glPopMatrix();

			
		}
	}
	//glDisable(GL_BLEND);
	
}

void CFigure::reshape(int w, int h)
{
}

void CFigure::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': number = 0; break;
	case '2': number = 1; break;
	case '3': number = 2; break;
	case '4': number = 3; break;
	case '5': number = 4; break;
	case '6': number = 5; break;
	case '7': number = 6; break;
	case '8': number = 7; break;
	case '9': number = 8; break;
	}
	switch (key)
	{
	case 's':
		if (Sphere_Alpha[number] > 1.f)
			Sphere_Alpha[number] = 0.1f;
		Sphere_Alpha[number] += 0.1f;
		break;
	case 'c':
		if (Cone_Alpha[number] > 1.f)
			Cone_Alpha[number] = 0.1f;
		Cone_Alpha[number] += 0.1f;
		break;
	case 't':
		if (Teapot_Alpha[number] > 1.f)
			Teapot_Alpha[number] = 0.1f;
		Teapot_Alpha[number] += 0.1f;
		break;
	}
}

void CFigure::mouse(int button, int state, int x, int y)
{
}

void CFigure::motion(int x, int y)
{
}

void CFigure::freemotion(int x, int y)
{
}

void CFigure::special(int key, int x, int y)
{
}

void CFigure::run()
{
}

void CFigure::BlendingType(int num)
{
	if (num == 0)
		glBlendFunc(GL_ONE, GL_ZERO);
	else if (num == 1)
		glBlendFunc(GL_ZERO, GL_ONE);
	else if (num == 2)
		glBlendFunc(GL_ONE, GL_ONE);
	else if (num == 3)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	else if (num == 4)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	else if (num == 5)
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	else if (num == 6)
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	else if (num == 7)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	else if (num == 8)
		glBlendFunc(GL_ZERO, GL_ZERO);
	//glDisable(GL_BLEND);
}

void CFigure::FigureRender(int num)
{

	glPushMatrix();
	{
		
		// Sphere
		glColor4f(0.f, 0.f, 1.f, Sphere_Alpha[num]);
		
		glutSolidSphere(50, 30, 30);

		glPushMatrix();
		{
			// Teapot
			glColor4f(1.f, 0.f, 0.f, Teapot_Alpha[num]);
			glTranslatef(-30, 0, 30);
			glutSolidTeapot(50);
		}
		glPopMatrix();
		// Cone
		glPushMatrix();
		{
			glColor4f(0.f, 1.f, 0.f, Cone_Alpha[num]);
			glTranslatef(30, 0, 60);
			glRotatef(-90, 1, 0, 0);
			glutSolidCone(50, 60, 30, 30);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void CFigure::ChoiceRender(float x, float y)
{
	glPushMatrix();
	{
		glLineWidth(5);
		glDisable(GL_BLEND);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(-x / 2, y / 2);
			glVertex2f(-x / 2, -y / 2);
			glVertex2f(x / 2, -y / 2);
			glVertex2f(x / 2, y / 2);
		}
		glEnd();
	}
	glPopMatrix();
}

void CFigure::FontRender()
{
	glDisable(GL_BLEND);
	glColor3f(1.f, 1.f, 1.f);
	char *string = "GL_ONE, GL_ZERO";
	glRasterPos2f(-100, -100); // 문자 출력할 위치 설정
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

	char *string1 = "GL_ZERO, GL_ONE";
	glRasterPos2f(150, -100); // 문자 출력할 위치 설정
	int len1 = (int)strlen(string1);
	for (int i = 0; i < len1; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);

	char *string2 = "GL_ONE, GL_ONE";
	glRasterPos2f(400, -100); // 문자 출력할 위치 설정
	int len2 = (int)strlen(string2);
	for (int i = 0; i < len2; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);



	char *string3 = "GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA";
	glRasterPos2f(-100, -300); // 문자 출력할 위치 설정
	int len3 = (int)strlen(string3);
	for (int i = 0; i < len3; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);

	char *string4 = "GL_SRC_ALPHA, GL_ONE";
	glRasterPos2f(150, -300); // 문자 출력할 위치 설정
	int len4 = (int)strlen(string4);
	for (int i = 0; i < len4; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string4[i]);

	char *string5 = "GL_ZERO, GL_SRC_COLOR";
	glRasterPos2f(400, -300); // 문자 출력할 위치 설정
	int len5 = (int)strlen(string5);
	for (int i = 0; i < len5; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string5[i]);



	char *string6 = "GL_ONE_MINUS_DST_COLOR, GL_ZERO";
	glRasterPos2f(-100, -500); // 문자 출력할 위치 설정
	int len6 = (int)strlen(string6);
	for (int i = 0; i < len6; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string6[i]);

	char *string7 = "GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR";
	glRasterPos2f(150, -500); // 문자 출력할 위치 설정
	int len7 = (int)strlen(string7);
	for (int i = 0; i < len7; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string7[i]);

	char *string8 = "GL_ZERO, GL_ZERO";
	glRasterPos2f(400, -500); // 문자 출력할 위치 설정
	int len8 = (int)strlen(string8);
	for (int i = 0; i < len8; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string8[i]);
}
