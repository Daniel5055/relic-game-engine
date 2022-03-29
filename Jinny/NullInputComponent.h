#pragma once

#include "InputComponent.h"

namespace Jinny
{
    class NullInputComponent : public InputComponent
    {
        // Initialization
        virtual void initialize(GameObject& object)
        {}

        // Updating
        virtual void update()
        {}

        // Closing
        virtual void close()
        {}
    };
}