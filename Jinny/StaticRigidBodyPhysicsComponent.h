#pragma once

#include "RigidBodyPhysicsComponent.h"

#include "Material.h"
#include "RigidBody.h"
#include "Shape.h"

namespace relic
{
    /**
     * \brief Component that represents a static rigidBody, a body that does not react to collisions
     */
    class StaticRigidBodyPhysicsComponent : public RigidBodyPhysicsComponent
    {
    public:
        // Constructor
        explicit StaticRigidBodyPhysicsComponent(framework::Shape shape, framework::Material material = framework::Material::nullium, double max_x_speed = 0, double max_y_speed = 0);
    };
}