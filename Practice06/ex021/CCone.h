#pragma once
#include "CScene.h"

class CCone : public CScene
{
public:
	CCone();
	virtual ~CCone();
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

};