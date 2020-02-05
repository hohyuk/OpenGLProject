#pragma once
#include "CObj.h"

const int MAX_SNOW{ 200 };
const int MAX_MARK{ 300 };
class CSnow : public CObj
{
public:
	CSnow();
	virtual ~CSnow();

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
	bool CreateSnow();
	bool CreateMark(Point*& snow);
private:
	Point* m_snow[MAX_SNOW];
	Point* m_mark[MAX_MARK];
	float speed;
	float createTime;
	float color;
	bool isStart;
};