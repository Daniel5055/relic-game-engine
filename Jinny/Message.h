#pragma once

#include <any>

#include "Identifier.h"

namespace relic
{
    /**
     * \brief The base struct for messages sent between systems and components
     * \tparam T A message type enum
     */
    template<typename T>
    struct Message
    {
        Message(T t, std::any v)
            :type(t), value(std::move(v))
        {
        }

        Message(T t)
            :type(t)
        {
            
        }

        Message()
        = default;

        T type;
        std::any value{};

        const Identifier* from{nullptr };
        const Identifier* to{nullptr};

    };
}
