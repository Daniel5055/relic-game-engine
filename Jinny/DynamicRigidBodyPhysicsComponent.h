#pragma once

#include "PhysicsComponent.h"

#include "Vector.h"
#include "Material.h"
#include "RigidBody.h"

namespace jinny
{
    //TODO: Make rigidbodies inherit from abstract rigid body class
    /**
     * \brief Component that represents a dynamic rigidBody
     */
    class DynamicRigidBodyPhysicsComponent : public PhysicsComponent
    {
    public:
        // Constructor
        DynamicRigidBodyPhysicsComponent(double mass, double max_x_speed, double max_y_speed, framework::Shape shape, 
            framework::Material material = framework::Material::nullium, framework::Vector applied_force = { 0, 0 });
    private:
        void doUpdates() override;
        // --- data ---
        framework::RigidBody m_rigid_body;
        framework::Point m_last_position;
    };
}