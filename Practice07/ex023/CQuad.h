#pragma once
#include "CScene.h"

class CQuad :public CScene
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
	void cube();
private:
	float m_Size;
	unsigned int m_Shade;
	bool isDepth;
	bool isCulling;
	float topAngle;
	float frontAngle;
	bool isTopOpen;
	bool isfrontOpen;
};

