#pragma once

#include "MessageExchanger.decl.h"

namespace relic
{
    template <typename T>
    MessageExchanger<T>::MessageExchanger(const Identifier& identifier, const bool is_local)
        :m_identifier(identifier), m_is_local(is_local)
    {
    }

    template <typename T>
    const Identifier& MessageExchanger<T>::getIdentifier() const
    {
        return m_identifier;
    }

    template <typename T>
    void MessageExchanger<T>::addReceiver(MessageReceiver<T>* receiver)
    {
        m_message_bus.addReceiver(receiver);
    }

    template <typename T>
    void MessageExchanger<T>::removeReceiver(MessageReceiver<T>* receiver)
    {
        m_message_bus.removeReceiver(receiver);
    }

    template <typename T>
    void MessageExchanger<T>::forwardMessage(Message<T> msg, bool locally)
    {
        m_message_bus.forwardMessage(msg, locally);
    }

}

