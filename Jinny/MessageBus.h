#pragma once

#include <vector>

#include "Message.h"

namespace relic
{

    /**
     * \brief A class used to forward messages to receivers of the same message type
     * \tparam T A message type
     */
    template<typename T>
    class MessageBus
    {
    public:
        void forwardMessage(Message<T> msg, const Identifier& id, bool immediate, bool local);
        void registerReceiver();
        void removeReceiver();
        void confirmRetrieval();

        const Message<T>& retrieveMessage(unsigned int position);

        size_t getQueueSize();

    private:
        // Messages queued with a reference to their message sender identifier
        // (In case the identifier was not set when message was forwarded)
        std::vector<std::pair<Message<T>, std::pair<const Identifier*, bool>>> m_queued_messages;
        std::vector<std::pair<Message<T>, std::pair<const Identifier*, bool>>> m_next_messages;

        int m_receiver_count{ 0 };
        int m_current_retrieval_count{ 0 };
    };

    template <typename T>
    void MessageBus<T>::forwardMessage(Message<T> msg, const Identifier& id, const bool immediate, const bool local)
    {
        if (immediate)
        {
            m_queued_messages.push_back(std::make_pair(msg, std::make_pair(&id, local)));

        }
        else
        {
            m_next_messages.push_back(std::make_pair(msg, std::make_pair(&id, local)));
        }
    }

    template <typename T>
    void MessageBus<T>::registerReceiver()
    {
        ++m_receiver_count;
    }

    template <typename T>
    void MessageBus<T>::removeReceiver()
    {
        --m_receiver_count;
    }

    template <typename T>
    void MessageBus<T>::confirmRetrieval()
    {
        ++m_current_retrieval_count;

        if (m_current_retrieval_count == m_receiver_count)
        {
            m_current_retrieval_count = 0;
            m_queued_messages = m_next_messages;
            m_next_messages.clear();
        }
    }

    template <typename T>
    const Message<T>& MessageBus<T>::retrieveMessage(const unsigned int position)
    {
        if (position < m_queued_messages.size())
        {
            // Setting the identifier if not done properly yet
            if (m_queued_messages[position].first.from == Identifier::null)
            {
                m_queued_messages[position].first.from = *m_queued_messages[position].second.first;
            }

            // If sent locally
            if (m_queued_messages[position].second.second)
            {
                // If a destination not already set then must be set to local with no sub type
                if (m_queued_messages[position].first.to == Identifier::null)
                {
                    // Setting the sub id to 0 to specify any subId
                    m_queued_messages[position].first.to = *m_queued_messages[position].second.first;
                    m_queued_messages[position].first.to.setSubId(0); 
                }
            }

            // Returning the message
            return m_queued_messages[position].first;
        }

        // Otherwise not good, throw error
        return m_queued_messages[0].first;

    }

    template <typename T>
    size_t MessageBus<T>::getQueueSize()
    {
        return m_queued_messages.size();
    }
}
