#pragma once

#include "Deliverable.h"

namespace relic
{
    /**
     * \brief The base struct for messages sent between systems and components
     */
    struct Message
    {
        virtual ~Message() = default;
        enum class Type
        {
            none,
            graphics,
            input,
            physics,
            core
        };

        Type getType() const
        {
            return m_type;
        }

        // Either sent by object or system
        bool is_sent_by_system{false};
        int object_id{-1};

    protected:
        explicit Message(const Type type = Type::none) : m_type(type) {}
    private:
        // Type is hidden because it can only be declared on construction of message by the message
        Type m_type;
    };
}
