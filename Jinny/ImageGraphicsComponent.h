#pragma once

#include "GraphicsComponent.h"

namespace relic
{
    /**
     * \brief Component which uses image for graphics
     *
     */
    class ImageGraphicsComponent : public GraphicsComponent
    {
    public:
        // Constructor
        explicit ImageGraphicsComponent(framework::Shape shape, const std::string& texture_name, const std::string& texture_path = "");
    };
}

