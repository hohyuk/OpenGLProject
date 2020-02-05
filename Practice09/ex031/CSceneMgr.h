#pragma once
#include "CObj.h"
const int MAX_OBJ{ 5 };
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

	void init();
	void update(int value);
	void render();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void freemotion(int x, int y);
	void special(int key, int x, int y);
	void run();
private:
	void coordinates();
	int Size;
	CObj* m_Obj[MAX_OBJ];
	bool isDepth;
};