#include "stdafx.h"
#include "CGLFrameWork.h"

namespace
{
	CGLFrameWork framework;
}
int main(int argc, char* argv[])
{
	framework.init(argc, argv, WinX, WinY, 100, 100, "Example23");

	framework.regDrawFunction([]() {framework.draw(); });
	framework.regReshapeFunction([](int w, int h) {framework.reshape(w, h); });
	framework.regTimerFunction([](int value) {framework.update(value); });
	framework.regKeyboardFunction([](unsigned char key, int x, int y) {framework.keyboard(key, x, y); });
	framework.regSpecialFunction([](int key, int x, int y) {framework.special(key, x, y); });
	framework.regMouseFunction([](int button, int state, int x, int y) {framework.mouse(button, state, x, y); });
	framework.regMotionFunction([](int x, int y) {framework.motion(x, y); }
	, [](int x, int y) {framework.freemotion(x, y); });

	framework.BindFunctions();

	framework.run();
	return 0;
}