#include "Point.h"

#include <SDL.h>


framework::Point::Point(int x, int y)
    :x(x), y(y)
{

}

framework::Point::Point(SDL_Point point)
{
    x = point.x;
    y = point.y;
}
