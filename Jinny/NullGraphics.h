#pragma once
#include "Graphics.h"

namespace framework
{
    // Graphics Framework which does nothing, to disable graphics
    class NullGraphics : public Graphics
    {
        // Initialization and Closing
        bool initialize(Window* window);
        void close();

        // Rendering functions
        void clear(Color clear_color);
        void draw(Graphic* graphic);
        void display();


        // Creation of textures and font
        Font* createFont(std::string path, int font_size);
        Texture* createTexture(std::string path);
        Texture* createTextTexture(std::string text, Font* font, Color color);

    };
}


