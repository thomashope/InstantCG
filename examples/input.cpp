#include "instantcg.h"
using namespace InstantCG;

int main()
{
    screen();
    ColorRGB bg = RGB_Black;

    while( !done( true, false ) )
    {
        int mouseX, mouseY;
        getMouseState(mouseX, mouseY);

        horLine( mouseY, 0, w, RGB_White);
        verLine( mouseX, 0, h, RGB_White);

        if( keyDown(SDL_SCANCODE_RIGHT) ) bg = RGB_Red;
        if( keyDown(SDL_SCANCODE_LEFT ) ) bg = RGB_Green;
        if( keyDown(SDL_SCANCODE_UP   ) ) bg = RGB_Blue;
        if( keyDown(SDL_SCANCODE_DOWN ) ) bg = RGB_Black;

        redraw();
        cls(bg);
    }

    return 0;
}
