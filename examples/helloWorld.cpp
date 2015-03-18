#include "instantcg.h"
using namespace InstantCG;

int main()
{

	screen(256, 256, false, "Hello World!");

	while( !done() )
	{


		SDL_SetRenderDrawColor(ren, std::rand()&0xff, std::rand()&0xff, std::rand()&0xff, 255);
    	SDL_RenderClear(ren);
		SDL_RenderPresent(ren);

	}

	return 0;
}
