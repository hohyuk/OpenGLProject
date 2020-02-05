#pragma once
#include "CScene.h"

class CMoveObjs :public CScene
{
public:
	CMoveObjs();
	virtual ~CMoveObjs();

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

	// Sphere
private:
	void sphere_draw();
	void sphere_move();
private:
	Point m_SphereT;
	Point m_SphereR;
	float moveSphere;
	float angleSphere;
	// Car
private:
	void wheel(float x, float y, float z);
	void bottomrect();
	void middlerect();
	void toprect();
	Point m_middle;
	Point m_top;
	bool b_move;
	bool Collision();
};