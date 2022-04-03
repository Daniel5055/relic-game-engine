#pragma once

#include "GraphicsComponent.h"

namespace jinny
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
    private:
        void handleEvent(ObjectEvent e) override;
    };
}

