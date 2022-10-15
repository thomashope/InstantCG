/*

InstantCG 20150401

InstantCG is a derivative work of QuickCG by Thomas Hope.
The aim is for InstantCG to be a drop in replacement for QuickCG using SDL2
and to build on QuickCG to include functionality that is only availible in
SDL2.

The below legal notice is preserved from the original QuickCG

QuickCG 20071121

Copyright (c) 2004-2007, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef INSTANTCG_H
#define INSTANTCG_H

#include <SDL.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

namespace InstantCG
{
////////////////////////////////////////////////////////////////////////////////
//useful templates//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 //usage: std::string str = valtostr(25353.91654654f);
 template<typename T>
 std::string valtostr(const T& val)
 {
     std::ostringstream sstream;
     sstream << val;
     return sstream.str();
 }

//usage: double val = stringtoval<double>("456.498.654");
 template<typename T>
 T strtoval(const std::string& s)
 {
     std::istringstream sstream(s);
     T val;
     sstream >> val;
     return val;
 }

//length is decimal precision of the floating point number
template<typename T>
std::string valtostr(const T& val, int length, bool fixed = true)
{
  std::ostringstream sstream;
  if(fixed) sstream << std::fixed;
  sstream << std::setprecision(length) << val;
  return sstream.str();
}

////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct ColorRGB8bit;
//a color with 3 components: r, g and b
struct ColorRGB
{
  int r;
  int g;
  int b;
  
  ColorRGB(Uint8 r, Uint8 g, Uint8 b);
  ColorRGB(const ColorRGB8bit& color);
  ColorRGB();
};
  
ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator*(const ColorRGB& color, int a);
ColorRGB operator*(int a, const ColorRGB& color);
ColorRGB operator/(const ColorRGB& color, int a);
bool operator==(const ColorRGB& color, const ColorRGB& color2);
bool operator!=(const ColorRGB& color, const ColorRGB& color2);

static const ColorRGB RGB_Black    (  0,   0,   0);
static const ColorRGB RGB_Red      (255,   0,   0);
static const ColorRGB RGB_Green    (  0, 255,   0);
static const ColorRGB RGB_Blue     (  0,   0, 255);
static const ColorRGB RGB_Cyan     (  0, 255, 255);
static const ColorRGB RGB_Magenta  (255,   0, 255);
static const ColorRGB RGB_Yellow   (255, 255,   0);
static const ColorRGB RGB_White    (255, 255, 255);
static const ColorRGB RGB_Gray     (128, 128, 128);
static const ColorRGB RGB_Grey     (192, 192, 192);
static const ColorRGB RGB_Maroon   (128,   0,   0);
static const ColorRGB RGB_Darkgreen(  0, 128,   0);
static const ColorRGB RGB_Navy     (  0,   0, 128);
static const ColorRGB RGB_Teal     (  0, 128, 128);
static const ColorRGB RGB_Purple   (128,   0, 128);
static const ColorRGB RGB_Olive    (128, 128,   0);

//a color with 3 components: r, g and b
struct ColorRGB8bit
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  
  ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b);
  ColorRGB8bit(const ColorRGB& color);
  ColorRGB8bit();
};
  
//a color with 3 components: h, s and l
struct ColorHSL
{
  int h;
  int s;
  int l;

  ColorHSL(Uint8 h, Uint8 s, Uint8 l);
  ColorHSL();
};

//a color with 3 components: h, s and v
struct ColorHSV
{
  int h;
  int s;
  int v;
  
  ColorHSV(Uint8 h, Uint8 s, Uint8 v);
  ColorHSV();
};

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern int w;               // the width of the window
extern int h;               // the height of the window
extern SDL_Window*   win;
extern SDL_Renderer* ren;

////////////////////////////////////////////////////////////////////////////////
//KEYBOARD FUNCTIONS////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool keyDown(SDL_Keycode key);  // checks if the key is held down, true as long as the key is held
bool keyDown(SDL_Scancode key); // checks if the key is held down, true as long as the key is held

////////////////////////////////////////////////////////////////////////////////
//BASIC SCREEN FUNCTIONS////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void screen(int width = 640, int height = 400, bool fullscreen = false, const std::string& text = " ");
void redraw();                                              // Updates the visible display
void cls(const ColorRGB& color = RGB_Black);                // Clears the screen to the given color
void pset(int x, int y, const ColorRGB& color);             // Sets a single pixel color
ColorRGB pget(int x, int y);                                // returns the pixel color 
// if your writing to the buffer[x][y] in that order leave at false
// if your using buffer[y][x] or buffer[y * width + x] set to true, true is 'faster' (i.e. takes better advantage of SDL2)
void drawBuffer(Uint32* buffer, bool swapXY = false);       // Draws an array of (w * h) pixel data to the screen
bool onScreen(int x, int y);                                // True if the given coords are inside the screen

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FUNCTIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void sleep();
void waitFrame(double oldTime, double frameDuration);       // frame duration in seconds
bool done(bool quit_if_esc = true, bool delay = true);
void end();                                                 // quits the program
void readKeys();                                            // gets the current state of the keyboard
void getMouseState(int& mouseX, int& mouseY);               // sets arguments to the current location of the mouse
void getMouseState(int& mouseX, int& mouseY, bool& LMB, bool& RMB); // sets left and right mouse button state
inline unsigned long getTicks() { return SDL_GetTicks(); }  // milliseconds since SDL was initialised
inline double getTime() { return SDL_GetTicks() / 1000.0; } // seconds since SDL was initialised

////////////////////////////////////////////////////////////////////////////////
//2D SHAPES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO change return type to bool
void horLine(int y, int x1, int x2, const ColorRGB& color); // draws a horizontal line
void verLine(int x, int y1, int y2, const ColorRGB& color); // draws a verticle line
void drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color);   // endpoints (x1, y1) (x2, y2)
bool drawCircle(int xc, int yc, int radius, const ColorRGB& color);     // circle outline at center (xc, yc)
bool drawDisk(int xc, int yc, int radius, const ColorRGB& color);       // filled circle at center (xc, yc)
void drawRect(int x1, int y1, int x2, int y2, const ColorRGB& color);   // corners   (x1, y1) (x2, y2)

////////////////////////////////////////////////////////////////////////////////
//COLOR CONVERSIONS/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ColorHSL RGBtoHSL(const ColorRGB& colorRGB);
ColorRGB HSLtoRGB(const ColorHSL& colorHSL);
ColorHSV RGBtoHSV(const ColorRGB& colorRGB);
ColorRGB HSVtoRGB(const ColorHSV& colorHSV);
Uint32   RGBtoINT(const ColorRGB& colorRGB);
ColorRGB INTtoRGB(Uint32 colorINT);

/*
////////////////////////////////////////////////////////////////////////////////
//FILE FUNCTIONS////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//TODO
void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) {}
void saveFile(const std::vector<unsigned char>& buffer, const std::string& filename) {}

////////////////////////////////////////////////////////////////////////////////
//IMAGE FUNCTIONS///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//TODO
int loadImage(std::vector<ColorRGB>& out,
              unsigned long& w,
              unsigned long& h,
              const std::string& filename)
{return 0;}
int loadImage(std::vector<Uint32>& out,
              unsigned long& w,
              unsigned long& h,
              const std::string& filename)
{return 0;}
int decodePNG(std::vector<unsigned char>& out_image_32bit,
              unsigned long& image_width,
              unsigned long& image_height,
              const unsigned char* in_png,
              unsigned long in_size)
{return 0;}
int decodePNG(std::vector<unsigned char>& out_image_32bit,
              unsigned long& image_width,
              unsigned long& image_height,
              const std::vector<unsigned char>& in_png)
{return 0;}

////////////////////////////////////////////////////////////////////////////////
//TEXT FUNCTIONS////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//TODO
extern bool font[256][8][8];
void drawLetter(unsigned char n,
                int x,
                int y,
                const ColorRGB& color = RGB_White,
                bool bg = 0,
                const ColorRGB& color2 = RGB_Black)
{}
int printString(const std::string& text,
                int x = 0,
                int y = 0,
                const ColorRGB& color = RGB_White,
                bool bg = 0,
                const ColorRGB& color2 = RGB_Black,
                int forceLength = 0)
{return 0;}

//print something (string, int, float, ...)
template<typename T>
int print(const T& val, int x = 0, int y = 0, const ColorRGB& color = RGB_White, bool bg = 0, const ColorRGB& color2 = RGB_Black, int forceLength = 0)
{
  std::string text = valtostr(val);
  return printString(text, x, y, color, bg, color2, forceLength);
}

//print some floating point number, this one allows printing floating point numbers with limited length
template<typename T>
int fprint(const T& val,
        int length,
        int x = 0,
        int y = 0,
        const ColorRGB& color = RGB_White,
        bool bg = 0,
        const ColorRGB& color2 = RGB_Black,
        int forceLength = 0)
{
  std::string text = valtostr(val, length, true);
  return printString(text, x, y, color, bg, color2, forceLength);
}

////////////////////////////////////////////////////////////////////////////////
//TEXT INPUT FUNCTIONS//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//TODO
Uint8 getInputCharacter();
void getInputString(std::string& text,
                    const std::string& message = "",
                    bool clear = false,
                    int x = 0,
                    int y = 0,
                    const ColorRGB& color = RGB_White,
                    bool bg = 0,
                    const ColorRGB& color2 = RGB_Black)
{}

template<typename T>
T getInput(const std::string& message = "",
        bool clear = false,
        int x = 0,
        int y = 0,
        const ColorRGB& color = RGB_White,
        bool bg = 0,
        const ColorRGB& color2 = RGB_Black)
{
  std::string text;
  getInputString(text, message, clear, x, y, color, bg, color2);
  return strtoval<T>(text);
}

////////////////////////////////////////////////////////////////////////////////
//SOUNDCARD FUNCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//TODO
int audioOpen(int samplerate, int framesize) {return 0;} //always 16-bit mono sound for now; returns 0 if no error happened
void audioClose() {}
int audioReOpen() {return 0;} //closes and opens again with same parameters

//push samples to the soundcard, making sure not to cause shortage or overflow
//pos and end are the range in the samples vector that you want to push to the audio card
void audioPushSamples(const std::vector<double>& samples, size_t pos, size_t end) {}

size_t audioSamplesShortage() {return 0;} //returns value > 0 if the soundcard is consuming more samples than you're producing
size_t audioSamplesOverflow() {return 0;} //returns value > 0 if you're producing more samples than the soundard is consuming - so take it easy a bit
void audioSetBufferSamplesRange(size_t min_samples, size_t max_samples) {} //set shortage and overflow values. E.g. 4096 and 8192.

//This plays the sound starting at this time, until it's done
//The difference with audioPushSamples is:
//audioPlay allows playing multiple sounds at the same time: it doesn't push at the end,
//but elementwise-adds or pushes back samples if needed.
//The duration depends on samplerate, make sure the samples in the vector have the correct samplerate.
void audioPlay(const std::vector<double>& samples) {}

void audioSetMode(int mode) {} //0: silent, 1: full (no volume calculations ==> faster), 2: volume-controlled (= default value)
void audioSetVolume(double volume) {} //multiplier used if mode is 2 (volume-controlled). Default value is 1.0.
*/
} // end of namespace InstantCG

#endif
