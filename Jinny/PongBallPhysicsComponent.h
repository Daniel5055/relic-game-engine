#pragma once

#include "RigidBodyPhysicsComponent.h"

namespace relic
{
    namespace pong
    {
        class PongBallPhysicsComponent : public RigidBodyPhysicsComponent
        {

        public:
            PongBallPhysicsComponent(framework::Shape shape, int left_wall_id, int right_wall_id);

        private:
            void handleMessage(PhysicsMessage msg) override;

            const int m_left_wall_id;
            const int m_right_wall_id;
        };
    }

}

