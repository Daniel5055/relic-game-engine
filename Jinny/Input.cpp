#include "Input.h"

#include "InputEvent.h"

#include "Point.h"
#include "Shape.h"

#include <SDL.h>

Framework::InputEvent Framework::Input::pollEvent() const
{
    SDL_Event e;
    InputEvent e_out;

    // Poll events
    SDL_PollEvent(&e);

    // Read the SDL events and return them as wrapped InputEvents
    switch (e.type)
    {
    case SDL_QUIT:
        e_out.type = InputEventType::EXIT_BUTTON_PRESSED;
        break;
    
    case SDL_KEYDOWN:
        e_out.type = InputEventType::KEY_DOWN;
        e_out.key = e.key.keysym.sym;
        break;

    case SDL_KEYUP:
        e_out.type = InputEventType::KEY_UP;
        e_out.key = e.key.keysym.sym;
        break;

    case SDL_MOUSEMOTION:
        e_out.type = InputEventType::MOUSE_EVENT;
        e_out.mouse_event = MouseEvent::MOUSE_MOTION;
        break;
   
    case SDL_MOUSEBUTTONDOWN:
        e_out.type = InputEventType::MOUSE_EVENT;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::LEFT_DOWN;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::RIGHT_DOWN;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        e_out.type = InputEventType::MOUSE_EVENT;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::LEFT_UP;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::RIGHT_UP;
        }
        break;
    default:
        e_out.type = InputEventType::NULL_EVENT;
        break;
    }

    return e_out;
}

bool Framework::Input::isInBoundary(const Point& point, const Shape& shape) const
{
    bool inside = true;

    if (point.x < shape.x)
    {
        inside = false;
    }
    else if (point.x > shape.x + shape.w)
    {
        inside = false;
    }
    else if (point.y < shape.y)
    {
        inside = false;
    }
    else if (point.y > shape.y + shape.h)
    {
        inside = false;
    }

    return inside;
}
