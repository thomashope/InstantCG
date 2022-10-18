#include "InstantCG.h"
using namespace InstantCG;

#define noiseWidth 192
#define noiseHeight 192
#define noiseDepth 64

double noise[noiseDepth][noiseHeight][noiseWidth]; //the noise array

void generateNoise();
double turbulence(double x, double y, double z, double size);

int main(int argc, char *argv[])
{
  screen(noiseWidth, noiseHeight, 0, "3D Random Noise");
  generateNoise();

  Uint8 L;
  ColorRGB color;
  double t;

  while(!done())
  {
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
      L = 192 + Uint8(turbulence(x, y, t, 32)) / 4;
      color = HSLtoRGB(ColorHSL(169, 255, L));

      pset(x, y, color);

    }
    t = getTicks() / 40.0;
    redraw();
  }
  return 0;
}

void generateNoise()
{
  for(int z = 0; z < noiseDepth; z++)
  for(int y = 0; y < noiseHeight; y++)
  for(int x = 0; x < noiseWidth; x++)
  {
    noise[z][y][x] = (rand() % 32768) / 32768.0;
  }
}

double smoothNoise(double x, double y, double z)
{
  //get fractional part of x and y
  double fractX = x - int(x);
  double fractY = y - int(y);
  double fractZ = z - int(z);

  //wrap around
  int x1 = (int(x) + noiseWidth) % noiseWidth;
  int y1 = (int(y) + noiseHeight) % noiseHeight;
  int z1 = (int(z) + noiseDepth) % noiseDepth;

  //neighbor values
  int x2 = (x1 + noiseWidth - 1) % noiseWidth;
  int y2 = (y1 + noiseHeight - 1) % noiseHeight;
  int z2 = (z1 + noiseDepth - 1) % noiseDepth;

  //smooth the noise with bilinear interpolation
  double value = 0.0;
  value += fractX     * fractY     * fractZ     * noise[z1][y1][x1];
  value += fractX     * (1 - fractY) * fractZ     * noise[z1][y2][x1];
  value += (1 - fractX) * fractY     * fractZ     * noise[z1][y1][x2];
  value += (1 - fractX) * (1 - fractY) * fractZ     * noise[z1][y2][x2];

  value += fractX     * fractY     * (1 - fractZ) * noise[z2][y1][x1];
  value += fractX     * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x1];
  value += (1 - fractX) * fractY     * (1 - fractZ) * noise[z2][y1][x2];
  value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x2];

  return value;
}

double turbulence(double x, double y, double z, double size)
{
  double value = 0.0, initialSize = size;

  while(size >= 1)
  {
    value += smoothNoise(x / size, y / size, z / size) * size;
    size /= 2.0;
  }

  return(128.0 * value / initialSize);
}
