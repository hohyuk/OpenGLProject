#pragma once
#include "CScene.h"

enum E_Model
{
	E_Solid,
	E_Wire
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
	void mainsphere();
	void course1();
	void course2();
	void course3();
	void model(E_Model e_model, double rad, int slice, int stack);
private:
	float m_move;
	float m_mainR;
	float m_mainSpeed;
	float m_co1R;
	float m_mini1;
	float m_co2R;
	float m_mini2;
	float m_co3R;
	float m_mini3;
	E_Model m_model;
};

