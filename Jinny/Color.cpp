#include "Color.h"

#include <SDL.h>


Framework::Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Framework::Color::Color(SDL_Color color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

Framework::Color::operator SDL_Color() const
{
    return { r, g, b, a };
}
