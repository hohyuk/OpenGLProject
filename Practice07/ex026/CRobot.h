#pragma once
#include "CObj.h"

class CRobot : public CObj
{
public:
	CRobot();
	virtual~CRobot();

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
	void robot_body();
	void robot_head();
	void robot_leg();
	void robot_upper_limb();

private:
	bool isJump;
	float angleX;
};