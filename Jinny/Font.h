#pragma once

// SDL Dependencies
#include <SDL_ttf.h>

namespace framework
{
    class Font
    {
    public:
        // Friend to graphics as only graphics can create font
        friend class Graphics;

        // Constructor
        Font();
        ~Font();

    private:
        TTF_Font* m_font_ptr;
    };
}


