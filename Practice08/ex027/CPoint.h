#pragma once
#include "CObj.h"
const int MAX_COUNT{ 19 };
class CPoint : public CObj
{
public:
	CPoint();
	virtual~CPoint();

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
	GLfloat ctrlpoints[MAX_COUNT][3];
	bool isDraw[MAX_COUNT];
	int count;
};

