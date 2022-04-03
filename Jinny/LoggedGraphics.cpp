#include "LoggedGraphics.h"

// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Graphic.h"
#include "Window.h"
#include "Font.h"
#include "Color.h"

framework::LoggedGraphics::LoggedGraphics(Window& window)
    :Graphics(window), m_logger("Graphics Framework")
{
    m_logger.log("Successful Initialisation");
}

framework::LoggedGraphics::~LoggedGraphics()
{

    m_logger.log("deinitialisation");
}

framework::Font* framework::LoggedGraphics::createFont(std::string path, int font_size) const
{
    Font* font_ptr = Graphics::createFont(path, font_size);

    if (font_ptr != nullptr)
    {
        m_logger.log("Font from: " + path + " created");
    }
    else
    {
        m_logger.logError("Font from " + path + " not created");
    }

    return font_ptr;
}

framework::Texture* framework::LoggedGraphics::createTexture(std::string path)  const
{
    Texture* texture_ptr = Graphics::createTexture(path);

    if (texture_ptr != nullptr)
    {
        m_logger.log("Texture from: " + path + " created");
    }
    else
    {
        m_logger.logError("Texture from " + path + " not created");
    }

    return texture_ptr;
}


framework::Texture* framework::LoggedGraphics::createTextTexture(std::string text, Font* font, Color color) const
{
    Texture* texture_ptr = Graphics::createTextTexture(text, font, color);

    if (texture_ptr != nullptr)
    {
        m_logger.log("Texture from font created");
    }
    else
    {
        m_logger.logError("Texture from font not created");
    }

    return texture_ptr;
}

