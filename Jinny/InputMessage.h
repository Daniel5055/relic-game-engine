#pragma once

#include "ObjectInput.h"

#include "Shape.h"

namespace Jinny
{
    enum class IMessageType
    {
        NULL_MESSAGE = 0,
        SUBSCRIBE_INPUT,
        UNSUBSCRIBE_INPUT,
        INPUT_TRIGGERED,

        EXIT_BUTTON_PRESSED
    };

    /**
     * Messages used by input components and system to communicate.
     */
    struct InputMessage
    {
        InputMessage()
        {
            type = IMessageType::NULL_MESSAGE;
            object_ID = -1;
            object_shape = nullptr;
        }
        IMessageType type;
        int object_ID;
        Framework::Shape* object_shape;
        ObjectInput object_input;
    };
}

