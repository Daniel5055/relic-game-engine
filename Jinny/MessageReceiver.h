#pragma once

#include <queue>

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
    public:
        // Receiving messages
        void receiveMessage(Message<T> msg);

    protected:
        // Constructor
        explicit MessageReceiver(const Identifier& identifier, bool is_local = false);

        // Destructor
        ~MessageReceiver();

        // Message Handling
        void handleMessages();

    private:
        // Private virtual methods
        virtual void handleMessage(Message<T> msg) = 0;

        // Message queue
        std::queue<Message<T>> m_message_queue;
    };

    template <typename T>
    void MessageReceiver<T>::receiveMessage(Message<T> msg)
    {
        m_message_queue.push(msg);
    }

    template <typename T>
    MessageReceiver<T>::MessageReceiver(const Identifier& identifier, bool is_local)
        :MessageExchanger<T>(identifier, is_local)
    {
        MessageExchanger<T>::addReceiver(this);
    }

    template <typename T>
    MessageReceiver<T>::~MessageReceiver()
    {
        MessageExchanger<T>::removeReceiver(this);
    }

    template <typename T>
    void MessageReceiver<T>::handleMessages()
    {
        while (!m_message_queue.empty())
        {
            Message<T> msg = m_message_queue.front();
            m_message_queue.pop();

            handleMessage(msg);
        }
    }
}

