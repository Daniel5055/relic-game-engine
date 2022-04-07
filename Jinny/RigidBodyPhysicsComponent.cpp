#include "RigidBodyPhysicsComponent.h"

#include "RigidBody.h"

relic::RigidBodyPhysicsComponent::RigidBodyPhysicsComponent(const double mass, const double damping_force, framework::Shape shape,
    const framework::Material material, double max_x_speed, double max_y_speed, const framework::Vector applied_force)
    :m_rigid_body(mass, damping_force, { max_x_speed, max_y_speed }, shape, material), m_last_position({ shape.x, shape.y })
{
    m_rigid_body.applySFForce(applied_force);
    PhysicsMessage msg;
    msg.type = PMessageType::set_rigid_body;
    msg.object_id = getObjectId();
    msg.rigid_body = &m_rigid_body;

    sendMessage(msg);
}

framework::RigidBody& relic::RigidBodyPhysicsComponent::getRigidBody()
{
    return m_rigid_body;
}

void relic::RigidBodyPhysicsComponent::doUpdates()
{
    MessageReceiver<PhysicsMessage>::handleMessages();

    // If moved
    const int x_diff = m_rigid_body.getRoundedX() - m_last_position.x;
    const int y_diff = m_rigid_body.getRoundedY() - m_last_position.y;
    if (x_diff != 0 || y_diff != 0)
    {
        // Send move message
        ObjectEvent e{ ObjectEvent::Type::move };
        e.movement = { x_diff, y_diff };
        sendEvent(e);

        m_last_position.x = m_rigid_body.getRoundedX();
        m_last_position.y = m_rigid_body.getRoundedY();
    }
}
