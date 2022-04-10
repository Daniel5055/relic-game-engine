#pragma once

#include "Identifier.h"

namespace relic
{
    /**
     * \brief Base class for all components
     */
    class Component
    {
    public:

        // Virtual destructor because component pointers would likely be deleted
        virtual ~Component() = default;

        // Updating
        void update();

        // id setter
        void setObjectId(const Identifier& id);

    protected:
        // id getter
        const Identifier& getObjectId() const;

        // Protected virtual method (allowing and usually recommending derived classes to call overrided super method)
        virtual void doUpdates() {}

    private:

        // Copy of the object id so messageExchangers can store a reference 
        Identifier m_id{ Identifier::null_identifier };

    };
}


