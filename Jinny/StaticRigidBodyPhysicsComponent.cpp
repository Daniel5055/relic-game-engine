#include "StaticRigidBodyPhysicsComponent.h"

#include "RigidBody.h"

relic::StaticRigidBodyPhysicsComponent::StaticRigidBodyPhysicsComponent(const framework::Shape shape,
    const framework::Material material, double max_x_speed, double max_y_speed)
    : RigidBodyPhysicsComponent(1, 0, shape, material)
{
    getRigidBody().setStatic(true);
}
