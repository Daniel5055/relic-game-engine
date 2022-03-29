#pragma once

#include "GameSystem.h"

#include "MessageBoard.h"
#include "PhysicsMessage.h"
#include "PhysicsEngine.h"
#include <memory>

namespace Framework
{
    class Physics;
}

namespace Jinny
{
    /**
     * System for handling physics between objects.
     */
    class PhysicsSystem : public GameSystem
    {
    public:
        // Constructor
        PhysicsSystem(PhysicsEngine* t_engine, MessageBoard<PhysicsMessage>& t_message_board);

        // Updating
        void update();

    private:
        // --- Internal Functions ---

        // Message handling
        void handleMessages();

        // --- Data ---

        // Message Board
        MessageBoard<PhysicsMessage>& m_message_board;

        // Physics Engine
        std::unique_ptr<PhysicsEngine> m_engine_ptr;
    };
}