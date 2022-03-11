#pragma once

// SDL Dependencies
struct SDL_Point;

namespace Framework
{
	
	struct Point
	{
		Point(int x = 0, int y = 0);
		Point(SDL_Point point);

		int x;
		int y;
	};
}



