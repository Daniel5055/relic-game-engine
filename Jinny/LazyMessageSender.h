#pragma once

#include "MessageSender.h"

namespace jinny
{
    
    /**
     * \brief A class that only sends messages once at least one receiver has been designated
     * \tparam M A deliverable, either a message or event
     */
    template<typename M>
    class LazyMessageSender : public MessageSender<M>
    {
    protected:
        ~LazyMessageSender() = default;

        // Override sendMessage to make sure receiver added before sending
        void sendMessage(M msg) final;
    private:

        // Sets receiver added to true and sends out queued messages
        void uponReceiverAdded() final;

        // For any final changes to made to queued messages before sending
        virtual void prepareMessage(M& msg);

        bool m_receiver_added{ false };
        std::queue<M> m_queued_messages;
    };

    template <typename M>
    void LazyMessageSender<M>::sendMessage(M msg)
    {
        if (m_receiver_added)
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
    void LazyMessageSender<M>::uponReceiverAdded()
    {
        // If receiver not added yet then finally send all messages
        if (!m_receiver_added)
        {
            m_receiver_added = true;
            
            while (!m_queued_messages.empty())
            {
                prepareMessage(m_queued_messages.front());
                MessageSender<M>::sendMessage(m_queued_messages.front());
                m_queued_messages.pop();
            }
        }
    }

    template <typename M>
    void LazyMessageSender<M>::prepareMessage(M& msg)
    {
    }
}

