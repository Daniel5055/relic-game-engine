#pragma once

#include "PhysicsComponent.h"

#include "Vector.h"
#include "Material.h"
#include "RigidBody.h"

namespace relic
{
    //TODO: Make rigidbodies inherit from abstract rigid body class
    /**
     * \brief Component that represents a dynamic rigidBody
     */
    class RigidBodyPhysicsComponent : public PhysicsComponent
    {
    public:
        // Constructor
        RigidBodyPhysicsComponent(double mass, double damping_force, framework::Shape shape, 
            framework::Material material = framework::Material::nullium,
            double max_x_speed = 0, double max_y_speed = 0, framework::Vector applied_force = { 0, 0 });
    protected:
        framework::RigidBody& getRigidBody();
    private:
        void doUpdates() override;
        // --- data ---
        framework::RigidBody m_rigid_body;
        framework::Point m_last_position;
    };
}