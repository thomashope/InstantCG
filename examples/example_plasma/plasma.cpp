#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "instantcg.h"
using namespace InstantCG;

#define screenWidth 256
#define screenHeight 256

// Y-coordinate first because we use horizontal scanlines
Uint32 plasma[screenHeight][screenWidth];
Uint32 buffer[screenHeight][screenWidth];
Uint32 palette[256];

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
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  {
    //the plasma buffer is a sum of sines
    int color = int
    (
        128.0 + (128.0 * sin(x / 16.0))
      + 128.0 + (128.0 * sin(y / 16.0))
    ) / 2;
    plasma[y][x] = color;
  }

  int paletteShift;

  //start the animation loop, it rotates the palette
  while(!done())
  {
    //the parameter to shift the palette varies with time
    paletteShift = int(getTicks() / 10.0);

    //draw every pixel again, with the shifted palette color
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
      buffer[y][x] = palette[(plasma[y][x] + paletteShift) % 256];
    }

    //make everything visible
    drawBuffer(buffer[0]);
    redraw();
  }

  return(0);
}
