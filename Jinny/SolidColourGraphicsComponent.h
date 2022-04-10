#pragma once

#include "GraphicsComponent.h"

#include "Shape.h"
#include "Colour.h"

namespace relic
{
    class SolidColourGraphicsComponent : public GraphicsComponent
    {
    public:
        SolidColourGraphicsComponent(framework::Shape shape, framework::Colour colour);
    };
}
