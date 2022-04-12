#pragma once

#include "Identifier.h"
#include "Message.h"
#include "MessageBus.h"

namespace relic
{
    /**
     * \brief The base class of message receivers and senders
     * \tparam T A message type
     */
    template<typename T>
    class MessageExchanger
    {
    protected:
        // Constructor
        explicit MessageExchanger(const Identifier& identifier, bool is_local = false);

        // Destructor
        ~MessageExchanger() = default;

        // Interfacing with message bus
        void forwardMessage(Message<T> msg, bool immediate);
        const Message<T>& retrieveMessage(unsigned int position);
        size_t getQueueSize();
        void registerReceiver();
        void removeReceiver();
        void confirmRetrieval();

        // Accessing private base data
        bool isLocal() const;
        const Identifier& getIdentifier() const;

    private:
        const Identifier& m_identifier;
        bool m_is_local;
        inline static MessageBus<T> m_message_bus{};
    };

    template <typename T>
    MessageExchanger<T>::MessageExchanger(const Identifier& identifier, const bool is_local)
        :m_identifier(identifier), m_is_local(is_local)
    {
    }

    template <typename T>
    void MessageExchanger<T>::forwardMessage(Message<T> msg, const bool immediate)
    {
        m_message_bus.forwardMessage(msg, m_identifier, immediate, m_is_local);
    }

    template <typename T>
    const Message<T>& MessageExchanger<T>::retrieveMessage(unsigned position)
    {
        return m_message_bus.retrieveMessage(position);
    }

    template <typename T>
    size_t MessageExchanger<T>::getQueueSize()
    {
        return m_message_bus.getQueueSize();
    }

    template <typename T>
    void MessageExchanger<T>::registerReceiver()
    {
        m_message_bus.registerReceiver();
    }

    template <typename T>
    void MessageExchanger<T>::removeReceiver()
    {
        m_message_bus.removeReceiver();
    }

    template <typename T>
    void MessageExchanger<T>::confirmRetrieval()
    {
        m_message_bus.confirmRetrieval();
    }

    template <typename T>
    bool MessageExchanger<T>::isLocal() const
    {
        return m_is_local;
    }

    template <typename T>
    const Identifier& MessageExchanger<T>::getIdentifier() const
    {
        return m_identifier;
    }
}
