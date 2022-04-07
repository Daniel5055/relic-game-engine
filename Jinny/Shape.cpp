#include "Shape.h"

// SDL
#include <SDL.h>

// Local Dependencies
#include "Point.h"

namespace framework
{
    Shape::Shape(const int x, const int y, const int w, const int h) : x(x), y(y), h(h), w(w)
    {
    }

    Shape::Shape(const Point position) : x(position.x), y(position.y), h(0), w(0)
    {
    }

    Shape::Shape(const Point position, const Point size) : x(position.x), y(position.y), h(size.y), w(size.x)
    {
    }

    Shape::Shape(SDL_Rect rect) : x(rect.x), y(rect.y), h(rect.h), w(rect.w)
    {
    }

    Shape::operator SDL_Rect() const
    {
        return { x, y, w, h };
    }

}
