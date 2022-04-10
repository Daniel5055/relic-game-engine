#include "PhysicsEngine.h"

relic::PhysicsEngine::PhysicsEngine(const framework::Physics& physics)
    :f_physics(physics)
{
}

std::vector<std::pair<relic::Identifier, relic::Identifier>> relic::PhysicsEngine::getTickCollisions()
{
    return m_accumulated_tick_collisions;
}

void relic::PhysicsEngine::addRigidBody(const Identifier& object_id, framework::RigidBody* rigid_body)
{
    m_rigid_bodies.insert({ object_id, rigid_body });
}

void relic::PhysicsEngine::removeRigidBody(const Identifier& object_id)
{
    if (const auto it = m_rigid_bodies.find(object_id); it != m_rigid_bodies.end())
    {
        m_rigid_bodies.erase(it);
    }
}

void relic::PhysicsEngine::registerCollision(const Identifier& object_1, const Identifier& object_2)
{
    m_accumulated_tick_collisions.emplace_back(object_1, object_2);
}

void relic::PhysicsEngine::restartTick()
{
    m_accumulated_tick_collisions.clear();
}
