#pragma once

#include "Component.h"
#include "LazyMessageSender.h"
#include "PhysicsMessage.h"

namespace jinny
{
    /**
     * \brief Base abstract class for components relating to physics
     */
    class PhysicsComponent
        : public Component
        , public LazyMessageSender<PhysicsMessage>
    {
    public:
        // Prevent ambiguity 
        using LazyMessageSender<PhysicsMessage>::addReceiver;
        using LazyMessageSender<PhysicsMessage>::sendMessage;

    private:
        // Defined as physics component
        Message::Type defineMessageType() final { return Message::Type::physics; }

        // Prepping queued messages with object id
        void prepareMessage(PhysicsMessage& msg) override;
    };

    inline void PhysicsComponent::prepareMessage(PhysicsMessage& msg)
    {
        if (msg.object_id == k_unset_id)
        {
            msg.object_id = getObjectId();
        }
    }
}

