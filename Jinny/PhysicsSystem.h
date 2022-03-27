#pragma once

#include "GameSystem.h"

#include "MessageBoard.h"
#include "PhysicsMessage.h"
#include "PhysicsEngine.h"

namespace Framework
{
    class Physics;
}

namespace Jinny
{
    class PhysicsSystem : public GameSystem
    {
    public:
        // Constructor
        PhysicsSystem();
        // Initialize
        void intialize(Framework::Physics* physics, MessageBoard<PhysicsMessage>* message_board);

        // Updating
        void update();

        // Closing
        void close();
    private:
        void handleMessages();

        // --- Internal Functions ---

        // Message Board
        MessageBoard<PhysicsMessage>* m_message_board;

        // Physics Engine
        PhysicsEngine* m_engine;
    };
}