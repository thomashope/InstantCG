#include "InstantCG.h"
using namespace InstantCG;

const int WIDTH = 640;
const int HEIGHT = 480;

int main ()
{
	screen(WIDTH, HEIGHT);

	while (!done())
	{
		redraw();
		cls();
	}

	return 0;
}