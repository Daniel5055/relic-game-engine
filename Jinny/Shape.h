#pragma once

// Encapsulation of SDL concepts for better strucutre

// SDL Dependencies
struct SDL_Rect;
namespace Framework
{
	struct Point;

	struct Shape
	{

		// Constructor
		Shape(int x = 0, int y = 0, int w = 0, int h = 0);
		Shape(Point position);
		Shape(Point position, Point size);
		Shape(SDL_Rect rect);

		operator SDL_Rect() const;

		// Values
		int x;
		int y;
		int h;
		int w;

		// Refers to if coordinates are screen coordinates, else are world coordinates
		bool is_screen_bound;
	};
}