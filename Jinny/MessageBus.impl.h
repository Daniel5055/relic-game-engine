#pragma once

#include "MessageBus.decl.h"

#include "MessageReceiver.h"

namespace relic
{
    template <typename T>
    void MessageBus<T>::addReceiver(MessageReceiver<T>* receiver)
    {
        m_receivers.push_back(receiver);
    }

    template <typename T>
    void MessageBus<T>::removeReceiver(MessageReceiver<T>* receiver)
    {
        m_receivers.erase(std::remove(m_receivers.begin(), m_receivers.end(), receiver), m_receivers.end());
    }

    template <typename T>
    void MessageBus<T>::forwardMessage(Message<T> msg, const bool locally)
    {
        if (locally)
        {
            for (auto& receiver : m_receivers)
            {
                if (receiver->getIdentifier() == *msg.from)
                {
                    receiver->receiveMessage(msg);
                }
            }
        }
        else
        {
            for (auto& receiver : m_receivers)
            {
                if (msg.to == nullptr)
                {
                    if (receiver->isLocal() && receiver->getIdentifier() == *msg.from || !receiver->isLocal())
                    {
                        receiver->receiveMessage(msg);
                    }
                }
                else
                {
                    if (receiver->getIdentifier() == *msg.to && (receiver->isLocal() && receiver->getIdentifier() == *msg.from || !receiver->isLocal()))
                    {
                        receiver->receiveMessage(msg);
                    }
                }
            }

        }
    }
}
