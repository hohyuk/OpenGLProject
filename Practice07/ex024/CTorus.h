#pragma once
#include "CScene.h"
const int MAX_COUNT{ 7 };
class CTorus : public CScene
{
public:
	CTorus();
	virtual~CTorus();

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
	void torusInit();
	void createTorus(int count);
	void deleteTorus();
	void floor();
	void pillar();
	void toruses();
private:
	Point m_initTrans;
	Point* m_Torus[MAX_COUNT];
	Point* m_TorusR[MAX_COUNT];
	float m_mat[16];
	bool isArrival[MAX_COUNT];
	int Count;
	float torusHeight;
	float torusRadIN;
	bool isDepth;
};

