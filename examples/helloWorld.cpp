#include "instantcg.h"
using namespace InstantCG;

int main()
{

	screen(256, 256, false, "Hello World!");
    ColorRGB bgColor;

	while( !done() )
	{
        bgColor.r = std::rand()&0xff;
        bgColor.g = std::rand()&0xff;
        bgColor.b = std::rand()&0xff;

        cls( bgColor );
        redraw();
	}

	return 0;
}
