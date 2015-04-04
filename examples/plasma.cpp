#include "InstantCG.h"
using namespace InstantCG;

#define dist(a, b, c, d) sqrt(double((a - c) * (a - c) + (b - d) * (b - d)))

/*
int main(int argc, char *argv[])
{
    screen(256, 256, 0, "Plasma");
    double time;
    while(!done())
    {
        //time = getTicks() / 50.0;
        time++;

        for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            double value = sin(dist(x + time, y, 128.0, 128.0) / 8.0)
                         + sin(dist(x, y, 64.0, 64.0) / 8.0)
                         + sin(dist(x, y + time / 7, 192.0, 64) / 7.0)
                         + sin(dist(x, y, 192.0, 100.0) / 8.0);
            int color = int((4 + value)) * 32;
            pset(x, y, ColorRGB(color, color * 2, 255 - color));
        }   
        redraw();
    }
    return(0);
}
*/


#define screenWidth 256
#define screenHeight 256

int plasma[screenWidth][screenHeight];
Uint32 buffer[screenWidth][screenHeight];
int palette[256];
	
int main(int argc, char *argv[])
{
	screen(screenWidth, screenHeight, 0, "Plasma");
   
    //generate the palette
    ColorRGB colorRGB;
    for(int x = 0; x < 256; x++)
    {
        //use HSVtoRGB to vary the Hue of the color through the palette
        colorRGB = HSVtoRGB(ColorHSV(x, 255, 255));
        palette[x] = RGBtoINT(colorRGB);
    }   
      
    //generate the plasma once
    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {
        //the plasma buffer is a sum of sines
        int color = int
        (
              128.0 + (128.0 * sin(x / 16.0))
            + 128.0 + (128.0 * sin(y / 32.0))
            + 128.0 + (128.0 * sin(sqrt(double((x - w / 2.0)* (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0))) / 8.0))
            + 128.0 + (128.0 * sin(sqrt(double(x * x + y * y)) / 8.0))
        ) / 4;
        plasma[x][y] = color;   
    }

    int paletteShift;
   
    //start the animation loop, it rotates the palette
    while(!done())
    {
        //the parameter to shift the palette varies with time
        paletteShift = int(getTicks() / 10.0);
       
        //draw every pixel again, with the shifted palette color
        for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            buffer[x][y]=palette[(plasma[x][y] + paletteShift) % 256];      
        }
       
        //make everything visible
        drawBuffer(buffer[0]);   
        redraw();
    }   

    return(0);
}
