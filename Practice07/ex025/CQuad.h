#pragma once
#include "CObj.h"
const int MAX_BALL{ 5 };
const int MAX_CUBE{ 3 };
class CQuad :public CObj
{
public:
	CQuad();
	virtual~CQuad();

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
	void cubeSpace();
	int createBall();
	void moveBall();
	void moveCube();
private:
	float m_Size;
	unsigned int m_Shade;
	bool isDepth;
	bool isCulling;
	// ball
	Point* m_ball[MAX_BALL];
	float ballSpeed;
	float ballradian;

	// cube
	Cube* m_cube[MAX_CUBE];
	// button
	bool isButtonOn;
};

