#pragma once

namespace Framework
{
	struct Shape;
	struct Point;

	struct InputEvent;

	class Input
	{
	public:
		InputEvent pollEvent();

		bool isInBoundary(const Point& point, const Shape& shape);
	};
}


