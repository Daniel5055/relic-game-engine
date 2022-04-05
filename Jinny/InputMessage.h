#pragma once

#include "ObjectInput.h"

#include "Message.h"

#include "Shape.h"

namespace relic
{
    enum class IMessageType
    {
        null_message = 0,
        subscribe_input,
        unsubscribe_input,
        input_triggered,

        exit_button_pressed
    };

    /**
     * \brief Messages to be sent by input systems and components
     */
    struct InputMessage : Message
    {
        InputMessage() : Message(Type::input) {}
        IMessageType type{IMessageType::null_message};
        framework::Shape* object_shape{nullptr};
        ObjectInput object_input{ObjectInputType::null_type};
    };
}
