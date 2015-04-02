#include "InstantCG.h"
using namespace InstantCG;

// THIS IS ALL TAKEN FROM http://lodev.org

int main(int argc, char *argv[]) 
{ 
    screen(256, 256, 0, "Texture Examples"); 
   
    // black and white XOR texture
    for(int x = 0; x < w; x++) 
    for(int y = 0; y < h; y++) 
    {    
         Uint8 c = x ^ y; 
         pset(x, y, ColorRGB(c, c, c)); 
    } 
   
    redraw(); 
    sleep();

    // Colors!
    ColorRGB color;
      
    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {   
         Uint8 c = (x ^ y);
         color = HSVtoRGB(ColorHSV(c, 255, 255));
         pset(x, y, color);
    }
      
    // and a bit of a triangle
    redraw();
    sleep();

    cls();

    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {
        if(x & y) pset(x, y, RGB_White);
    }    
    redraw();
    sleep();

    return 0; 
}