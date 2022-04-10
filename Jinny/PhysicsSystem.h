#pragma once

#include <memory>

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "PhysicsType.h"

#include "PhysicsEngine.h"

namespace framework
{
    class Physics;
}

namespace relic
{
    /**
     * \brief System for handling physics between objects.
     */
    class PhysicsSystem final : 
        public GameSystem,
        public MessageReceiver<PhysicsSystemType>,
        public MessageSender<PhysicsObjectType>
    {
    public:
        // Constructor
        explicit PhysicsSystem(PhysicsEngine* engine);

    private:
        // --- Internal Functions ---

        void doUpdates() override;
        void handleMessage(const Message<PhysicsSystemType>& msg) override;

        // --- Data ---

        // Physics Engine
        std::unique_ptr<PhysicsEngine> m_engine_ptr;
        std::map<Identifier, bool> m_subscribed_collision_checking;
    };
}