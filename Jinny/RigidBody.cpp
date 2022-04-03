#include "RigidBody.h"

#include "Physics.h"

#include <cmath>

framework::RigidBody::RigidBody(const double mass, const double damping_force, const framework::Vector max_speed, const framework::Shape shape, const framework::Material material)
    : m_mass(mass), m_damping(damping_force), m_shape(shape), m_position(shape.x, shape.y), m_material(material), m_max_speed(max_speed)
{
}

double framework::RigidBody::getMass() const
{
    return m_mass;
}

framework::Vector framework::RigidBody::getVelocity() const
{
    return m_current_velocity;
}

void framework::RigidBody::increaseVelocity(const Vector additional_velocity)
{
    m_current_velocity += additional_velocity;

    // Ensure speed is within limit if specified
    for (const int axis : {0, 1})
    {
        if (0 != m_max_speed[axis] && abs(m_current_velocity[axis]) > m_max_speed[axis])
        {
            if (m_current_velocity[axis] > 0)
            {
                m_current_velocity[axis] = m_max_speed[axis];
            }
            else
            {
                m_current_velocity[axis] = -m_max_speed[axis];

            }
        }
    }

    // Prevent stupidly small non zero velocities
    if (abs(m_current_velocity[0]) < 0.00000000001)
    {
        m_current_velocity[0] = 0.0;
    }
    if (abs(m_current_velocity[1]) < 0.00000000001)
    {
        m_current_velocity[1] = 0.0;
    }
}

framework::Vector framework::RigidBody::getAppliedForce()
{
    return m_mf_force + m_sf_force;
}

void framework::RigidBody::clearSFForce()
{
    m_sf_force.clear();
}

void framework::RigidBody::applyMFForce(const Vector force)
{
    m_mf_force += force;
}

void framework::RigidBody::applySFForce(const Vector force)
{
    m_sf_force += force;
}

bool framework::RigidBody::isStationary() const
{
    if (m_current_velocity.x == 0 && m_current_velocity.y == 0)
    {
        return true;
    }

    return false;
}

double framework::RigidBody::getDamping() const
{
    return m_damping;
}

void framework::RigidBody::move(Vector movement)
{
    m_position += movement;

    const int whole_x = static_cast<int>(round(m_position.x));
    if (whole_x != m_shape.x)
    {
        m_shape.x = whole_x;
    }

    const int whole_y = static_cast<int>(round(m_position.y));
    if (whole_y != m_shape.y)
    {
        m_shape.y = whole_y;
    }
}

int framework::RigidBody::getRoundedX() const
{
    return m_shape.x;
}

int framework::RigidBody::getRoundedY() const
{
    return m_shape.y;
}

int framework::RigidBody::getWidth() const
{
    return m_shape.w;
}

int framework::RigidBody::getHeight() const
{
    return m_shape.h;
}

framework::Vector framework::RigidBody::getSize() const
{
    return {static_cast<double>(m_shape.w), static_cast<double>(m_shape.h)};
}

framework::Vector framework::RigidBody::getPosition() const
{
    return m_position;
}

void framework::RigidBody::setPosition(Vector position)
{
    m_position = position;
    m_shape.x = static_cast<int>(round(position.x));
    m_shape.y = static_cast<int>(round(position.y));
}

bool framework::RigidBody::isStatic() const
{
    return m_is_static;
}

void framework::RigidBody::setStatic(const bool is_static)
{
    m_is_static = is_static;
}

framework::Material framework::RigidBody::getMaterial() const
{
    return m_material;
}
