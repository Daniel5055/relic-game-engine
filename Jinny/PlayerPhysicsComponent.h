#pragma once

#include "RigidBodyPhysicsComponent.h"

#include "RigidBody.h"
#include "Shape.h"

namespace relic
{
    /** \brief Component that defines dynamic rigid body that reacts to input */
    class PlayerPhysicsComponent
    : public RigidBodyPhysicsComponent
    , public MessageReceiver<ObjectType>
    {
    public:
        // Constructor
        PlayerPhysicsComponent(double mass, double max_x_speed, double max_y_speed, framework::Shape shape);
    private:
        void handleMessage(const Message<ObjectType>& msg) override;

        void doUpdates() override;
    };

}