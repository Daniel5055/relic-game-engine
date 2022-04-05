#pragma once

#include "Component.h"
#include "LazyMessageSender.h"
#include "GameMessage.h"


namespace relic
{
    /**
     * \brief Base abstract class for components relating to core features of the game engine
     */
    class CoreComponent
        : public Component
        , public LazyMessageSender<GameMessage>
    {
    public:
        // Prevent ambiguity 
        using LazyMessageSender<GameMessage>::addReceiver;
        using LazyMessageSender<GameMessage>::deployMessages;

    protected:

        // Prevent ambiguity
        using LazyMessageSender<GameMessage>::sendMessage;

    private:
        // Core component type
        Message::Type defineMessageType() final { return Message::Type::core; }

        // Overriding message prep to set object id after the fact
        void prepareMessage(GameMessage& msg) override;

    };

    inline void CoreComponent::prepareMessage(GameMessage& msg)
    {
        if (msg.object_id == k_unset_id)
        {
            msg.object_id = getObjectId();
        }
    }
}
