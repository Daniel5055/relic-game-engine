#include "PhysicsSystem.h"

#include "Physics.h"
#include "RigidBody.h"
#include "Shape.h"
#include "GridPhysicsEngine.h"

Jinny::PhysicsSystem::PhysicsSystem()
{
    m_engine = new GridPhysicsEngine();
}

void Jinny::PhysicsSystem::intialize(Framework::Physics* physics, MessageBoard<PhysicsMessage>* message_board)
{
    m_message_board = message_board;

    m_engine->initialise(physics);
}

void Jinny::PhysicsSystem::update()
{
    // Handle Messages
    handleMessages();

    // Update physics engine
    m_engine->update();
}

void Jinny::PhysicsSystem::close()
{
    m_engine->close();
}

void Jinny::PhysicsSystem::handleMessages()
{
    // NOTE: for simplicity, physics based objects cannot be gui objects 

    // Pop all messages from message board
    int size = m_message_board->getQueueSize();
    for (int it = 0; it < size; it++)
    {
        PhysicsMessage msg = m_message_board->popMessage();

        switch (msg.type)
        {
        case PMessageType::SET_RIGID_BODY:
            m_engine->addRigidBody(msg.object_ID, msg.rigid_body);
            break;
        }
    }
}


