#include "Point.h"

#include <SDL.h>


Framework::Point::Point(int x, int y)
	:x(x), y(y)
{

}

Framework::Point::Point(SDL_Point point)
{
	x = point.x;
	y = point.y;
}
