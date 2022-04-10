#include "PhysicsSystem.h"
#include "GridPhysicsEngine.h"

relic::PhysicsSystem::PhysicsSystem(PhysicsEngine* engine)
    : MessageReceiver<PhysicsSystemType>(Identifier::null),
      MessageSender<PhysicsObjectType>(Identifier::null), m_engine_ptr(engine)
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
            Message msg{ PhysicsObjectType::collision_occurred, std::make_any<Identifier>(ids.second)};
            msg.to = ids.first;

            sendMessage(msg);
        }
        if (m_subscribed_collision_checking[ids.second])
        {
            Message msg{ PhysicsObjectType::collision_occurred, std::make_any<Identifier>(ids.first)};
            msg.to = ids.second;

            sendMessage(msg);
        }
    }
}

void relic::PhysicsSystem::handleMessage(const Message<PhysicsSystemType>& msg)
{
    // NOTE: for simplicity, physics based objects cannot be gui objects 

    switch (msg.type)
    {
    case PhysicsSystemType::set_rigid_body:
        m_engine_ptr->addRigidBody(msg.from, std::any_cast<framework::RigidBody*>(msg.value));
        if (m_subscribed_collision_checking.find(msg.from) == m_subscribed_collision_checking.end())
        {
            m_subscribed_collision_checking[msg.from] = false;
        }
        break;
    case PhysicsSystemType::remove_rigid_body:
        m_engine_ptr->removeRigidBody(msg.from);
        break;
    case PhysicsSystemType::register_collision_checking:
        m_subscribed_collision_checking[msg.from] = true;
        break;
    }
}

