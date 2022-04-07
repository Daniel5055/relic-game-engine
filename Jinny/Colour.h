#pragma once

// SDL_Dependencies
struct SDL_Color;

#include <SDL.h>

namespace framework
{
    /**
     * \brief Represents a colour using 8bit rgba values
     */
    struct Colour
    {

        Colour(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
        Colour(SDL_Color colour);

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;

        explicit operator SDL_Color() const;
    };
}
