#include "PhysicsEngine.h"

relic::PhysicsEngine::PhysicsEngine(const framework::Physics& physics)
    :f_physics(physics)
{
}

void relic::PhysicsEngine::addRigidBody(int object_id, framework::RigidBody* rigid_body)
{
    m_rigid_bodies.insert({ object_id, rigid_body });
}
