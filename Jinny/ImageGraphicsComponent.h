#pragma once

#include "GraphicsComponent.h"

namespace Jinny
{
    class ImageGraphicsComponent : public GraphicsComponent
    {
    public:
        // Constructor
        ImageGraphicsComponent(std::string texture_name, std::string texture_path = "");

        // Initialization
        void initialize(GameObject& object);


    private:
    };
}


