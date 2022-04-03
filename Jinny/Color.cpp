#include "Color.h"

#include <SDL.h>


framework::Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

framework::Color::Color(SDL_Color color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

framework::Color::operator SDL_Color() const
{
    return { r, g, b, a };
}
