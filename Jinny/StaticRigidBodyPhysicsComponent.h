#pragma once

#include "PhysicsComponent.h"

#include "Material.h"
#include "RigidBody.h"
#include "Shape.h"

namespace relic
{
    /**
     * \brief Component that represents a static rigidBody, a body that does not react to collisions
     */
    class StaticRigidBodyPhysicsComponent : public PhysicsComponent
    {
    public:
        // Constructor
        explicit StaticRigidBodyPhysicsComponent(framework::Shape shape, framework::Material material = framework::Material::nullium);

    private:
        // --- Data ---
        framework::RigidBody m_rigid_body;
    };
}