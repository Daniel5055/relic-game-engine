#pragma once

#include "GraphicsComponent.h"

#include <string>

// Framework Dependencies
namespace framework
{
    struct Colour;
}

namespace relic
{
    /**
     * \brief Component used to draw text
     */
    class TextGraphicsComponent :public GraphicsComponent
    {
    public:
        // Constructor
        explicit TextGraphicsComponent(framework::Shape shape, const std::string& text, const std::string& font_name,
            framework::Colour font_colour = { 0x00, 0x00, 0x00, 0x00 },
            const std::string& font_path = "", unsigned int font_size = 12);
    };
}
