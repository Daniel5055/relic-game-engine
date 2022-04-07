#include "PhysicsEngine.h"

relic::PhysicsEngine::PhysicsEngine(const framework::Physics& physics)
    :f_physics(physics)
{
}

std::vector<std::pair<int, int>> relic::PhysicsEngine::getTickCollisions()
{
    return m_accumulated_tick_collisions;
}

void relic::PhysicsEngine::addRigidBody(int object_id, framework::RigidBody* rigid_body)
{
    m_rigid_bodies.insert({ object_id, rigid_body });
}

void relic::PhysicsEngine::registerCollision(int object_1, int object_2)
{
    m_accumulated_tick_collisions.push_back({ object_1, object_2 });
}

void relic::PhysicsEngine::restartTick()
{
    m_accumulated_tick_collisions.clear();
}
