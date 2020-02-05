#pragma once

class CScene;		// 전방 선언

class CGLFrameWork
{
public:
	CGLFrameWork();
	~CGLFrameWork();

	void Init(int argc, char* argv[], int WinWidth, int WinHeight, int WinX, int WinY
		, const char* WinCaption, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	void Run();
	void Draw();
	void Render();
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void Motion(int x, int y);
	void FreeMotion(int x, int y);
	void Special(int key, int x, int y);
	void Update(int value);

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

	void toScene(CScene* newScene)
	{
		auto old = m_CurrScene;
		m_CurrScene = newScene;
		delete old;
	}
private:
	int	m_fps = 16;
	bool m_projection;
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
	CScene* m_CurrScene{ nullptr };
};

