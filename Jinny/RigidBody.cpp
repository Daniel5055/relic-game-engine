#include "RigidBody.h"

#include "Physics.h"

#include <cmath>

Framework::RigidBody::RigidBody(double mass, double dampening, Framework::Shape* shape_ptr, Framework::Material material)
{
    m_mass = mass;
    m_dampening = dampening;
    m_rigid_body_shape_ptr = shape_ptr;
    m_material = material;
    m_is_static = false;

    m_current_velocity = { 0, 0 };

    m_mf_force = { 0, 0 };
    m_sf_force = { 0, 0 };

    m_time_after_tick = 0;
}

double Framework::RigidBody::getMass() const
{
    return m_mass;
}

void Framework::RigidBody::setMass(double mass)
{
    m_mass = mass;
}

Framework::Vector Framework::RigidBody::getVelocity()
{
    return m_current_velocity;
}

void Framework::RigidBody::increaseVelocity(Vector additional_velocity)
{
    m_current_velocity += additional_velocity;
}

void Framework::RigidBody::stopXVelocity()
{
    m_current_velocity.x_value = 0;
}

void Framework::RigidBody::stopYVelocity()
{
    m_current_velocity.y_value = 0;
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

double Framework::RigidBody::getXMovement() const
{
    return m_x_moved;
}

double Framework::RigidBody::getYMovement() const
{
    return m_y_moved;
}

void Framework::RigidBody::setMovement(double x_moved, double y_moved)
{
    m_x_moved = x_moved;
    m_y_moved = y_moved;
}

void Framework::RigidBody::addTickMovement(double x_moved, double y_moved)
{
    m_x_moved += x_moved;
    m_y_moved += y_moved;
}

void Framework::RigidBody::setXMovement(double x_moved)
{
    m_x_moved += x_moved;
}

void Framework::RigidBody::setYMovement(double y_moved)
{
    m_y_moved += y_moved;
}

double Framework::RigidBody::getTimeAfterTick()
{
    return m_time_after_tick;
}

void Framework::RigidBody::setTimeAfterTick(double time)
{
    m_time_after_tick = time;
}

bool Framework::RigidBody::isStationary() const
{
    if (m_current_velocity.x_value == 0 && m_current_velocity.y_value == 0)
    {
        // TODO: could be janky this
        if (m_x_moved == 0 && m_y_moved == 0)
        {
            return true;
        }
    }

    return false;
}

double Framework::RigidBody::getDampening() const
{
    return m_dampening;
}

double Framework::RigidBody::getX() const
{
    return m_exact_x;
}

double Framework::RigidBody::getY() const
{
    return m_exact_y;
}

void Framework::RigidBody::setX(int x)
{
    m_rigid_body_shape_ptr->x = x;
    m_exact_x = x;
}

void Framework::RigidBody::setY(int y)
{
    m_rigid_body_shape_ptr->y = y;
    m_exact_y = y;
}

void Framework::RigidBody::move()
{
    m_exact_x += m_x_moved;
    m_exact_y += m_y_moved;

    int whole_x = round(m_exact_x);
    if (whole_x != m_rigid_body_shape_ptr->x)
    {
        m_rigid_body_shape_ptr->x = whole_x;
    }

    int whole_y = round(m_exact_y);
    if (whole_y != m_rigid_body_shape_ptr->y)
    {
        m_rigid_body_shape_ptr->y = whole_y;
    }
}

int Framework::RigidBody::getRoundedX() const
{
    return m_rigid_body_shape_ptr->x;
}

int Framework::RigidBody::getRoundedY() const
{
    return m_rigid_body_shape_ptr->y;
}

void Framework::RigidBody::setShape(Framework::Shape* shape_ptr)
{
    m_rigid_body_shape_ptr = shape_ptr;
    m_exact_x = shape_ptr->x;
    m_exact_y = shape_ptr->y;
}

int Framework::RigidBody::getWidth() const
{
    return m_rigid_body_shape_ptr->w;
}

int Framework::RigidBody::getHeight() const
{
    return m_rigid_body_shape_ptr->h;
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
