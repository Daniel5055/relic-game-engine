#include "Input.h"

#include "InputEvent.h"

#include "Point.h"
#include "Shape.h"

#include <SDL.h>

framework::InputEvent framework::Input::pollEvent() const
{
    SDL_Event e;
    InputEvent e_out;

    // Poll events
    SDL_PollEvent(&e);

    // Read the SDL events and return them as wrapped InputEvents
    switch (e.type)
    {
    case SDL_QUIT:
        e_out.type = InputEventType::exit_button_pressed;
        break;
    
    case SDL_KEYDOWN:
        e_out.type = InputEventType::key_down;
        e_out.key = e.key.keysym.sym;
        break;

    case SDL_KEYUP:
        e_out.type = InputEventType::key_up;
        e_out.key = e.key.keysym.sym;
        break;

    case SDL_MOUSEMOTION:
        e_out.type = InputEventType::mouse_event;
        e_out.mouse_event = MouseEvent::mouse_motion;
        break;
   
    case SDL_MOUSEBUTTONDOWN:
        e_out.type = InputEventType::mouse_event;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::left_down;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::right_down;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        e_out.type = InputEventType::mouse_event;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::left_up;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::right_up;
        }
        break;
    default:
        e_out.type = InputEventType::null_event;
        break;
    }

    return e_out;
}

bool framework::Input::isInBoundary(const Point& point, const Shape& shape) const
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
