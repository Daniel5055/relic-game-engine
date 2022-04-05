#pragma once

#include <memory>

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "PhysicsMessage.h"

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
        public MessageReceiver<PhysicsMessage>
    {
    public:
        // Constructor
        explicit PhysicsSystem(PhysicsEngine* engine);

    private:
        // --- Internal Functions ---

        void doUpdates() override;
        void handleMessage(PhysicsMessage msg) override;

        // --- Data ---

        // Physics Engine
        std::unique_ptr<PhysicsEngine> m_engine_ptr;
    };
}