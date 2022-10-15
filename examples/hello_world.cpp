#include "instantcg.h"

using namespace InstantCG;

int main(int argc, char* argv[])
{
    screen(256, 256, 0, "Small Test Script");
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
            pset(x, y, ColorRGB(x, y, 128));
        }
    redraw();
    sleep();
    return 0;
}
