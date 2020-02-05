#include "stdafx.h"
#include "CGLFrameWork.h"
using namespace std;

namespace
{
	CGLFrameWork framework;
}

int main(int argc, char* argv[])
{
	framework.Init(argc, argv, WinX, WinY, 100, 100, "Example18");

	framework.regDrawFunction([]() {framework.Draw(); });
	framework.regReshapeFunction([](int w, int h) {framework.Reshape(w, h); });
	framework.regTimerFunction([](int value) {framework.Update(value); });
	framework.regKeyboardFunction([](unsigned char key, int x, int y) {framework.Keyboard(key, x, y); });
	framework.regSpecialFunction([](int key, int x, int y) {framework.Special(key, x, y); });
	framework.regMouseFunction([](int button, int state, int x, int y) {framework.Mouse(button, state, x, y); });
	framework.regMotionFunction([](int x, int y) {framework.Motion(x, y); }
	, [](int x, int y) {framework.FreeMotion(x, y); });

	framework.BindFunctions();

	framework.Run();
	return 0;
}