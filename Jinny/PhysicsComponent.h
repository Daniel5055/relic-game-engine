#pragma once

#include "Component.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "PhysicsType.h"
#include "ObjectType.h"

namespace relic
{
    /**
     * \brief Base abstract class for components relating to physics
     */
    class PhysicsComponent
        : public Component
        , public MessageSender<PhysicsSystemType>
        , public MessageSender<ObjectType>
    {
    public:
        PhysicsComponent();
    };
}

