#pragma once

namespace Framework
{
    struct Shape;
}

namespace Jinny
{
    class Scene;

    enum class GameMessageType
    {
        NULL_MESSAGE = 0,
        CHANGE_SCENE,
        SET_CAMERA,

        DELETE_OBJECT,
    };

    struct GameMessage
    {
        // Constructor
        GameMessage(GameMessageType msg_type = GameMessageType::NULL_MESSAGE, int id = -1)
        {
            type = msg_type;
            object_ID = id;
        }

        GameMessageType type;
        int object_ID;
        union
        {
            Scene* scene_ptr;
            Framework::Shape* shape_ptr;
        };


    };
}