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

Framework::Graphics::Graphics()
{
    m_renderer_ptr = nullptr;
}

bool Framework::Graphics::initialize(Window* window)
{
    m_renderer_ptr = SDL_CreateRenderer(window->m_window_ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer_ptr == nullptr)
    {
        return false;
    }

    return true;
}


void Framework::Graphics::close()
{
    if (m_renderer_ptr != nullptr)
    {
        SDL_DestroyRenderer(m_renderer_ptr);
        m_renderer_ptr = nullptr;
    }

}


void Framework::Graphics::clear(Framework::Color color)
{
    
    SDL_SetRenderDrawColor(m_renderer_ptr, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer_ptr);
    
}


void Framework::Graphics::draw(Graphic* graphic)
{
    // May slow down
    if (graphic->getClip() == nullptr)
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), nullptr, &(SDL_Rect)*graphic->getShape());
    }
    else
    {
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), &(SDL_Rect)*graphic->getClip(), &(SDL_Rect)*graphic->getShape());
    }
    
}

void Framework::Graphics::draw(Graphic* graphic, int x_shift, int y_shift)
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
        SDL_RenderCopy(m_renderer_ptr, graphic->getTexture()->getTexture(), &(SDL_Rect)*graphic->getClip(), &shape);
    }
}

void Framework::Graphics::display()
{
    SDL_RenderPresent(m_renderer_ptr);
}

Framework::Font* Framework::Graphics::createFont(std::string path, int font_size)
{
    Font* font = new Font();
    font->m_font_ptr = TTF_OpenFont(path.c_str(), font_size);

    return font;
}

Framework::Texture* Framework::Graphics::createTexture(std::string path)
{
    Texture* texture = new Texture();
    SDL_Surface* surface_ptr = IMG_Load(path.c_str());  
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    return texture;


}


Framework::Texture* Framework::Graphics::createTextTexture(std::string text, Framework::Font* font, Framework::Color color)
{
    
    Texture* texture = new Texture();   
    SDL_Surface* surface_ptr = TTF_RenderText_Blended(font->m_font_ptr, text.c_str(), color);
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    return texture;

}

Framework::Texture* Framework::Graphics::createWrappedTextTexture(std::string text, Font* font, Color color, Shape* shape)
{
    Texture* texture = new Texture();
    SDL_Surface* surface_ptr = TTF_RenderText_Blended_Wrapped(font->m_font_ptr, text.c_str(), color, shape->w);
    texture->setTexture(SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr));

    return texture;
}

void Framework::Graphics::assignTexture(Graphic* graphic, Texture* texture)
{
    // Set Texture
    graphic->setTexture(texture);
    // Set Texture size
}
