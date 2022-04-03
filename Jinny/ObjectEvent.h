#pragma once

#include "ObjectInput.h"
#include "Point.h"

namespace jinny
{

    /**
     * \brief Messages sent between components in an object
     */
    struct ObjectEvent
    {
        enum class Type
        {
            null_event,
            component_incorporated,
            input_triggered,
            move,
        };

        Type type{ Type::null_event };

        union
        {
            ObjectInput input;
            framework::Point movement;
        };
    };
}


