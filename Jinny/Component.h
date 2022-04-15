#pragma once

#include "Identifier.h"
#include "MessageSender.h"
#include "LoggingType.h"

namespace relic
{
    /**
     * \brief Base class for all components
     */
    class Component
        :public MessageSender<LoggingType>
    {
    public:
        Component();

        // Virtual destructor because component pointers would likely be deleted
        virtual ~Component() = default;

        // Updating
        void update();

        // id setter and getter
        void setId(const Identifier& id, int component_count);
        const Identifier& getId() const;

    protected:

        // Protected virtual method (allowing and usually recommending derived classes to call overrided super method)
        virtual void doUpdates() {}

    private:

        // Copy of the object id so messageExchangers can store a reference 
        Identifier m_id{ Identifier::null };
    };
}


