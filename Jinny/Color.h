#pragma once

// SDL_Dependencies
struct SDL_Color;

#include <SDL.h>

namespace framework
{
    struct Color
    {

        Color(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
        Color(SDL_Color color);

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;

        operator SDL_Color() const;


    };
}
