#pragma once

#include "MessageExchanger.h"
#include "Message.h"

namespace relic
{
    /**
     * \brief A class used to send messages to the MessageBus
     * \tparam T A message type
     */
    template<typename T>
    class MessageSender : public MessageExchanger<T>
    {
    protected:
        explicit MessageSender(const Identifier& identifier, bool is_local = false);
        // Protected destructor because should never be deleted by base pointer to this class
        ~MessageSender();

        // Method to be used by child classes to send message
        void sendMessage(Message<T> msg);
        void sendImmediateMessage(Message<T> msg);
    };

    template <typename T>
    MessageSender<T>::MessageSender(const Identifier& identifier, bool is_local)
        :MessageExchanger<T>(identifier, is_local)
    {
    }

    template <typename T>
    MessageSender<T>::~MessageSender() = default;

    template <typename T>
    void MessageSender<T>::sendMessage(Message<T> msg)
    {
        // Set from for message if not already done so (also prevents lying by message sender)
        msg.from = MessageExchanger<T>::getIdentifier();
        if (MessageExchanger<T>::isLocal())
        {
            // If the to id is not the identifier, then set the to identifier with a 0 subId
            if (msg.to != MessageExchanger<T>::getIdentifier())
            {
                msg.to = MessageExchanger<T>::getIdentifier();
                msg.to.setSubId(0);
            }

            // Else leave it (in case sub id is to somewhere specific)
        }
        MessageExchanger<T>::forwardMessage(msg, false);
    }

    template <typename T>
    void MessageSender<T>::sendImmediateMessage(Message<T> msg)
    {
        // Set from for message if not already done so (also prevents lying by message sender)
        msg.from = MessageExchanger<T>::getIdentifier();
        if (MessageExchanger<T>::isLocal())
        {
            // If the to id is not the identifier, then set the to identifier with a 0 subId
            if (msg.to != MessageExchanger<T>::getIdentifier())
            {
                msg.to = MessageExchanger<T>::getIdentifier();
                msg.to.setSubId(0);
            }

            // Else leave it (in case sub id is to somewhere specific)
        }
        MessageExchanger<T>::forwardMessage(msg, true);
    }
}
