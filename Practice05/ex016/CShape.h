#pragma once
#include "CScene.h"
enum E_Shape
{
	E_Cube,
	E_Circle,
	E_Cone,
	E_Teapot
};
class CShape : public CScene
{
public:
	CShape();
	virtual ~CShape();

	virtual void init();
	virtual void run();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void mouse(int button, int state, int x, int y);
	virtual void motion(int x, int y);
	virtual void freemotion(int x, int y);
	virtual void special(int key, int x, int y);
	virtual void update(int value);

private:
	void coordinates();
	void ground();
	void leftshape();
	void rightshape();
private:
	Point m_leftR;
	Point m_rightR;
	int rand_left;
	int rand_right;
	E_Shape shape;
};

