#include "Window.h"

#include "Shape.h"
#include "Point.h"

#include <SDL.h>

void Framework::Window::initialize(std::string name, int width, int height, bool show)
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

	m_null_camera = new Shape(0, 0, width, height);
	m_camera = m_null_camera;
}

void Framework::Window::close()
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

void Framework::Window::setCamera(Shape* camera)
{
	m_camera = camera;
}

Framework::Shape* Framework::Window::getCamera()
{
	return m_camera;
}

Framework::Point Framework::Window::getStaticMousePosition()
{
	Point point;
	SDL_GetMouseState(&point.x, &point.y);

	return point;
}

Framework::Point Framework::Window::getCameraMousePosition()
{
	// For now, return x, y + mouse position
	// Does not account for zoom

	Point point;
	SDL_GetMouseState(&point.x, &point.y);

	point.x += m_camera->x;
	point.y += m_camera->y;

	return point;
}