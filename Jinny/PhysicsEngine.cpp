#include "PhysicsEngine.h"

Jinny::PhysicsEngine::PhysicsEngine(const Framework::Physics& t_physics)
    :f_physics(t_physics)
{
}

void Jinny::PhysicsEngine::addRigidBody(int object_id, Framework::RigidBody* rigid_body)
{
    m_rigid_bodies.insert({ object_id, rigid_body });
}
