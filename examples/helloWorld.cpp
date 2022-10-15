#include "instantcg.h"

using namespace InstantCG;

int mouseX = 0, mouseY = 0;
float x = 128, y = 128;
float curTime = 0, oldTime = 0, dt = 1/50.0;

const int WIDTH = 512;
const int HEIGHT = 512;

Uint32 buffer[WIDTH * HEIGHT];

int main(int argc, char** argv)
{
	screen(WIDTH, HEIGHT, false, "Hello World!");
 
    while( !done(true, false) )
    {
        // set the old time to the time of the prevous loop
        oldTime = curTime;
        curTime = getTime();        // get the current time 
        dt = (curTime - oldTime);   // get delta time

        for( int x = 0; x < w; x++ )
        for( int y = 0; y < h; y++ )
        {
            buffer[y*WIDTH+x] = RGBtoINT(ColorRGB(x/2, y/2, 128));
        }
        drawBuffer(buffer, true);

        // if an arrow key is pressed, move the circle in it's direction 
        float speed = 40 * dt;
        if( keyDown(SDL_SCANCODE_RIGHT) ) { x += speed; }
        if( keyDown(SDL_SCANCODE_LEFT ) ) { x -= speed; }
        if( keyDown(SDL_SCANCODE_DOWN ) ) { y += speed; }
        if( keyDown(SDL_SCANCODE_UP   ) ) { y -= speed; }

        redraw();
    }
	return 0;
}
