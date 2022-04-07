#pragma once

#include "Graphics.h"
#include "Logger.h"


namespace framework
{
    /**
     * Logged version of graphics framework class.
     */
    class LoggedGraphics : public Graphics
    {
    public:

        // Constructor
        explicit LoggedGraphics(Window& window);

        // Destructor
        ~LoggedGraphics();

        // Logged creation of textures and font
        Font* createFont(std::string path, int font_size) const override;
        Texture* createTexture(std::string path) const override;
        Texture* createTextTexture(std::string text, Font* font, Colour color) const override;

    private:

        // Logger
        const Logger m_logger;
    };
}

