#pragma once

namespace Framework
{
    struct Shape;
    struct Point;

    struct InputEvent;

    /**
     * Framework class containing useful input related methods.
     */
    class Input
    {
    public:
        // For polling events in the program
        InputEvent pollEvent() const;

        // Checking if a point is within a shape
        bool isInBoundary(const Point& point, const Shape& shape) const;
    };
}


