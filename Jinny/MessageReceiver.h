#pragma once

#include <queue>

#include "Message.h"
#include "ObjectEvent.h"

namespace jinny
{
    /**
     * Abstract class to be inherited by classes that receive and handle messages.
     */
    template <typename M>
    class MessageReceiver
    {
        // Ensuring M is a message
        static_assert(std::is_base_of_v<Message, M> || std::is_base_of_v<ObjectEvent, M>, "MessageReceiver not assigned deliverable type");

    public:
        // Pushing messages
        void pushMessage(M msg)
        {
            m_message_queue.push(msg);
        }

    protected:
        // Protected destructor because should never be deleted by base pointer to this class
        ~MessageReceiver() = default;

        void handleMessages()
        {
            while (!m_message_queue.empty())
            {
                M msg = m_message_queue.front();
                m_message_queue.pop();

                handleMessage(msg);
            }
        }
    private:
        // Private virtual methods
        virtual void handleMessage(M msg) = 0;

        // Message queue
        std::queue<M> m_message_queue;
    };
}
