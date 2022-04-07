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
#include "Colour.h"

#include <cassert>

framework::Graphics::Graphics(const Window& window)
    :m_renderer_ptr(SDL_CreateRenderer(window.m_window_ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
{
    assert(m_renderer_ptr != nullptr);
}


framework::Graphics::~Graphics()
{
    SDL_DestroyRenderer(m_renderer_ptr);
}


void framework::Graphics::clear(const Colour clear_colour) const
{
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer_ptr, clear_colour.r, clear_colour.g, clear_colour.b, clear_colour.a);
    SDL_RenderClear(m_renderer_ptr);
}

void framework::Graphics::draw(Graphic* graphic) const
{
    draw(graphic, 0, 0);
}

void framework::Graphics::draw(Graphic* graphic, const int x_shift, const int y_shift) const
{
    // May slow down
    auto shape = static_cast<SDL_Rect>(graphic->getShape());
    shape.x -= x_shift;
    shape.y -= y_shift;

    const auto clip = static_cast<SDL_Rect>(graphic->getClip());

    if (graphic->getTexture() == nullptr)
    {
        // Then draw with colour
        SDL_SetRenderDrawColor(m_renderer_ptr, graphic->getColour().r, graphic->getColour().g, graphic->getColour().b, graphic->getColour().a);
        SDL_RenderFillRect(m_renderer_ptr, &shape);
        SDL_SetRenderDrawColor(m_renderer_ptr, 255, 255, 255, 255);
    }
    else if (clip.h == 0 && clip.w == 0)
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), nullptr, &shape);
    }
    else
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), &clip, &shape);
    }
}

void framework::Graphics::display() const
{
    SDL_RenderPresent(m_renderer_ptr);
}

framework::Font* framework::Graphics::createFont(const std::string path, const int font_size) const
{
    const auto font = new Font();
    font->m_font_ptr = TTF_OpenFont(path.c_str(), font_size);
    assert(font->m_font_ptr != nullptr);

    return font;
}

framework::Texture* framework::Graphics::createTexture(std::string path) const
{
    const auto texture = new Texture();
    SDL_Surface* surface_ptr = IMG_Load(path.c_str());
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}


framework::Texture* framework::Graphics::createTextTexture(const std::string text, framework::Font* font, const framework::Colour colour) const
{
    const auto texture = new Texture();
    SDL_Surface* surface_ptr = TTF_RenderText_Blended(font->m_font_ptr, text.c_str(), static_cast<SDL_Color>(colour));
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}

framework::Texture* framework::Graphics::createWrappedTextTexture(const std::string text, Font* font, const Colour colour, Shape* shape) const
{
    const auto texture = new Texture();
    SDL_Surface* surface_ptr = TTF_RenderText_Blended_Wrapped(font->m_font_ptr, text.c_str(), static_cast<SDL_Color>(colour), shape->w);
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    assert(texture->getTexture() != nullptr);

    return texture;
}

void framework::Graphics::assignTexture(Graphic* graphic, Texture* texture) const
{
    // Set Texture
    graphic->setTexture(texture);
}
