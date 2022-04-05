#include "DynamicRigidBodyPhysicsComponent.h"

#include "RigidBody.h"

relic::DynamicRigidBodyPhysicsComponent::DynamicRigidBodyPhysicsComponent(const double mass, double max_x_speed, double max_y_speed, const framework::Shape shape, const framework::Material material, framework::Vector force)
    :m_rigid_body(mass, 0, { max_x_speed, max_y_speed }, shape, material), m_last_position({shape.x, shape.y})
{
    m_rigid_body.applySFForce(force);
        PhysicsMessage msg;
        msg.type = PMessageType::set_rigid_body;
        msg.object_id = getObjectId();
        msg.rigid_body = &m_rigid_body;

        sendMessage(msg);
}

void relic::DynamicRigidBodyPhysicsComponent::doUpdates()
{
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
