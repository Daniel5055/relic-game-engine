#pragma once

#include "AnimationComponent.h"

namespace jinny
{
    class ButtonAnimationComponent : public AnimationComponent
    {

    public:
        // Constructor
        ButtonAnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height);
    };
}