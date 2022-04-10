#pragma once

#include <vector>

#include "Message.h"

namespace relic
{
    template<typename T>
    class MessageReceiver;

    /**
     * \brief A class used to forward messages to receivers of the same message type
     * \tparam T A message type
     */
    template<typename T>
    class MessageBus
    {
    public:
        void addReceiver(MessageReceiver<T>* receiver);
        void removeReceiver(MessageReceiver<T>* receiver);

        void forwardMessage(Message<T> msg, bool locally = false);
    private:
        std::vector<MessageReceiver<T>*> m_receivers;
    };
}
