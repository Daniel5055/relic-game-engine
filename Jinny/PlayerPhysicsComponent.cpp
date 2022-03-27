#include "PlayerPhysicsComponent.h"

# include "Material.h"
#include "RigidBody.h"

Jinny::PlayerPhysicsComponent::PlayerPhysicsComponent(double mass, double max_x_speed, double max_y_speed)
{
    // Create Data
    m_rigid_body = new Framework::RigidBody(mass, 0, {max_x_speed, max_y_speed}, nullptr, Framework::Material::ENTITY);
}

void Jinny::PlayerPhysicsComponent::initialize(GameObject& object)
{
    setObject(&object);

    // Set Shape
    ObjectEvent o_event = *object.getQueueIterator();
    if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
    {
        m_rigid_body->setShape(o_event.shape);
    }

    PhysicsMessage msg_1;
    msg_1.type = PMessageType::SET_RIGID_BODY;
    msg_1.object_ID = object.getObjectID();
    msg_1.rigid_body = m_rigid_body;
    pushMessage(msg_1);
}

void Jinny::PlayerPhysicsComponent::update()
{
    handleEvents();
    handleMessages();
}

Jinny::PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
    delete m_rigid_body;
    m_rigid_body = nullptr;

    delete m_rigid_body;
    m_rigid_body = nullptr;
}

void Jinny::PlayerPhysicsComponent::handleEvents()
{
    for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
    {

        if (it->type == EventType::INPUT_TRIGGERED)
        {
            double is_down = 0;
            if (it->input.type == ObjectInputType::KEY_DOWN)
            {
                is_down = 1;

            }
            else if (it->input.type == ObjectInputType::KEY_UP)
            {
                is_down = -1;
            }

            switch (it->input.key)
            {
            case 'a':
                m_rigid_body->applyMFForce({ is_down * -100, 0 });

                break;

            case 'd':
                m_rigid_body->applyMFForce({ is_down * 100, 0 });

                break;

            case 'w':
                m_rigid_body->applyMFForce({ 0, is_down * -100 });

                break;

            case 's':
                m_rigid_body->applyMFForce({ 0, is_down * 100 });

                break;
            }
        }
    }
}

void Jinny::PlayerPhysicsComponent::handleMessages()
{

}
