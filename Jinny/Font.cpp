#include "Font.h"

#include <SDL_ttf.h>

Framework::Font::Font()
{
    m_font_ptr = nullptr;
}

Framework::Font::~Font()
{
    TTF_CloseFont(m_font_ptr);
    m_font_ptr = nullptr;
}

