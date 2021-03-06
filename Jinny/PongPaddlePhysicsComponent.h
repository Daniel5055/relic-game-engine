#pragma once
#include "RigidBodyPhysicsComponent.h"

namespace relic
{
    namespace pong
    {
        class PongPaddlePhysicsComponent final
            : public RigidBodyPhysicsComponent
            , public MessageReceiver<ObjectType>
        {
        public:
            explicit PongPaddlePhysicsComponent(framework::Shape shape, framework::Direction facing, char up_key, char down_key);
        protected:
            void doUpdates() override;
        private:
            void handleMessage(const Message<ObjectType>& msg) override;

            const char m_up_key;
            const char m_down_key;
        };
    }
}

