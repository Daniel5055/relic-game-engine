#include "Input.h"

#include "InputEvent.h"

#include "Point.h"
#include "Shape.h"

#include <SDL.h>

Framework::InputEvent Framework::Input::pollEvent()
{
    SDL_Event e;
    InputEvent e_out;

    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_QUIT:
    
        return { InputEventType::EXIT_BUTTON_PRESSED };

        break;
    
    case SDL_KEYDOWN:
        

        e_out.type = InputEventType::KEY_DOWN;

        e_out.key = e.key.keysym.sym;

        return e_out;

        break;
    case SDL_KEYUP:
        e_out.type = InputEventType::KEY_UP;

        e_out.key = e.key.keysym.sym;

        return e_out;

        break;

    case SDL_MOUSEMOTION:
        e_out;

        e_out.type = InputEventType::MOUSE_EVENT;
        e_out.mouse_event = MouseEvent::MOUSE_MOTION;
        return e_out;

        break;
   
    case SDL_MOUSEBUTTONDOWN:
        e_out;

        e_out.type = InputEventType::MOUSE_EVENT;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::LEFT_DOWN;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::RIGHT_DOWN;
        }
        
        return e_out;

        break;

    case SDL_MOUSEBUTTONUP:
        e_out;

        e_out.type = InputEventType::MOUSE_EVENT;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
            e_out.mouse_event = MouseEvent::LEFT_UP;
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            e_out.mouse_event = MouseEvent::RIGHT_UP;
        }

        return e_out;

        break;
    }


    return { InputEventType::NULL_EVENT };
}

bool Framework::Input::isInBoundary(const Point& point, const Shape& shape)
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
