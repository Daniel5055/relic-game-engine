#pragma once

#include <string>

#include "Shape.h" 
#include "Point.h"

// SDL Dependencies
struct SDL_Window;

namespace framework
{

    /**
     * Framework class relating to the main window of the program.
     */
    class Window
    {
    public:
        friend class Graphics;

        // Initialisation and Closing
        explicit Window(std::string name, int width, int height, bool show);
        ~Window();


        // Size accessors
        unsigned int getWindowWidth() const;
        unsigned int getWindowHeight() const;

        // Camera Accessors
        void setCamera(const Shape camera);
        Shape getCamera() const;

        Point getStaticMousePosition() const;
        Point getCameraMousePosition() const;

    private:

        // Using pointer due to SDL 
        SDL_Window* m_window_ptr;

        // Cameras
        const Shape m_null_camera;
        Shape m_camera;
    };
}


