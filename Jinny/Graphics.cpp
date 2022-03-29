#include "Graphics.h"


// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Graphic.h"
#include "Texture.h"
#include "Shape.h"

#include "Window.h"
#include "Font.h"
#include "Color.h"

#include <assert.h>

Framework::Graphics::Graphics()
{
}

Framework::Graphics::Graphics(const Window& t_window)
    :m_renderer_ptr(SDL_CreateRenderer(t_window.m_window_ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
{
    assert(m_renderer_ptr != nullptr);
}


Framework::Graphics::~Graphics()
{
    SDL_DestroyRenderer(m_renderer_ptr);
}


void Framework::Graphics::clear(Framework::Color color) const
{
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer_ptr, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer_ptr);
}

void Framework::Graphics::draw(Graphic* graphic) const
{
    // May slow down
    SDL_Rect shape = (SDL_Rect)*graphic->getShape();
    if (graphic->getClip() == nullptr)
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), nullptr, &shape);
    }
    else
    {
        SDL_Rect clip = (SDL_Rect)*graphic->getClip();
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), &clip, &shape);
    }
}

void Framework::Graphics::draw(Graphic* graphic, int x_shift, int y_shift) const
{
    // May slow down
    SDL_Rect shape = (SDL_Rect)*graphic->getShape();
    shape.x -= x_shift;
    shape.y -= y_shift;

    if (graphic->getClip() == nullptr)
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), nullptr, &shape);
    }
    else
    {
        SDL_Rect clip = (SDL_Rect)*graphic->getClip();
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), &clip, &shape);
    }
}

void Framework::Graphics::display() const
{
    SDL_RenderPresent(m_renderer_ptr);
}

Framework::Font* Framework::Graphics::createFont(std::string path, int font_size) const
{
    Font* font = new Font();
    font->m_font_ptr = TTF_OpenFont(path.c_str(), font_size);
    assert(font->m_font_ptr != nullptr);

    return font;
}

Framework::Texture* Framework::Graphics::createTexture(std::string path) const
{
    Texture* texture = new Texture();
    SDL_Surface* surface_ptr = IMG_Load(path.c_str());
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}


Framework::Texture* Framework::Graphics::createTextTexture(std::string text, Framework::Font* font, Framework::Color color) const
{
    Texture* texture = new Texture();
    SDL_Surface* surface_ptr = TTF_RenderText_Blended(font->m_font_ptr, text.c_str(), color);
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}

Framework::Texture* Framework::Graphics::createWrappedTextTexture(std::string text, Font* font, Color color, Shape* shape) const
{
    Texture* texture = new Texture();
    SDL_Surface* surface_ptr = TTF_RenderText_Blended_Wrapped(font->m_font_ptr, text.c_str(), color, shape->w);
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}

void Framework::Graphics::assignTexture(Graphic* graphic, Texture* texture) const
{
    // Set Texture
    graphic->setTexture(texture);
}
