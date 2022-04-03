#pragma once

#include "Message.h"

namespace framework
{
    struct Shape;
}

namespace jinny
{
    class Scene;

    enum class GameMessageType
    {
        null_message = 0,
        change_scene,
        set_camera,

        delete_object,
    };


    /**
     * \brief Messages to be sent by core systems and components
     */
    struct GameMessage : Message
    {
        GameMessage() : Message(Type::core) {}

        GameMessageType type{GameMessageType::null_message};
        union
        {
            Scene* scene_ptr{nullptr};
            framework::Shape* shape_ptr;
        };
    };
}