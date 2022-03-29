#pragma once

#include "PhysicsComponent.h"

#include "Vector.h"
#include "Material.h"
namespace Framework
{
    class RigidBody;
    class RigidBody;
}

namespace Jinny
{
    class DynamicRigidBodyPhysicsComponent : public PhysicsComponent
    {
    public:
        // Constructor
        DynamicRigidBodyPhysicsComponent(double mass, double max_x_speed, double max_y_speed, Framework::Material material = Framework::Material::NULLIUM, Framework::Vector applied_force = { 0, 0 });

        // Initialize
        void initialize(GameObject& object);

        // Update
        void update();

        // Destructor
        ~DynamicRigidBodyPhysicsComponent();

    private:
        // --- data
        Framework::RigidBody* m_rigid_body;
    };
}