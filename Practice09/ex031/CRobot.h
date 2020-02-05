#pragma once
#include "CObj.h"

const int MAX_BALL{ 72 };
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
	void flash(float x, float y, float z, GLenum light, bool isLight, float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f);
	bool pyramid_area(float x,float z);
	void ballRender();
	void ballMove();
private:
	bool isJump;
	float angleX;
	bool isSportLight;
	float exponent;
	Point* ball[MAX_BALL];
};