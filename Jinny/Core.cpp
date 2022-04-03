#include "Core.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cassert>

framework::Core::Core()
{
    // Initialize SDL Versions
    assert(SDL_Init(SDL_Init(SDL_INIT_VIDEO)) >= 0);

    int png_id = IMG_INIT_PNG;
    assert((IMG_Init(png_id) & png_id));

    assert(TTF_Init() != -1);
}

framework::Core::~Core()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
