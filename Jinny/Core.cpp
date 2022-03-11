#include "Core.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool Framework::Core::initialize()
{
	// Initialize SDL Versions
	if (SDL_Init(SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		return false;
	}

	int png_ID = IMG_INIT_PNG;
	if (!(IMG_Init(png_ID) & png_ID))
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}
    return true;
}

void Framework::Core::close()
{
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
