#include "InstantCG.h"
using namespace InstantCG;

// THIS IS ALL TAKEN FROM http://lodev.org
#define width 256
#define height 256

double noise[width][height]; //the noise array

void generateNoise();
double smoothNoise(double x, double y);
double turbulence(double x, double y, double size);

int main(int argc, char *argv[]) 
{ 

    screen(256, 256, 0, "Texture Examples"); 

    generateNoise();
    
    ColorRGB color;
     
    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {     
        //color.r = color.g = color.b = Uint8(256 * noise[x][y]);
        //color.r = color.g = color.b = Uint8(256 * noise[x / 8][y / 8]);
        //color.r = color.g = color.b = Uint8(256 * smoothNoise(x / 8.0, y / 8.0));
        color.r = color.g = color.b = Uint8(turbulence(x, y, 64));
        pset(x, y, color);
    }  
    
    redraw();
    sleep();
   
    // black and white XOR texture
    for(int x = 0; x < w; x++) 
    for(int y = 0; y < h; y++) 
    {    
         Uint8 c = x ^ y; 
         pset(x, y, ColorRGB(c, c, c)); 
    } 
   
    redraw(); 
    sleep();
      
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

void generateNoise()
{
    for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++)
    {
        noise[x][y] = (rand() % 32768) / 32768.0;
    }
}

double smoothNoise(double x, double y)
{  
   //get fractional part of x and y
   double fractX = x - int(x);
   double fractY = y - int(y);
   
   //wrap around
   int x1 = (int(x) + width) % width;
   int y1 = (int(y) + height) % height;
   
   //neighbor values
   int x2 = (x1 + width - 1) % width;
   int y2 = (y1 + height - 1) % height;

   //smooth the noise with bilinear interpolation
   double value = 0.0;
   value += fractX       * fractY       * noise[x1][y1];
   value += fractX       * (1 - fractY) * noise[x1][y2];
   value += (1 - fractX) * fractY       * noise[x2][y1];
   value += (1 - fractX) * (1 - fractY) * noise[x2][y2];

   return value;
}

double turbulence(double x, double y, double size)
{
    double value = 0.0, initialSize = size;
    
    while(size >= 1)
    {
        value += smoothNoise(x / size, y / size) * size;
        size /= 2.0;
    }
    
    return(128.0 * value / initialSize);
}