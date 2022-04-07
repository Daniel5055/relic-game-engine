#pragma once

#include "Component.h"
#include "LazyMessageSender.h"
#include "MessageReceiver.h"
#include "PhysicsMessage.h"

namespace relic
{
    /**
     * \brief Base abstract class for components relating to physics
     */
    class PhysicsComponent
        : public Component
        , public LazyMessageSender<PhysicsMessage>
        , public MessageReceiver<PhysicsMessage>
    {
    public:
        // Prevent ambiguity 
        using LazyMessageSender<PhysicsMessage>::addReceiver;
        using LazyMessageSender<PhysicsMessage>::deployMessages;
        using MessageReceiver<PhysicsMessage>::receiveMessage;
    protected:
        using LazyMessageSender<PhysicsMessage>::sendMessage;

    private:
        void doUpdates() override;
        // Defined as physics component
        Message::Type defineMessageType() final { return Message::Type::physics; }

        // Prepping queued messages with object id
        void prepareMessage(PhysicsMessage& msg) override;
        void handleMessage(PhysicsMessage msg) override;
    };

    inline void PhysicsComponent::doUpdates()
    {
        MessageReceiver<PhysicsMessage>::handleMessages();
    }

    inline void PhysicsComponent::prepareMessage(PhysicsMessage& msg)
    {
        if (msg.object_id == k_unset_id)
        {
            msg.object_id = getObjectId();
        }
    }

    inline void PhysicsComponent::handleMessage(PhysicsMessage msg)
    {
    }
}

