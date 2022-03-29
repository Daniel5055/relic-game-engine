#include "Texture.h"

#include <SDL.h>

#include "Point.h"

Framework::Texture::Texture()
{
    m_texture_ptr = nullptr;
    m_width = 0;
    m_height = 0;
}

Framework::Texture::~Texture()
{
    SDL_DestroyTexture(m_texture_ptr);
}



SDL_Point Framework::Texture::getSize()
{
    return { m_width, m_height };
}

int Framework::Texture::getWidth()
{
    return m_width;
}

int Framework::Texture::getHeight()
{
    return m_height;
}

void Framework::Texture::setTexture(SDL_Texture* texture_ptr)
{
    m_texture_ptr = texture_ptr;
    SDL_QueryTexture(m_texture_ptr, nullptr, nullptr, &m_width, &m_height);
}

SDL_Texture* Framework::Texture::getTexture()
{
    return m_texture_ptr;
}
