#pragma once
#include "CScene.h"

class CAirplane : public CScene
{
public:
	CAirplane();
	virtual ~CAirplane();
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
	void airplanebody();
	void airplanehead();
	void airplanewing(float x,float y,float z,float angle);
	void airplanerotor();
	void airplanetail(float x, float y, float z);
	void airplaneengle(float scale,float pos,float& angle,int count_);
	void colorupdate();

	float rotorAngle;
	float airAngle;
	float engineAngle;
};