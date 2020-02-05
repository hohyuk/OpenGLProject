#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint()
{
}

CPoint::~CPoint()
{
}

void CPoint::init()
{
	count = 0;
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		isDraw[i] = false;
		memset(ctrlpoints[i], 0, sizeof(ctrlpoints[i]));
	}
		
}

void CPoint::update(int value)
{
}

void CPoint::render()
{
	for (int i = 0; i < MAX_COUNT; i+=3)
	{
		if (isDraw[i + 3] && i + 3 < MAX_COUNT)
		{
			glColor3f(1.f, 1.f, 1.f);
			glMap1f(GL_MAP1_VERTEX_3, 0.f, 1.f, 3, 4, &ctrlpoints[i][0]);

			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(20, 0.f, 1.f);
			glEvalMesh1(GL_LINE, 0, 20);

			glDisable(GL_MAP1_VERTEX_3);
		}
	}
	
	
	
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (isDraw[i])
		{
			glPointSize(5);
			glColor3f(0.f, 1.f, 0.f);
			glBegin(GL_POINTS);
			{
				glVertex3fv(&ctrlpoints[i][0]);
			}
			glEnd();
		}
	}
}

void CPoint::reshape(int w, int h)
{
}

void CPoint::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		init();
		cout << "reset" << endl;
		break;
	}
}

void CPoint::mouse(int button, int state, int x, int y)
{
	if (button == GLUT_DOWN && state == GLUT_LEFT_BUTTON)
	{
		if (count < MAX_COUNT)
		{
			ctrlpoints[count][0] = float(x);
			ctrlpoints[count][1] = float(600 - y);
			ctrlpoints[count][2] = 0;
			isDraw[count] = true;
			++count;
		}
		else
		{
			cout << "full : " << count << endl;
		}
		cout << "x = " << x << "y = " << y << endl;
	}
}

void CPoint::motion(int x, int y)
{
}

void CPoint::freemotion(int x, int y)
{
}

void CPoint::special(int key, int x, int y)
{
}

void CPoint::run()
{
}
