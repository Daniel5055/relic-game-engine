#include "Font.h"

#include <SDL_ttf.h>

framework::Font::Font()
{
    m_font_ptr = nullptr;
}

framework::Font::~Font()
{
    TTF_CloseFont(m_font_ptr);
    m_font_ptr = nullptr;
}

