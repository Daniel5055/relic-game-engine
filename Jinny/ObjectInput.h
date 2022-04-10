#pragma once

#include "Shape.h"

namespace relic
{
    enum class ObjectInputType
    {
        null_type = 0,

        // Specifically for Input class
        left_mouse_press = 1,
        right_mouse_press = 2,
        key_press = 3,


        mouse_over,
        mouse_off,

        left_mouse_down = 8,
        left_mouse_up,

        right_mouse_down,
        right_mouse_up,

        // Specifically for Input Class
        key_down,
        key_up,

    };

    struct ObjectInput
    {
        ObjectInput(const ObjectInputType t = ObjectInputType::null_type, const char k = ' ') : type(t), key(k)
        {
        }
        ObjectInputType type;
        char key;
        framework::Shape* mouse_shape{nullptr};

    };

}


