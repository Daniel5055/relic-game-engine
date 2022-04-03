#include "PlayerPhysicsComponent.h"

# include "Material.h"
#include "RigidBody.h"

jinny::PlayerPhysicsComponent::PlayerPhysicsComponent(const double mass, double max_x_speed, double max_y_speed, const framework::Shape shape)
    :m_rigid_body(mass, 0, { max_x_speed, max_y_speed }, shape, framework::Material::entity), m_last_position(shape.x, shape.y)
{
    // Set rigid body
    PhysicsMessage msg;
    msg.type = PMessageType::set_rigid_body;
    msg.object_id = getObjectId();
    msg.rigid_body = &m_rigid_body;
    sendMessage(msg);
}

void jinny::PlayerPhysicsComponent::handleEvent(const ObjectEvent e)
{
    if (e.type == ObjectEvent::Type::input_triggered)
    {
        double is_down = 0;
        if (e.input.type == ObjectInputType::key_down)
        {
            is_down = 1;

        }
        else if (e.input.type == ObjectInputType::key_up)
        {
            is_down = -1;
        }

        // TODO: Change this so that Player physics does not have to care about the key, but rather care on the idea, (Like move north south etc)
        switch (e.input.key)
        {
        case 'a':
            m_rigid_body.applyMFForce({ is_down * -100, 0 });

            break;

        case 'd':
            m_rigid_body.applyMFForce({ is_down * 100, 0 });

            break;

        case 'w':
            m_rigid_body.applyMFForce({ 0, is_down * -100 });

            break;

        case 's':
            m_rigid_body.applyMFForce({ 0, is_down * 100 });

            break;
        }
    }
}

void jinny::PlayerPhysicsComponent::doUpdates()
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
