#include "Core.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <assert.h>

Framework::Core::Core()
{
    // Initialize SDL Versions
    assert(SDL_Init(SDL_Init(SDL_INIT_VIDEO)) >= 0);

    int png_ID = IMG_INIT_PNG;
    assert((IMG_Init(png_ID) & png_ID));

    assert(TTF_Init() != -1);
}

Framework::Core::~Core()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
