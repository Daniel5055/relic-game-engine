#pragma once

#include "PhysicsComponent.h"

#include "RigidBody.h"
#include "Shape.h"

namespace jinny
{
    /** \brief Component that defines dynamic rigid body that reacts to input */
    class PlayerPhysicsComponent : public PhysicsComponent
    {
    public:
        // Constructor
        PlayerPhysicsComponent(double mass, double max_x_speed, double max_y_speed, framework::Shape shape);
    private:
        void handleEvent(ObjectEvent e) override;

        void doUpdates() override;

        framework::RigidBody m_rigid_body;
        framework::Point m_last_position;
    };

}