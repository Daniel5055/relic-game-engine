#pragma once

#include "Vector.h"
#include "Point.h"

namespace Framework
{
    class RigidBody;
    class RigidBody;
}
namespace Jinny
{
    enum class PMessageType
    {
        NULL_MESSAGE = 0,
        SET_RIGID_BODY,
    };

    struct PhysicsMessage
    {
        PhysicsMessage()
        {
            type = PMessageType::NULL_MESSAGE;
            object_ID = -1;
        }

        PMessageType type;
        int object_ID;

        // Save memory
        union
        {
            Framework::RigidBody* rigid_body;
            Framework::Vector vector;
        };
    };
}
