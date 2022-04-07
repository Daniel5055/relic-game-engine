#pragma once

#include <string>
#include "Colour.h"

#include "Message.h"

namespace framework
{
    class Graphic;
}
namespace relic
{
    enum class GMessageType
    {
        null_message = 0,

        load_texture,
        load_font,
        assign_texture,
        assign_text,

        show_graphic,
        hide_graphic,
    };

    /**
     * \brief Messages to be sent by graphics systems and components
     */
    struct GraphicsMessage : Message
    {
        GraphicsMessage() : Message(Type::graphics) {}

        GMessageType type{GMessageType::null_message};

        framework::Graphic* graphic{nullptr};

        std::string string_1;
        std::string string_2;
        int num{};
        framework::Colour color;
    };
}