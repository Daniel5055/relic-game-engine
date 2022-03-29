#pragma once

#include "Graphics.h"
#include "Logger.h"


namespace Framework
{
    /**
     * Logged version of graphics framework class.
     */
    class LoggedGraphics : public Graphics
    {
    public:

        // Constructor
        explicit LoggedGraphics(Window& t_window);

        // Destructor
        ~LoggedGraphics();

        // Logged creation of textures and font
        Font* createFont(std::string path, int font_size) const override;
        Texture* createTexture(std::string path) const override;
        Texture* createTextTexture(std::string text, Font* font, Color color) const override;

    private:

        // Logger
        const Logger m_logger;
    };
}

