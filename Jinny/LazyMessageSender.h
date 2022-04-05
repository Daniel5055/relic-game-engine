#pragma once

#include "MessageSender.h"

namespace relic
{
    
    /**
     * \brief A class that only sends messages once at least one receiver has been designated
     * \tparam M A deliverable, either a message or event
     */
    template<typename M>
    class LazyMessageSender : public MessageSender<M>
    {
    public:
        // Sets deployed to true and sends out queued messages
        void deployMessages();

    protected:
        ~LazyMessageSender() = default;

        // Override sendMessage to make sure receiver added before sending
        void sendMessage(M msg) final;

    private:
        // For any final changes to made to queued messages before sending
        virtual void prepareMessage(M& msg);

        bool m_deployed{ false };
        std::queue<M> m_queued_messages;
    };

    template <typename M>
    void LazyMessageSender<M>::sendMessage(M msg)
    {
        if (m_deployed)
        {
            MessageSender<M>::sendMessage(msg);
        }
        else
        {
            // If receiver not added, then push to queued messages
            m_queued_messages.push(msg);
        }
    }

    template <typename M>
    void LazyMessageSender<M>::deployMessages()
    {
        m_deployed = true;
        while(!m_queued_messages.empty())
        {
            prepareMessage(m_queued_messages.front());
            MessageSender<M>::sendMessage(m_queued_messages.front());
            m_queued_messages.pop();
        }
    }

    template <typename M>
    void LazyMessageSender<M>::prepareMessage(M& msg)
    {
    }
}

