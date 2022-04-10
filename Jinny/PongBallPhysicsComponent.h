#pragma once

#include "RigidBodyPhysicsComponent.h"

#include "MessageReceiver.h"
#include "MessageSender.h"
#include "PongType.h"

namespace relic::pong
{
    class PongBallPhysicsComponent final
        : public RigidBodyPhysicsComponent
        , public MessageReceiver<PhysicsObjectType>
        , public MessageSender<PongType>
    {

    public:
        PongBallPhysicsComponent(framework::Shape shape, Identifier left_wall_id, Identifier right_wall_id);

        void doUpdates() override;

    private:
        void handleMessage(const Message<PhysicsObjectType>& msg) override;


        const Identifier m_left_wall_id;
        const Identifier m_right_wall_id;
    };
}

