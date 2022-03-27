#include "PhysicsEngine.h"

Jinny::PhysicsEngine::PhysicsEngine()
{
}

void Jinny::PhysicsEngine::initialise(const Framework::Physics* physics_ptr)
{
    f_physics = physics_ptr;
}

void Jinny::PhysicsEngine::close()
{
}

void Jinny::PhysicsEngine::addRigidBody(int object_id, Framework::RigidBody* rigid_body)
{
    m_rigid_bodies.insert({ object_id, rigid_body });
}
