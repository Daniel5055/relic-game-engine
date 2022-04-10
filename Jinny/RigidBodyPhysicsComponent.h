#pragma once

#include "PhysicsComponent.h"

#include "Vector.h"
#include "Material.h"
#include "Point.h"
#include "RigidBody.h"

namespace relic
{
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
        ~RigidBodyPhysicsComponent() override;
    protected:
        framework::RigidBody& getRigidBody();
        void doUpdates() override;
    private:
        // --- data ---
        framework::RigidBody m_rigid_body;
        framework::Point m_last_position;
    };
}