#include "PhysicsSystem.h"
#include "GridPhysicsEngine.h"

jinny::PhysicsSystem::PhysicsSystem(PhysicsEngine* engine)
    :m_engine_ptr(engine)
{
}

void jinny::PhysicsSystem::doUpdates()
{
    // Handle Messages
    handleMessages();

    // Update physics engine
    m_engine_ptr->update();
}

void jinny::PhysicsSystem::handleMessage(const PhysicsMessage msg)
{
    // NOTE: for simplicity, physics based objects cannot be gui objects 

    switch (msg.type)
    {
    case PMessageType::set_rigid_body:
        m_engine_ptr->addRigidBody(msg.object_id, msg.rigid_body);
        break;
    }
}

