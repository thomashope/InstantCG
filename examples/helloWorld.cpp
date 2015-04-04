#include "instantcg.h"
using namespace InstantCG;

int mouseX = 0;
int mouseY = 0;

int main()
{

	screen(256, 256, false, "Hello World!");
    ColorRGB bgColor, sample;

	while( !done() )
	{
        bgColor.r = std::rand()&0xff;
        bgColor.g = std::rand()&0xff;
        bgColor.b = std::rand()&0xff;
        cls( bgColor );
        
        horLine(128, 0, 255, RGB_White);
        verLine(128, 0, 255, RGB_White);
        drawRect(100, 0, 140, 40, RGB_Green);
        drawRect(100, 40, 140, 80, RGB_Yellow);

        if (keyDown(SDLK_SPACE))
        {
            cls(RGB_Black);
            drawRect(0, 0, 20, 40, RGB_Blue);
        }
        
        if (keyDown(SDL_SCANCODE_M)) {
            getMouseState(mouseX, mouseY);

            std::cout << "mouse: " << mouseX << ", " << mouseY << std::endl;

            sample = pget(mouseX, mouseY);

            drawRect(0, 0, 24, 44, RGB_Black);
            drawRect(0, 0, 20, 40, sample);
        }

        redraw();
        cls();
	}

	return 0;
}
