#pragma once

#include "Message.h"
#include "Vector.h"

#include "Message.h"

namespace framework
{
    class RigidBody;
}
namespace jinny
{
    enum class PMessageType
    {
        null_message = 0,
        set_rigid_body,
    };

    /**
     * \brief Messages to be sent by physics systems and components
     */
    struct PhysicsMessage : Message
    {
        PhysicsMessage() : Message(Type::physics) {}

        PMessageType type{ PMessageType::null_message };

        // Save memory
        union
        {
            framework::RigidBody* rigid_body{nullptr};
            framework::Vector vector;
        };
    };
}
