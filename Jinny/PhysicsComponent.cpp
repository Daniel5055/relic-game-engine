#include "PhysicsComponent.h"

relic::PhysicsComponent::PhysicsComponent()
    : MessageSender<PhysicsSystemType>(getId()), MessageSender<ObjectType>(getId(), true)
{
}
