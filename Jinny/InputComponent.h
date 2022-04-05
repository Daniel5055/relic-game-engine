#pragma once


#include "Component.h"
#include "MessageReceiver.h"
#include "LazyMessageSender.h"
#include "InputMessage.h"

namespace relic
{
    /**
     * \brief Base abstract class for components relating to input
     */
    class InputComponent
        : public Component
        , public MessageReceiver<InputMessage>
        , public LazyMessageSender<InputMessage>
    {
    public:
        // Prevent ambiguity 
        using LazyMessageSender<InputMessage>::addReceiver;
        using LazyMessageSender<InputMessage>::deployMessages;
        using MessageReceiver<InputMessage>::receiveMessage;

        ~InputComponent() override = default;

    protected:
        using LazyMessageSender<InputMessage>::sendMessage;

    private:

        void handleMessage(InputMessage msg) override {}

        // Define as input component
        Message::Type defineMessageType() final { return Message::Type::input; }

        // Prep initial messages within queue 
        void prepareMessage(InputMessage& msg) override;
    };

    inline void InputComponent::prepareMessage(InputMessage& msg)
    {
        if (msg.object_id == k_unset_id)
        {
            msg.object_id = getObjectId();
        }
    }
}


