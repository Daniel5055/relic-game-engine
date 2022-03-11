#pragma once

#include <string>

// SDL Dependencies
struct SDL_Window;
namespace Framework
{
	struct Shape;
	struct Point;

	class Window
	{
	public:
		friend class Graphics;

		// Initialization and Closing
		void initialize(std::string name, int width, int height, bool show);
		void close();

		// Size accessors
		unsigned int getWindowWidth() const;
		unsigned int getWindowHeight() const;

		// Camera Accessors
		void setCamera(Shape* camera);
		Shape* getCamera();

		Point getStaticMousePosition();
		Point getCameraMousePosition();

	private:
		SDL_Window* m_window_ptr;

		Shape* m_camera;
		Shape* m_null_camera;
	};
}


