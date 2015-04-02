#include "InstantCG.h"
using namespace InstantCG;

const int WIDTH = 640;
const int HEIGHT = 480;

Uint32 buffer[WIDTH][HEIGHT];

int main()
{
	screen(WIDTH, HEIGHT);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			buffer[x][y] = 0xffffff;
			if (y < 10) buffer[x][y] = 0xff00ff;
			//if (y > h-10) buffer[x][y] = 0xff00ff;
		}
	}
	
	while (!done())
	{
		redraw();
		cls();

		drawBuffer(buffer[0]);
	}

	return 0;
}