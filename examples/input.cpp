#include "instantcg.h"
using namespace InstantCG;

bool lockCursor = false;

int main()
{
    screen();
    ColorRGB bg = RGB_Black;

    while( !done( true, false ) )
    {
        int mouseX, mouseY;
        bool LMB, RMB;
        getMouseState(mouseX, mouseY, LMB, RMB);

        horLine( mouseY, 0, w, RGB_White);
        verLine( mouseX, 0, h, RGB_White);

        if( keyDown(SDL_SCANCODE_RIGHT) ) bg = RGB_Red;
        if( keyDown(SDL_SCANCODE_LEFT ) ) bg = RGB_Green;
        if( keyDown(SDL_SCANCODE_UP   ) ) bg = RGB_Blue;
        if( keyDown(SDL_SCANCODE_DOWN ) ) bg = RGB_Black;
        if( LMB ) bg = RGB_Teal;
        if( RMB ) bg = RGB_Olive;
        if( RMB && LMB ) bg = RGB_Purple;

        if( keyDown(SDL_SCANCODE_SPACE) )
        {
            if( !lockCursor ) std::cout << "locking cursor" << std::endl;
            lockCursor = true;
        }
        else 
        {
            if( lockCursor ) std::cout << "unlocking cursor" << std::endl;
            lockCursor = false;
        }

        SDL_SetRelativeMouseMode( SDL_bool(lockCursor) );

        if( lockCursor )
        {
            
        }

        redraw();
        cls(bg);
    }

    return 0;
}


