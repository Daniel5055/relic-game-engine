#include "Texture.h"

#include <SDL.h>

#include "Point.h"

framework::Texture::Texture()
{
    m_texture_ptr = nullptr;
    m_width = 0;
    m_height = 0;
}

framework::Texture::~Texture()
{
    SDL_DestroyTexture(m_texture_ptr);
}



SDL_Point framework::Texture::getSize()
{
    return { m_width, m_height };
}

int framework::Texture::getWidth()
{
    return m_width;
}

int framework::Texture::getHeight()
{
    return m_height;
}

void framework::Texture::setTexture(SDL_Texture* texture_ptr)
{
    m_texture_ptr = texture_ptr;
    SDL_QueryTexture(m_texture_ptr, nullptr, nullptr, &m_width, &m_height);
}

SDL_Texture* framework::Texture::getTexture()
{
    return m_texture_ptr;
}
