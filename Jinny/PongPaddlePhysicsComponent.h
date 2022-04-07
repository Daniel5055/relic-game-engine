#pragma once
#include "RigidBodyPhysicsComponent.h"

namespace relic
{
    namespace pong
    {
        class PongPaddlePhysicsComponent final :
            public RigidBodyPhysicsComponent
        {
        public:
            explicit PongPaddlePhysicsComponent(framework::Shape shape, char up_key, char down_key);
        private:
            void handleEvent(ObjectEvent e) override;

            const char m_up_key;
            const char m_down_key;
        };
    }
}

