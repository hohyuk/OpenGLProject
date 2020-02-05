#pragma once
#include "CObj.h"

class CLighting :public CObj
{
public:
	CLighting();
	virtual ~CLighting();

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
	void flash(float x, float y, float z, GLenum light, bool isLight, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
private:
	bool isLightNum1;
	bool isLightNum2;
	bool isLightNum3;
	bool isLightNum4;
	bool isTurn;
	bool isNormal;
	float ambient;
};