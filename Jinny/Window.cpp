#include "Window.h"

#include "Shape.h"
#include "Point.h"

#include <SDL.h>
#include <assert.h>

framework::Window::Window(const std::string name, const int width, const int height, const bool show)
    : m_null_camera(0, 0, width, height), m_camera(m_null_camera)
{
    SDL_WindowFlags flag;
    if (show)
    {
        flag = SDL_WINDOW_SHOWN;
    }
    else
    {
        flag = SDL_WINDOW_HIDDEN;
    }

    m_window_ptr = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flag);
    assert(m_window_ptr != nullptr);
}

framework::Window::~Window()
{
    SDL_DestroyWindow(m_window_ptr);
}

unsigned int framework::Window::getWindowWidth() const
{
    int width;
    int height;
    SDL_GetWindowSize(m_window_ptr, &width, &height);
    return width;
}

unsigned int framework::Window::getWindowHeight() const
{
    int width;
    int height;
    SDL_GetWindowSize(m_window_ptr, &width, &height);
    return height;
}

void framework::Window::setCamera(const Shape camera)
{
    m_camera = camera;
}

framework::Shape framework::Window::getCamera() const
{
    return m_camera;
}

framework::Point framework::Window::getStaticMousePosition() const
{
    Point point;
    SDL_GetMouseState(&point.x, &point.y);

    return point;
}

framework::Point framework::Window::getCameraMousePosition() const
{
    // For now, return x, y + mouse position
    // Does not account for zoom

    Point point;
    SDL_GetMouseState(&point.x, &point.y);

    point.x += m_camera.x;
    point.y += m_camera.y;

    return point;
}