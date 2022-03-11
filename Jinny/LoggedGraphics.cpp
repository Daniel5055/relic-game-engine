#include "LoggedGraphics.h"

// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Graphic.h"
#include "Window.h"
#include "Font.h"
#include "Color.h"

#include "Logger.h"

bool Framework::LoggedGraphics::initialize(Window* window)
{
    m_logger_ptr = new Logger("Graphics Framework");

    if (Graphics::initialize(window))
    {
        m_logger_ptr->log("Successfully Initialized");
        return true;
    }
    else
    {
        m_logger_ptr->logError("Initialization Failed");
        return false;
    }
 
}

void Framework::LoggedGraphics::close()
{
    Graphics::close();

    m_logger_ptr->log("deinitialized");

    delete m_logger_ptr;
}

Framework::Font* Framework::LoggedGraphics::createFont(std::string path, int font_size)
{
    Font* font_ptr = Graphics::createFont(path, font_size);

    if (font_ptr != nullptr)
    {
        m_logger_ptr->log("Font from: " + path + " created");
    }
    else
    {
        m_logger_ptr->logError("Font from " + path + " not created");
    }

    return font_ptr;
}

Framework::Texture* Framework::LoggedGraphics::createTexture(std::string path)
{
    Texture* texture_ptr = Graphics::createTexture(path);

    if (texture_ptr != nullptr)
    {
        m_logger_ptr->log("Texture from: " + path + " created");
    }
    else
    {
        m_logger_ptr->logError("Texture from " + path + " not created");
    }

    return texture_ptr;
}


Framework::Texture* Framework::LoggedGraphics::createTextTexture(std::string text, Font* font, Color color)
{
    Texture* texture_ptr = Graphics::createTextTexture(text, font, color);

    if (texture_ptr != nullptr)
    {
        m_logger_ptr->log("Texture from font created");
    }
    else
    {
        m_logger_ptr->logError("Texture from font not created");
    }

    return texture_ptr;
}

