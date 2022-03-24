#include "RigidBody.h"

#include "Physics.h"

#include <cmath>

Framework::RigidBody::RigidBody(double mass, double dampening, Framework::Shape* shape_ptr, Framework::Material material)
{
    m_mass = mass;
    m_dampening = dampening;
    m_shape_ptr = shape_ptr;
    m_material = material;
    m_is_static = false;

    m_current_velocity = { 0, 0 };

    m_mf_force = { 0, 0 };
    m_sf_force = { 0, 0 };
}

double Framework::RigidBody::getMass() const
{
    return m_mass;
}

void Framework::RigidBody::setMass(double mass)
{
    m_mass = mass;
}

Framework::Vector Framework::RigidBody::getVelocity() const
{
    return m_current_velocity;
}

void Framework::RigidBody::increaseVelocity(Vector additional_velocity)
{
    m_current_velocity += additional_velocity;
    if (abs(m_current_velocity[0]) < 0.00000000001)
    {
        m_current_velocity[0] = 0.0;
    }
    if (abs(m_current_velocity[1]) < 0.00000000001)
    {
        m_current_velocity[1] = 0.0;
    }
}

void Framework::RigidBody::stopXVelocity()
{
    m_current_velocity.x = 0;
}

void Framework::RigidBody::stopYVelocity()
{
    m_current_velocity.y = 0;
}

void Framework::RigidBody::stopVelocity()
{
    m_current_velocity.x = 0;
    m_current_velocity.y = 0;
}

Framework::Vector Framework::RigidBody::getAppliedForce()
{
    Vector applied_force = m_mf_force + m_sf_force;
    return applied_force;
}

void Framework::RigidBody::clearSFForce()
{
    m_sf_force.clear();
}

void Framework::RigidBody::applyMFForce(Vector force)
{
    m_mf_force += force;
}

void Framework::RigidBody::applySFForce(Vector force)
{
    m_sf_force += force;
}

bool Framework::RigidBody::isStationary() const
{
    if (m_current_velocity.x == 0 && m_current_velocity.y == 0)
    {
        return true;
    }

    return false;
}

double Framework::RigidBody::getDampening() const
{
    return m_dampening;
}

void Framework::RigidBody::move(Vector movement)
{
    m_position += movement;

    int whole_x = round(m_position.x);
    if (whole_x != m_shape_ptr->x)
    {
        m_shape_ptr->x = whole_x;
    }

    int whole_y = round(m_position.y);
    if (whole_y != m_shape_ptr->y)
    {
        m_shape_ptr->y = whole_y;
    }
}

int Framework::RigidBody::getRoundedX() const
{
    return m_shape_ptr->x;
}

int Framework::RigidBody::getRoundedY() const
{
    return m_shape_ptr->y;
}

void Framework::RigidBody::setShape(Framework::Shape* shape_ptr)
{
    m_shape_ptr = shape_ptr;
    m_position = Vector(shape_ptr->x, shape_ptr->y);
}

int Framework::RigidBody::getWidth() const
{
    return m_shape_ptr->w;
}

int Framework::RigidBody::getHeight() const
{
    return m_shape_ptr->h;
}

Framework::Vector Framework::RigidBody::getSize() const
{
    return Vector(m_shape_ptr->w, m_shape_ptr->h);
}

Framework::Vector Framework::RigidBody::getPosition() const
{
    return m_position;
}

void Framework::RigidBody::setPosition(Vector position)
{
    m_position = position;
    m_shape_ptr->x = round(position.x);
	m_shape_ptr->y = round(position.y);
}

bool Framework::RigidBody::isStatic() const
{
    return m_is_static;
}

void Framework::RigidBody::setStatic(bool is_static)
{
    m_is_static = is_static;
}

Framework::Material Framework::RigidBody::getMaterial() const
{
    return m_material;
}
