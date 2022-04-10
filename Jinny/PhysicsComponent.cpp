#include "PhysicsComponent.h"

relic::PhysicsComponent::PhysicsComponent()
    : MessageSender<PhysicsSystemType>(getObjectId()), MessageSender<ObjectType>(getObjectId(), true)
{
}
