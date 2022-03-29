#include "Window.h"

#include "Shape.h"
#include "Point.h"

#include <SDL.h>
#include <assert.h>

Framework::Window::Window(std::string t_name, int t_width, int t_height, bool t_show)
    : m_null_camera(0, 0, t_width, t_height), m_camera(m_null_camera)
{
    SDL_WindowFlags flag;
    if (t_show)
    {
        flag = SDL_WINDOW_SHOWN;
    }
    else
    {
        flag = SDL_WINDOW_HIDDEN;
    }

    m_window_ptr = SDL_CreateWindow(t_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, t_width, t_height, flag);
    assert(m_window_ptr != nullptr);
}

Framework::Window::~Window()
{
    SDL_DestroyWindow(m_window_ptr);
}

unsigned int Framework::Window::getWindowWidth() const
{
    int width;
    int height;
    SDL_GetWindowSize(m_window_ptr, &width, &height);
    return width;
}

unsigned int Framework::Window::getWindowHeight() const
{
    int width;
    int height;
    SDL_GetWindowSize(m_window_ptr, &width, &height);
    return height;
    return 0;
}

void Framework::Window::setCamera(Shape camera)
{
    m_camera = camera;
}

Framework::Shape Framework::Window::getCamera() const
{
    return m_camera;
}

Framework::Point Framework::Window::getStaticMousePosition() const
{
    Point point;
    SDL_GetMouseState(&point.x, &point.y);

    return point;
}

Framework::Point Framework::Window::getCameraMousePosition() const
{
    // For now, return x, y + mouse position
    // Does not account for zoom

    Point point;
    SDL_GetMouseState(&point.x, &point.y);

    point.x += m_camera.x;
    point.y += m_camera.y;

    return point;
}