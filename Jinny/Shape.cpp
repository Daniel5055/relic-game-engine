#include "Shape.h"

// SDL
#include <SDL.h>

// Local Dependencies
#include "Point.h"

namespace Framework
{
	Shape::Shape(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		is_screen_bound = false;
	}

	Shape::Shape(Point position)
	{
		x = position.x;
		y = position.y;

		w = 0;
		h = 0;

		is_screen_bound = false;
	}

	Shape::Shape(Point position, Point size)
	{
		x = position.x;
		y = position.y;
		w = size.x;
		h = size.y;

		is_screen_bound = false;
	}

	Shape::Shape(SDL_Rect rect)
	{
		x = rect.x;
		y = rect.y;
		w = rect.w;
		h = rect.h;

		is_screen_bound = false;
	}

	Shape::operator SDL_Rect() const
	{
		return { x, y, w, h };
	}

}
