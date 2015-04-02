#include "InstantCG.h"
using namespace InstantCG;

int main(int argc, char *argv[]) 
{ 
    screen(256, 256, 0, "The XOR Texture"); 
   
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
      
    redraw();
    sleep();

    return 0; 
}