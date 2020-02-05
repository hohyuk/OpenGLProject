#pragma once

class CSceneMgr;	// 전방 선언

class CGLFrameWork
{
public:
	CGLFrameWork();
	~CGLFrameWork();

	void init(int argc, char* argv[], int WinWidth, int WinHeight, int WinX_, int WinY_
		, const char* WinCaption, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	void update(int value);
	void draw();
	void render();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void special(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void freemotion(int x, int y);
	void run();

	using DrawFunc = void(*)();
	using ReshapeFunc = void(*)(int, int);
	using TimerFunc = void(*)(int);
	using KeyboardFunc = void(*)(unsigned char key, int x, int y);
	using MouseFunc = void(*)(int button, int state, int x, int y);
	using MotionFunc = void(*)(int x, int y);
	using SpecialFunc = void(*)(int key, int x, int y);

	void regDrawFunction(DrawFunc draw) { fnDraw = draw; }
	void regReshapeFunction(ReshapeFunc reshape) { fnReshape = reshape; }
	void regTimerFunction(TimerFunc timer) { fnTimer = timer; }
	void regKeyboardFunction(KeyboardFunc keyboard) { fnKeyboard = keyboard; }
	void regMouseFunction(MouseFunc mouse) { fnMouse = mouse; }
	void regMotionFunction(MotionFunc motion, MotionFunc freemotion)
	{
		fnMotion = motion;
		fnFreeMotion = freemotion;
	}

	void regSpecialFunction(SpecialFunc special) { fnSpecial = special; }

	void BindFunctions()
	{
		glutDisplayFunc(fnDraw);
		glutReshapeFunc(fnReshape);
		glutKeyboardFunc(fnKeyboard);
		glutMouseFunc(fnMouse);
		glutMotionFunc(fnMotion);
		glutPassiveMotionFunc(fnFreeMotion);
		glutSpecialFunc(fnSpecial);
		glutTimerFunc(m_fps, fnTimer, 1);
	}

private:
	DrawFunc fnDraw{ nullptr };
	ReshapeFunc fnReshape{ nullptr };
	TimerFunc fnTimer{ nullptr };
	KeyboardFunc fnKeyboard{ nullptr };
	MouseFunc fnMouse{ nullptr };
	MotionFunc fnMotion{ nullptr };
	MotionFunc fnFreeMotion{ nullptr };
	SpecialFunc fnSpecial{ nullptr };

private:
	int m_fps = 16;
	CSceneMgr* m_SceneMgr{ nullptr };
	Point m_Camera;
	Point m_Rotate;
	bool isProject;
};