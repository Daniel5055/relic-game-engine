#pragma once


namespace Jinny
{
    enum class ObjectInputType
    {
        NULL_TYPE = 0,

        // Specifically for Input class
        LEFT_MOUSE_PRESS = 1,
        RIGHT_MOUSE_PRESS = 2,
        KEY_PRESS = 3,


        MOUSE_OVER,
        MOUSE_OFF,

        LEFT_MOUSE_DOWN = 8,
        LEFT_MOUSE_UP,

        RIGHT_MOUSE_DOWN,
        RIGHT_MOUSE_UP,

        // Specifically for Input Class
        KEY_DOWN,
        KEY_UP,

    };

    struct ObjectInput
    {

        ObjectInput(ObjectInputType t = ObjectInputType::NULL_TYPE, char k = ' ')
        {
            type = t;
            key = k;
        }
        ObjectInputType type;

        char key;

    };

}


