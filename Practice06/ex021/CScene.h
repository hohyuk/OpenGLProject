#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void init() {}
	virtual void run() {}
	virtual void render() {}
	virtual void reshape(int w, int h) {}
	virtual void keyboard(unsigned char key, int x, int y) {}
	virtual void mouse(int button, int state, int x, int y) {}
	virtual void motion(int x, int y) {}
	virtual void freemotion(int x, int y) {}
	virtual void special(int key, int x, int y) {}
	virtual void update(int value) {}
protected:
	Point m_Info;
	Point m_Rotate;
	Point m_Translate;
	Point m_Camera;
	float m_Angle;
	float m_moveX;
	float m_moveY;
	float m_Scale;
	float m_Speed;
	const float m_PI{ 3.141592f };
};