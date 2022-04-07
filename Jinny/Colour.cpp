#include "Colour.h"

#include <SDL.h>


framework::Colour::Colour(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) : r(r), g(g), b(b), a(a)
{
}

framework::Colour::Colour(const SDL_Color colour) : r(colour.r), g(colour.g), b(colour.b), a(colour.a)
{
}

framework::Colour::operator SDL_Color() const
{
    return { r, g, b, a };
}
