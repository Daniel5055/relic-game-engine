#include "PhysicsSystem.h"

#include "Physics.h"
#include "RigidBody.h"
#include "Shape.h"
#include "GridPhysicsEngine.h"

Jinny::PhysicsSystem::PhysicsSystem(PhysicsEngine* t_engine_ptr, MessageBoard<PhysicsMessage>& t_message_board)
    :m_engine_ptr(t_engine_ptr), m_message_board(t_message_board)
{
}

void Jinny::PhysicsSystem::update()
{
    // Handle Messages
    handleMessages();

    // Update physics engine
    m_engine_ptr->update();
}

void Jinny::PhysicsSystem::handleMessages()
{
    // NOTE: for simplicity, physics based objects cannot be gui objects 

    // Pop all messages from message board
    int size = m_message_board.getQueueSize();
    for (int it = 0; it < size; it++)
    {
        PhysicsMessage msg = m_message_board.popMessage();

        switch (msg.type)
        {
        case PMessageType::SET_RIGID_BODY:
            m_engine_ptr->addRigidBody(msg.object_ID, msg.rigid_body);
            break;
        }
    }
}


