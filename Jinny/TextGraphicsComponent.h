#pragma once

#include <string>

#include "GraphicsComponent.h"

// Framework Dependencies
namespace Framework
{
    struct Color;
}

namespace Jinny
{
    class TextGraphicsComponent :public GraphicsComponent
    {
    public:
        // Constructor
        TextGraphicsComponent(std::string text, std::string font_name, Framework::Color font_color = { 0x00, 0x00, 0x00, 0x00 }, std::string font_path = "", int font_size = 12);

        // Initialization
        void initialize(GameObject& object);


    private:
    };
}
