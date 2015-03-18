//
// InstantCG is a modified version of QuickCG
//
//

/*
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

#include "instantcg.h"

namespace InstantCG
{

////////////////////////////////////////////////////////////////////////////////
//VARIABLES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int w; //width of the screen
int h; //height of the screen
SDL_Window*   win; //The window
SDL_Renderer* ren; //The renderer

SDL_Event event = {0};

////////////////////////////////////////////////////////////////////////////////
//BASIC SCREEN FUNCTIONS////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//The screen function: sets up the window for 32-bit color graphics.
//Creates a graphical screen of width*height pixels in 32-bit color.
//Set fullscreen to 0 for a window, or to 1 for fullscreen output
//text is the caption or title of the window
//also inits SDL
void screen(int width, int height, bool fullscreen, const std::string& text)
{
	w = width;
	h = height;


	// TODO: add fullscreen option
	// TODO: add error handeling
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(text.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FUNCTIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Returns 1 if you close the window or press the escape key. Also handles everything thats needed per frame.
bool done(bool quit_if_esc, bool delay)
{
	if (delay) SDL_Delay(5); //So it consumes less processing power
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return true;
		if (quit_if_esc &&
			event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE) return true;
	}
	return false;
}

//Ends the program
void end()
{
	SDL_Quit();
	std::exit(1);
}

} // end of namespace InstantCG



