#pragma once
#include "CObj.h"
class CHexa :public CObj
{
public:
	CHexa();
	virtual~CHexa();

	virtual void init();
	virtual void update(int value);
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void mouse(int button, int state, int x, int y);
	virtual void motion(int x, int y);
	virtual void freemotion(int x, int y);
	virtual void special(int key, int x, int y);
	virtual void run();

private:
	int Mode;
	float color;
	GLfloat m_density;
	GLfloat m_start;
	GLfloat m_end;
};

