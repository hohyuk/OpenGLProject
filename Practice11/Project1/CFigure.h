#pragma once
#include "CObj.h"
class CFigure : public CObj
{
public:
	CFigure();
	virtual ~CFigure();

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
	void BlendingType(int num);
	void FigureRender(int num);
	void ChoiceRender(float x,float y);
	void FontRender();
private:
	int number;
	float Sphere_Alpha[9];
	float Cone_Alpha[9];
	float Teapot_Alpha[9];

};

