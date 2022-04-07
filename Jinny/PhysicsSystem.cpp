#include "PhysicsSystem.h"
#include "GridPhysicsEngine.h"

relic::PhysicsSystem::PhysicsSystem(PhysicsEngine* engine)
    :m_engine_ptr(engine)
{
}

void relic::PhysicsSystem::doUpdates()
{
    // Handle Messages
    handleMessages();

    // Update physics engine
    m_engine_ptr->update();
    for (const auto& ids : m_engine_ptr->getTickCollisions())
    {
        if (m_subscribed_collision_checking[ids.first])
        {
            PhysicsMessage msg;

            msg.type = PMessageType::collision_occurred;
            msg.object_id = ids.first;
            msg.colliding_object_id = ids.second;
            msg.is_sent_by_system = true;

            sendMessage(msg);
        }
        if (m_subscribed_collision_checking[ids.second])
        {
            PhysicsMessage msg;

            msg.type = PMessageType::collision_occurred;
            msg.object_id = ids.second;
            msg.colliding_object_id = ids.first;
            msg.is_sent_by_system = true;

            sendMessage(msg);
        }
    }
}

void relic::PhysicsSystem::handleMessage(const PhysicsMessage msg)
{
    // NOTE: for simplicity, physics based objects cannot be gui objects 

    switch (msg.type)
    {
    case PMessageType::set_rigid_body:
        m_engine_ptr->addRigidBody(msg.object_id, msg.rigid_body);
        if (m_subscribed_collision_checking.find(msg.object_id) == m_subscribed_collision_checking.end())
        {
            m_subscribed_collision_checking[msg.object_id] = false;
        }
        break;
    case PMessageType::register_collision_checking:
        m_subscribed_collision_checking[msg.object_id] = true;
    }
}

