#include "CGlFrameWork.h"

namespace
{
	CGlFrameWork framework;
}

int main(int argc, char* argv[])
{
	framework.GlutInitialize(argc, argv, WinX, WinY, 100, 100, "example13");
	framework.RegisterDrawFunction([]() {framework.DrawScene(); });
	framework.RegisterReshapeFunction([](int w, int h) {framework.Reshape(w, h); });
	framework.RegisterTimerFunction([](int value) {framework.Timer(value); });
	framework.RegisterMouseFunction([](int button, int state, int x, int y)
	{framework.Mouse(button, state, x, y); });
	framework.RegisterKeyFunction([](unsigned char key, int x, int y)
	{framework.Keyboard(key, x, y); });
	framework.RegisterSpecialKeyFunction([](int key, int x, int y)
	{framework.SpecialKeyboard(key, x, y); });

	framework.Bind();

	framework.Run();
	return 0;
}