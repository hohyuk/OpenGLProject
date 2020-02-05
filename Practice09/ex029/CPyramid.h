#pragma once
#include "CObj.h"

class CPyramid : public CObj
{
public:
	CPyramid();
	virtual ~CPyramid();

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
	float Earth_Revolution;
	float Moon_Revolution;
};