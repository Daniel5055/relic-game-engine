#pragma once

#include "Identifier.h"

#include "Message.h"

#include "MessageBus.h"

namespace relic
{
    template<typename T>
    class MessageReceiver;

    /**
     * \brief The base class of message receivers and senders
     * \tparam T A message type
     */
    template<typename T>
    class MessageExchanger
    {
    public:
        explicit MessageExchanger(const Identifier& identifier, bool is_local = false);

        const Identifier& getIdentifier() const;

        bool isLocal() const
        {
            return m_is_local;
        }
    protected:
        void addReceiver(MessageReceiver<T>* receiver);
        void removeReceiver(MessageReceiver<T>* receiver);
        void forwardMessage(Message<T> msg, bool locally);

    private:
        const Identifier& m_identifier;
        bool m_is_local;
        inline static MessageBus<T> m_message_bus{};
    };

}
