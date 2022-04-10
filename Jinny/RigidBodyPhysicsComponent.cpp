#include "RigidBodyPhysicsComponent.h"

#include "RigidBody.h"

relic::RigidBodyPhysicsComponent::RigidBodyPhysicsComponent(const double mass, const double damping_force, framework::Shape shape,
    const framework::Material material, double max_x_speed, double max_y_speed, const framework::Vector applied_force)
    :m_rigid_body(mass, damping_force, { max_x_speed, max_y_speed }, shape, material), m_last_position({ shape.x, shape.y })
{
    m_rigid_body.applySFForce(applied_force);

    MessageSender<PhysicsSystemType>::sendMessage({ PhysicsSystemType::set_rigid_body, std::make_any<framework::RigidBody*>(&m_rigid_body) });
}

relic::RigidBodyPhysicsComponent::~RigidBodyPhysicsComponent()
{
    MessageSender<PhysicsSystemType>::sendImmediateMessage({ PhysicsSystemType::remove_rigid_body });
}

framework::RigidBody& relic::RigidBodyPhysicsComponent::getRigidBody()
{
    return m_rigid_body;
}

void relic::RigidBodyPhysicsComponent::doUpdates()
{
    PhysicsComponent::doUpdates();

    // If moved
    const int x_diff = m_rigid_body.getRoundedX() - m_last_position.x;
    const int y_diff = m_rigid_body.getRoundedY() - m_last_position.y;
    if (x_diff != 0 || y_diff != 0)
    {
        // Send move message
        Message e{ ObjectType::move, std::make_any<framework::Point>(x_diff, y_diff) };
        MessageSender<ObjectType>::sendMessage(e);

        m_last_position.x = m_rigid_body.getRoundedX();
        m_last_position.y = m_rigid_body.getRoundedY();
    }
}
