#pragma once

#include "Message.h"
#include "MessageExchanger.h"

namespace relic
{
    /**
     * \brief A message used to receive messages forwarded through the message bus
     * \tparam T A message type
     */
    template <typename T>
    class MessageReceiver : public MessageExchanger<T>
    {
    protected:
        // Constructor
        explicit MessageReceiver(const Identifier& identifier, bool is_local = false);
        ~MessageReceiver();

        // Message Handling
        void handleMessages();
    private:
        // Private virtual methods
        virtual void handleMessage(const Message<T>& msg) = 0;
    };

    template <typename T>
    MessageReceiver<T>::MessageReceiver(const Identifier& identifier, bool is_local)
        :MessageExchanger<T>(identifier, is_local)
    {
        MessageExchanger<T>::registerReceiver();
    }

    template <typename T>
    MessageReceiver<T>::~MessageReceiver()
    {
        MessageExchanger<T>::removeReceiver();
    }

    template <typename T>
    void MessageReceiver<T>::handleMessages()
    {
        for (size_t i = 0; i < MessageExchanger<T>::getQueueSize(); ++i)
        {
            const Message<T>& msg = MessageExchanger<T>::retrieveMessage(i);
            if (msg.to == Identifier::null || msg.to == MessageExchanger<T>::getIdentifier())
            {
                if (MessageExchanger<T>::isLocal() && msg.from == MessageExchanger<T>::getIdentifier() || !MessageExchanger<T>::isLocal())
                {
                    // Only handle message under correct conditions
                    handleMessage(msg);
                }
            }
        }

        MessageExchanger<T>::confirmRetrieval();
    }
}

