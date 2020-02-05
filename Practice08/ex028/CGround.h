#pragma once
#include "CObj.h"

class CGround : public CObj
{
public:
	CGround();
	virtual ~CGround();

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
	GLfloat Surface[3][3][3]= { { { -4.0, 0.0, 4.0 }, { 0.0, 10.0, 4.0 }, { 4.0, 0.0, 4.0 } },
	{ { -4.0, 0.0, 0.0 },{ 0.0, 10.0, 0.0 },{ 4.0, 0.0, 0.0 } },
	{ { -4.0, 0.0, -4.0 },{ 0.0, 10.0, -4.0 },{ 4.0, 0.0, -4.0 } } };

	float waveY;
};

