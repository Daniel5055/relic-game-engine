#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include "MessageReceiver.h"
#include "Message.h"

namespace relic
{
    /**
     * \brief A class used to send messages to designated receivers
     * \tparam M A deliverable, either a message or event
     */
    template<typename M>
    class MessageSender
    {
        // Ensuring M is a message
        static_assert(std::is_base_of_v<Message, M> || std::is_base_of_v<ObjectEvent, M>, "MessageSend not assigned deliverable type");

    public:
        void addReceiver(MessageReceiver<M>* receiver);

    protected:
        // Protected destructor because should never be deleted by base pointer to this class
        ~MessageSender();

        // Method to be used by child classes to send message
        virtual void sendMessage(M msg);
    private:

        // Message receivers to send messages to
        std::vector<MessageReceiver<M>*> m_message_receivers{};
    };

    template <typename M>
    void MessageSender<M>::addReceiver(MessageReceiver<M>* receiver)
    {
        m_message_receivers.push_back(receiver);
    }

    template <typename M>
    MessageSender<M>::~MessageSender() = default;

    template <typename M>
    void MessageSender<M>::sendMessage(M msg)
    {
        // Iterate through message receivers and push back
        for (const auto& message_receiver : m_message_receivers)
        {
            message_receiver->receiveMessage(msg);
        }
    }
}
