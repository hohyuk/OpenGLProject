#pragma once
#include "CObj.h"

class CLighting : public CObj
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
	void Light1();
	void Light2();
private:
	float ambient;
	float diffuse;
	float specular;
private:
	bool isLightNum1;
	bool isLightNum2;

};