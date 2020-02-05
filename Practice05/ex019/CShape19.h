#pragma once
#include "CScene.h"

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
	void roolsphere(float x,float y, float z);
	void bottomrect();
	void middlerect();
	void toprect();
private:
	float m_rad;	// 구의 반지름
	float m_move;
	Point m_middle;
	Point m_top;
};

